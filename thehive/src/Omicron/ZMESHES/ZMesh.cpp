#include "ZMesh.hpp"
#include <glm/gtx/norm.hpp>
#include <BinaryParser.hpp>
#include <glm/gtx/fast_square_root.hpp>
#include <glm/gtx/normalize_dot.hpp>

#define LOD1 10000
#define KILL 100
//#define GRADOVISION cos(30*3.14159265359/180.f)
#define GRADOVISION -0.17364817766


glm::vec3* ZMesh::PlayerPosition;
glm::vec3* ZMesh::CameraPosition;

void ZMesh::assignMaterial(ZMaterial* material_){
    zmat = material_;
}

void ZMesh::FrustrumTest(const glm::vec3 &Position, bool &dib){
    glm::vec3 vectores[]{
        VOX.BLB,
        VOX.BLF,
        VOX.BRB,
        VOX.BRF
    };
    //frustrum
    glm::vec3 dircam(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);
    dircam.y=0;
    dircam       *=-1;
    dircam       = glm::normalize(dircam);

    glm::vec3 dirobj;
    glm::vec3 campos = *CameraPosition;

    for (uint8_t i = 0; i < 4; ++i) {
        if(vectores[i]==glm::vec3()){
            dib=true;
            break;
        }

        dirobj = Position+vectores[i]-campos;
        dirobj.y = 0;
        //dirobj   = glm::normalize(dirobj);
        float sol         = glm::fastNormalizeDot(dirobj,dircam);
        if(GRADOVISION < sol) {
            dib=true;
            break;
        }
    }
}

bool ZMesh::LODTest(const glm::vec3 Position, uint8_t &LOD){

    float distance = glm::fastLength(Position-(*PlayerPosition)) - Radius;
    if(distance > KILL) return true;
    else if(distance > LOD1 && MeshLODs.size() > 1) LOD = 1;

    return false;
}

void ZMesh::loadBoundingBox(const std::string& BoundingBoxPath){
    if(!BoundingBoxPath.empty()){
        BinaryParser::ReadBoundingBox(BoundingBoxPath, &VOX);
        Radius = glm::fastLength(VOX.URB);
    }
}


void ZMesh::setPlayerPtr(glm::vec3* _PlayerPosition){
    PlayerPosition = _PlayerPosition;
}

void ZMesh::setCameraPtr(glm::vec3* _PlayerPosition){
    CameraPosition = _PlayerPosition;
}
