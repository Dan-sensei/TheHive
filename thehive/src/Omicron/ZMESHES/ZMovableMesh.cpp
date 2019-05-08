#include "ZMovableMesh.hpp"
#include <Omicron/AssetManager.hpp>
#include <iostream>
#include <Singleton.hpp>

#include <ShaderUniformMapping.hpp>


ZMovableMesh::ZMovableMesh() {
    zmat = nullptr;
    Radius = 0;
    MVP = glm::mat4();
}

bool ZMovableMesh::load(const std::string& Name){
    MeshLODs.reserve(1);
    MeshLODs.push_back(Singleton<AssetManager>::Instance()->getMeshData(Name));

    return true;
}

void ZMovableMesh::beginDraw(){

    glm::vec3 ObjectPos(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);

    uint8_t LOD = 0;
    if(LODTest(ObjectPos, LOD)) return;

    Shader* sh = zmat->getShader();
    zmat->Bind();

    glm::mat4 MV = viewMatrix*modelMatrix;
    // MODELO
    glUniformMatrix4fv(9,1,GL_FALSE,&MV[0][0]);

    // NORMAL_MATRIX
    glm::mat3 VP = glm::transpose(glm::inverse(glm::mat3(MV)));
    glUniformMatrix3fv(_U_MODEL,1,GL_FALSE,&VP[0][0]);

    // MODELO*VISTA*PERSPECTIVA
    glUniformMatrix4fv(12,1,GL_FALSE,&MVP[0][0]);

    MVP = projMatrix * viewMatrix * modelMatrix;
    //GLuint MVP = sh->getUniformLocation("MVP");
    glUniformMatrix4fv(_U_MVP,1,GL_FALSE,&MVP[0][0]);

    // LA FINALE
    MeshLODs[LOD]->draw();
}


void ZMovableMesh::endDraw(){}

ZMovableMesh::~ZMovableMesh(){
}
