#ifndef ZMESH_H
#define ZMESH_H

#include <vector>
#include <cstdint>
#include <string>
//#include "ZMaterial.hpp"

class ZMesh{
    public:

        ZMesh();
        ZMesh(const ZMesh &orig);
        ~ZMesh();

        bool load(const std::string& path, unsigned int type);


    private:

        std::vector< float > Positions;
        std::vector< float > UV_Coords;
        std::vector< float > Normals;
        std::vector< float > Tangents;
        std::vector< float > Bitangents;
        std::vector< unsigned short > Indexes;

        //Específico de OpenGL=========================================================================//
            unsigned int VAO;
            std::vector<unsigned int> VBOs;
            unsigned int IndexBuffer;
            void Bind();
            void Unbind();
            void addVertexBuffer(std::vector<float>& data, unsigned int type, unsigned int DataLength, uint8_t layout);
        //=============================================================================================//

        //ZMaterial* zmat;
};

#endif