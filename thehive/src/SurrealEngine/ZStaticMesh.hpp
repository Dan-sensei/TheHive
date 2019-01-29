#ifndef ZSTATICMESH_H
#define ZSTATICMESH_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"

class ZStaticMesh{
    public:
        ZStaticMesh();
        ZStaticMesh(const ZStaticMesh &orig) = delete;
        ~ZStaticMesh();

        bool load(const std::string& Name);

    private:
        //Específico de OpenGL=========================================================================//
            unsigned int VAO;
            std::vector<unsigned int> VBOs;
            unsigned int IndexBuffer;
            void Bind();
            void Unbind();
            void addVertexBuffer(std::vector<float>& data, unsigned int DataLength, uint8_t layout);
        //=============================================================================================//

        ZMaterial* zmat;
};

#endif