#include "ZStaticMesh.hpp"
#include "AssetManager.hpp"

#include <glm/gtx/norm.hpp>
#include <iostream>
#include <sys/stat.h>


#define CONO_VISION 110
#define VISION_RADS cos(CONO_VISION*3.14159265359/180.f)

#define LOD1 10000
#define KILL 22500

glm::vec3* ZStaticMesh::PlayerPosition = nullptr;
TCamara* ZStaticMesh::camera = nullptr;

ZStaticMesh::ZStaticMesh()
:zmat(nullptr), MVP(0), M(0), MVP_Z(0)
{
    toDo = &ZStaticMesh::Dro;

    MVP_Z = AssetManager::getShader("Z-Prepass")->getUniformLocation("MVP");

}

bool ZStaticMesh::load(const std::string& Name){
    MeshLODs.reserve(2);
    MeshLODs.push_back(AssetManager::getMeshData(Name));
    return true;
}

void ZStaticMesh::addLOD(std::string Name){
    //Check if file exists
    struct stat buffer;
    if(stat (Name.c_str(), &buffer) == 0) {
        MeshLODs.push_back(AssetManager::getMeshData(Name));
    }
}

void ZStaticMesh::enableFrustumCulling(bool flag) {
    toDo = flag ? &ZStaticMesh::FrustumCullingTest : &ZStaticMesh::Dro;
}

void ZStaticMesh::assignMaterial(ZMaterial* material_){
    zmat = material_;
    auto sh = zmat->getShader();
    MVP = sh->getUniformLocation("MVP");
    M = sh->getUniformLocation("M");
}

void ZStaticMesh::setPlayerPtr(glm::vec3* _PlayerPosition){
    PlayerPosition = _PlayerPosition;
}

void ZStaticMesh::setMainCamera(TCamara* _camera){
    camera = _camera;
}


void ZStaticMesh::beginDraw(){
    (this->*toDo)();
}

void ZStaticMesh::FrustumCullingTest(){

    glm::vec3 CameraDir = glm::normalize(camera->getTarget() - camera->getPosition());
    glm::vec3 CameraToObjectDir = glm::normalize(glm::vec3(modelMatrix[3]) - camera->getPosition());

    if(glm::dot(CameraDir, CameraToObjectDir) < VISION_RADS) return;

    JustRender();
}

void ZStaticMesh::Dro(){

    uint8_t LOD = 0;
    localModelMatrix = modelMatrix;
    localMVP = projMatrix * viewMatrix * modelMatrix;

    // glm::vec3 ObjectPos = localModelMatrix[3];
    // float distance = glm::length2(ObjectPos-(*PlayerPosition));
    // if(distance > KILL) return;
    // else if(distance > LOD1 && MeshLODs.size() > 1) LOD = 1;


    // MODELO*VISTA*PERSPECTIVA
    glUniformMatrix4fv(MVP_Z,1,GL_FALSE,&localMVP[0][0]);

    // LA FINALE
    MeshLODs[LOD]->draw();
    DRAWN++;


}

void ZStaticMesh::JustRender(){

    uint8_t LOD = 0;

    // glm::vec3 ObjectPos = localModelMatrix[3];
    // float distance = glm::length2(ObjectPos-(*PlayerPosition));
    // if(distance > KILL) return;
    // else if(distance > LOD1 && MeshLODs.size() > 1) LOD = 1;

    zmat->Bind();

    // MODELO
    glUniformMatrix4fv(M,1,GL_FALSE,&localModelMatrix[0][0]);

    // MODELO*VISTA*PERSPECTIVA
    glUniformMatrix4fv(MVP,1,GL_FALSE,&localMVP[0][0]);

    // LA FINALE
    MeshLODs[LOD]->draw();

    DRAWN++;

}

void ZStaticMesh::endDraw(){}

ZStaticMesh::~ZStaticMesh(){
    ////std::cout << "Deleting mesh..." << '\n';
}
