#include "ZMesh.hpp"
#include <glm/gtx/norm.hpp>
#include <BinaryParser.hpp>
#include <glm/gtx/fast_square_root.hpp>
#include <glm/gtx/normalize_dot.hpp>

#define LOD1 10000
#define KILL 100
//#define GRADOVISION cos(30*3.14159265359/180.f)


glm::vec3* ZMesh::PlayerPosition;

void ZMesh::assignMaterial(ZMaterial* material_){
    zmat = material_;
}

bool ZMesh::LODTest(const glm::vec3 Position, uint8_t &LOD){

    float distance = glm::fastLength(Position-(*PlayerPosition)) - Radius;
    if(distance > KILL) return true;
    else if(distance > LOD1 && MeshLODs.size() > 1) LOD = 1;

    return false;
}


void ZMesh::setPlayerPtr(glm::vec3* _PlayerPosition){
    PlayerPosition = _PlayerPosition;
}
