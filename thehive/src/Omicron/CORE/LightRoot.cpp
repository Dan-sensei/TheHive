#include "LightRoot.hpp"
#include <Omicron/Omicron.hpp>
#include <Singleton.hpp>

glm::vec3* LightRoot::CameraPosition = nullptr;
LightRoot::LightRoot(ZNode* P)
:ZNode(P), SPOT(0), POINT(0), MAXSPOT(0), MAXPOINT(0)
{
    static_cast<StandardNode*>(P)->addHijo(this);
    SPOT_LIGHTS.reserve(10);
    POINT_LIGHTS.reserve(15);
    Engine = Singleton<Omicron>::Instance();
}

LightRoot::LightRoot(const LightRoot &orig)
:SPOT_LIGHTS(orig.SPOT_LIGHTS), POINT_LIGHTS(POINT_LIGHTS), SPOT(orig.SPOT), POINT(orig.POINT), MAXSPOT(orig.MAXSPOT), MAXPOINT(orig.MAXPOINT)
{}

LightRoot::~LightRoot(){
    SPOT_LIGHTS.clear();
    POINT_LIGHTS.clear();
    std::cout << " MAX SPOTS " << MAXSPOT << '\n';
    std::cout << "MAX POINTS " << MAXPOINT << '\n' << '\n';
}

void LightRoot::setActive(uint8_t ZONE, bool Active) {
    auto SPOT_it = SPOT_LIGHTS.begin();
    while(SPOT_it != SPOT_LIGHTS.end()){
        if(SPOT_it->ZONE == ZONE)
            SPOT_it->ACTIVE = Active;

        ++SPOT_it;
    }

    auto POINT_it = POINT_LIGHTS.begin();
    while(POINT_it != POINT_LIGHTS.end()){
        if(POINT_it->ZONE == ZONE)
            POINT_it->ACTIVE = Active;

        ++POINT_it;
    }
}


ZStaticSpotLight* LightRoot::emplace_SpotLight(const glm::vec3 &MVP, const glm::vec3 &Color, uint8_t ZONE) {
    SPOT_LIGHTS.emplace_back(MVP, Color, ZONE);
    return &SPOT_LIGHTS.back();
}

ZStaticPointLight* LightRoot::emplace_PointLight(const glm::vec3 &MVP, const glm::vec3 &Color, uint8_t ZONE) {
    POINT_LIGHTS.emplace_back(MVP, Color, ZONE);
    return &POINT_LIGHTS.back();
}


#define DISTANCE 50*50

void LightRoot::draw() {

    SPOT = 0;
    POINT = 0;

    glm::vec3 CameraPos = *CameraPosition;

    std::vector<ZStaticSpotLight*> SPOTLIGHTS_PTR;

    auto SPOT_it = SPOT_LIGHTS.begin();
    while(SPOT_it != SPOT_LIGHTS.end()){
        if(SPOT_it->ACTIVE && glm::length2(SPOT_it->getPosition()-CameraPos) < DISTANCE) {
            ++SPOT;
            SPOTLIGHTS_PTR.push_back(&(*SPOT_it));
        }
        ++SPOT_it;
    }

    std::vector<ZStaticPointLight*> POINTLIGHTS_PTR;
    POINTLIGHTS_PTR.reserve(20);

    auto POINT_it = POINT_LIGHTS.begin();
    while(POINT_it != POINT_LIGHTS.end()){
        if(POINT_it->ACTIVE && glm::length2(POINT_it->getPosition()-CameraPos)) {
            ++POINT;
            POINTLIGHTS_PTR.push_back(&(*POINT_it));
        }
        ++POINT_it;
    }

    Engine->setLights(SPOT, POINT);
    if(SPOT > MAXSPOT) MAXSPOT = SPOT;
    if(POINT > MAXPOINT) MAXPOINT = POINT;

    for(uint8_t i = 0; i < SPOTLIGHTS_PTR.size(); ++i){
        SPOTLIGHTS_PTR[i]->setN(i);
        SPOTLIGHTS_PTR[i]->beginDraw();
        SPOTLIGHTS_PTR[i]->endDraw();
    }

    for(uint8_t i = 0; i < POINTLIGHTS_PTR.size(); ++i){
        POINTLIGHTS_PTR[i]->setN(i);
        POINTLIGHTS_PTR[i]->beginDraw();
        POINTLIGHTS_PTR[i]->endDraw();
    }

}

bool LightRoot::isLeaf(){
    return false;
}
