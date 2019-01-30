#include "ZStaticMesh.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"

ZStaticMesh::ZStaticMesh()
:VAO(0), zmat(nullptr)
{
    glGenVertexArrays(1, &VAO);

};

bool ZStaticMesh::load(const std::string& Name){

    ZMeshData* Mesh = AssetManager::getMeshData(Name);
    zmat = Mesh->zmat;

    if(Mesh->Positions.size() == 0) return false;

    IndexSize = Mesh->Indexes.size();

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mesh->Indexes.size()*sizeof(unsigned short), &(Mesh->Indexes[0]), GL_STATIC_DRAW);

    glBindVertexArray(VAO);
        addVertexBuffer(Mesh->Positions,  3, 0);
        addVertexBuffer(Mesh->UV_Coords,  2, 1);
        addVertexBuffer(Mesh->Normals,    3, 2);
        addVertexBuffer(Mesh->Tangents,   3, 3);
        addVertexBuffer(Mesh->Bitangents, 3, 4);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBindVertexArray(0);

    return true;
}

void ZStaticMesh::addVertexBuffer(std::vector<float> &data, unsigned int DataLength, uint8_t layout){

    VBOs.push_back(0);

    glGenBuffers(1, &VBOs.back());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs.back());
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), &data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(layout);
    glVertexAttribPointer(layout, DataLength, GL_FLOAT, GL_FALSE, 0, nullptr);

}

void ZStaticMesh::assignMaterial(ZMaterial* material_){
    zmat = material_;
}


void ZStaticMesh::Draw(){
    glBindVertexArray(VAO);
    zmat->Bind();
    glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_SHORT, nullptr);
}

ZStaticMesh::~ZStaticMesh(){
    //std::cout << "Deleting mesh..." << '\n';
    uint8_t i = VBOs.size() + 1;
    while(--i)  glDeleteBuffers(1, &VBOs[i]);

    glDeleteVertexArrays(1, &VAO);
}
