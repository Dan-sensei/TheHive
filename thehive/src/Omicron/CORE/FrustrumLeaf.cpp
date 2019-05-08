#include "FrustrumLeaf.hpp"
#include <glm/gtx/normalize_dot.hpp>


glm::vec3* FrustrumLeaf::CameraPosition;


FrustrumLeaf::FrustrumLeaf()
{}

FrustrumLeaf::FrustrumLeaf(StandardNode* P, TEntidad* Ent)
:ZNode(static_cast<ZNode*>(P), Ent)
{
    static_cast<StandardNode*>(P)->addHijo(this);
}


FrustrumLeaf::FrustrumLeaf(const FrustrumLeaf &orig)
:ZNode(orig.Padre, orig.Entidad)
{

}

FrustrumLeaf::~FrustrumLeaf(){}


void FrustrumLeaf::draw(){
    if(Entidad){
        glm::vec2 ViewDirection = glm::vec2(-viewMatrix[0][2], -viewMatrix[2][2]);

        if(isInsideFrustrum(ViewDirection)){
            Entidad->beginDraw();
            Entidad->endDraw();
        }

    }
}

bool FrustrumLeaf::isLeaf(){
    return true;
}

#define GRADOVISION 0

bool FrustrumLeaf::isInsideFrustrum(const glm::vec2 &ViewDirection){

    //frustrum
    glm::vec2 dirobj;
    glm::vec2 campos = glm::vec2((*CameraPosition).x, (*CameraPosition).z);

    if(LastFailedFrustrumCorner != -1){
        dirobj = CORNERS[LastFailedFrustrumCorner] - campos;
        float sol         = glm::fastNormalizeDot(dirobj, ViewDirection);
        if(GRADOVISION < sol) {
            return true;
        }
    }

    for (uint8_t i = 0; i < 4; ++i) {
        if(i == LastFailedFrustrumCorner) continue;

        dirobj = CORNERS[i] - campos;
        float sol         = glm::fastNormalizeDot(dirobj, ViewDirection);
        if(GRADOVISION < sol) {
            LastFailedFrustrumCorner = i;
            return true;
        }
    }

    LastFailedFrustrumCorner = -1;
    return false;
}

void FrustrumLeaf::setCameraPtr(glm::vec3* _PlayerPosition){
    CameraPosition = _PlayerPosition;
}

void FrustrumLeaf::beginDraw(){};
void FrustrumLeaf::endDraw(){};
