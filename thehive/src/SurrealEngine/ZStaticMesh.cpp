#include "ZStaticMesh.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"

// glm::mat4 TEntidad::modelMatrix;
// glm::mat4 TEntidad::viewMatrix;
// glm::mat4 TEntidad::projMatrix;

ZStaticMesh::ZStaticMesh()
:VAO(0), zmat(nullptr)
{
    glGenVertexArrays(1, &VAO);

};

bool ZStaticMesh::load(const std::string& Name){

    ZMeshData* Mesh = AssetManager::getMeshData(Name);
    zmat = Mesh->zmat;

    if(Mesh->PositionsNormals.size() == 0) return false;

    IndexSize = Mesh->Indexes.size();

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mesh->Indexes.size()*sizeof(unsigned short), &(Mesh->Indexes[0]), GL_STATIC_DRAW);


    addVertexBuffer(Mesh->PositionsNormals, 6);
    addVertexBuffer(Mesh->UV_Coords, 2);
    addVertexBuffer(Mesh->TangentsBitangents, 6);

    glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);

        glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 3, GL_FLOAT, false, 12);
        glVertexAttribFormat(2, 2, GL_FLOAT, false, 0);
        glVertexAttribFormat(3, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(4, 3, GL_FLOAT, false, 12);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);
        glVertexAttribBinding(2, 1);
        glVertexAttribBinding(3, 2);
        glVertexAttribBinding(4, 2);

        glBindVertexBuffer(0, VBOs[0], 0, 24);
        glBindVertexBuffer(1, VBOs[1], 0, 8);
        glBindVertexBuffer(2, VBOs[2], 0, 24);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBindVertexArray(0);

    return true;
}

void ZStaticMesh::addVertexBuffer(std::vector<float> &data, unsigned int DataLength){

    VBOs.push_back(0);

    glGenBuffers(1, &VBOs.back());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs.back());
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), &data[0], GL_STATIC_DRAW);

}

void ZStaticMesh::assignMaterial(ZMaterial* material_){
    zmat = material_;
}

void ZStaticMesh::beginDraw(){
    Shader* sh = zmat->getShader();

    // VISTA
    GLuint V = sh->getUniformLocation("V");
    glUniformMatrix4fv(V,1,GL_FALSE,&viewMatrix[0][0]);

    // MODELO
    GLuint M = sh->getUniformLocation("M");
    glUniformMatrix4fv(M,1,GL_FALSE,&modelMatrix[0][0]);

    // MODELO*VISTA EN 3X3
    glm::mat3 MV = glm::mat3(viewMatrix * modelMatrix);
    GLuint MV3x3 = sh->getUniformLocation("MV3x3");
    glUniformMatrix3fv(MV3x3,1,GL_FALSE,&MV[0][0]);

    // MODELO*VISTA*PERSPECTIVA
    glm::mat4 MVP_L = projMatrix * viewMatrix * modelMatrix;
    GLuint MVP = sh->getUniformLocation("MVP");
    glUniformMatrix4fv(MVP,1,GL_FALSE,&MVP_L[0][0]);

    glBindVertexArray(VAO);

    // LA FINALE
    zmat->Bind();
    glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_SHORT, nullptr);
}

void ZStaticMesh::endDraw(){}

ZStaticMesh::~ZStaticMesh(){
    //std::cout << "Deleting mesh..." << '\n';
    uint8_t i = VBOs.size() + 1;
    while(--i)  glDeleteBuffers(1, &VBOs[i]);

    glDeleteVertexArrays(1, &VAO);
}
