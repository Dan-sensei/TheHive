#include "ZStaticMesh.hpp"
#include "AssetManager.hpp"


ZStaticMesh::ZStaticMesh()
:zmat(nullptr)
{

}

bool ZStaticMesh::load(const std::string& Name){

    mesh = AssetManager::getMeshData(Name);

    return true;
}

void ZStaticMesh::assignMaterial(ZMaterial* material_){
    zmat = material_;
}

void ZStaticMesh::beginDraw(){

    Shader* sh = zmat->getShader();

    // MODELO
    GLuint M = sh->getUniformLocation("M");
    glUniformMatrix4fv(M,1,GL_FALSE,&modelMatrix[0][0]);

    // MODELO*VISTA*PERSPECTIVA
    glm::mat4 MVP_L = projMatrix * viewMatrix * modelMatrix;
    GLuint MVP = sh->getUniformLocation("MVP");
    glUniformMatrix4fv(MVP,1,GL_FALSE,&MVP_L[0][0]);

    // LA FINALE
    zmat->Bind();
    mesh->draw();

}

void ZStaticMesh::endDraw(){}

ZStaticMesh::~ZStaticMesh(){
    ////std::cout << "Deleting mesh..." << '\n';

}
