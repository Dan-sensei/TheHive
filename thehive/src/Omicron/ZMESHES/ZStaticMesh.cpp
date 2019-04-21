#include "ZStaticMesh.hpp"
#include <Omicron/AssetManager.hpp>


#include <iostream>
#include <sys/stat.h>
#include <BinaryParser.hpp>

#include <ShaderUniformMapping.hpp>


ZStaticMesh::ZStaticMesh(const glm::mat4 TheModelMatrix){
    localModelMatrix = TheModelMatrix;
    zmat = nullptr;
    Radius = 0;
}

bool ZStaticMesh::load(const std::string& Name){
    MeshLODs.reserve(2);
    MeshLODs.push_back(Singleton<AssetManager>::Instance()->getMeshData(Name));

    return true;
}

void ZStaticMesh::addLOD(std::string Name){
    //Check if file exists
    struct stat buffer;
    if(stat (Name.c_str(), &buffer) == 0) {
        MeshLODs.push_back(Singleton<AssetManager>::Instance()->getMeshData(Name));
    }
}


void ZStaticMesh::beginDraw(){

    glm::vec3 ObjectPos(localModelMatrix[3][0], localModelMatrix[3][1], localModelMatrix[3][2]);

    bool dib = false;
    FrustrumTest(ObjectPos, dib);
    if(!dib) return;
    //terminar frustrum

    uint8_t LOD = 0;
    if(LODTest(ObjectPos, LOD)) return;

    Shader* sh = zmat->getShader();
    zmat->Bind();

    glm::mat4 MV = viewMatrix*localModelMatrix;
    // MODELO
    glUniformMatrix4fv(9,1,GL_FALSE,&MV[0][0]);

    // NORMAL_MATRIX
    glm::mat3 VP = glm::transpose(glm::inverse(glm::mat3(MV)));
    glUniformMatrix3fv(_U_MODEL,1,GL_FALSE,&VP[0][0]);

    // MODELO*VISTA*PERSPECTIVA

    glUniformMatrix4fv(12,1,GL_FALSE,&MVP[0][0]);

    MVP = projMatrix * viewMatrix * localModelMatrix;
    //GLuint MVP = sh->getUniformLocation("MVP");
    glUniformMatrix4fv(_U_MVP,1,GL_FALSE,&MVP[0][0]);

    // LA FINALE
    MeshLODs[LOD]->draw();
}
void ZStaticMesh::beginDrawwithoutligt(){

    glm::vec3 ObjectPos(localModelMatrix[3][0], localModelMatrix[3][1], localModelMatrix[3][2]);
    uint8_t LOD = 0;
    LODTest(ObjectPos, LOD);

    Shader* sh = zmat->getShader();
    zmat->Bind();

    // MODELO*VISTA*PERSPECTIVA
    glm::mat4 MVP_L = projMatrix * viewMatrix * localModelMatrix;
    GLuint MVP = sh->getUniformLocation("MVP");
    glUniformMatrix4fv(MVP,1,GL_FALSE,&MVP_L[0][0]);

    // LA FINALE
    MeshLODs[LOD]->draw();
}

void ZStaticMesh::endDraw(){}

ZStaticMesh::~ZStaticMesh(){
    ////std::cout << "Deleting mesh..." << '\n';
}
