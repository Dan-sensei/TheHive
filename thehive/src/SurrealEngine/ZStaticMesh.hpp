#ifndef ZSTATICMESH_H
#define ZSTATICMESH_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "TNodo.hpp"

class ZStaticMesh : public TEntidad {
    public:
        ZStaticMesh();
        ZStaticMesh(const ZStaticMesh &orig) = delete;
        ~ZStaticMesh();

        bool load(const std::string& Name);
        void assignMaterial(ZMaterial* material_);
        virtual void beginDraw(const uint8_t&);
        virtual void endDraw(const uint8_t&);

    private:
        //Específico de OpenGL=========================================================================//
            unsigned int VAO;
            std::vector<unsigned int> VBOs;
            unsigned int IndexBuffer;
            unsigned int IndexSize;
            void Bind();
            void Unbind();
            void addVertexBuffer(std::vector<float>& data, unsigned int DataLength);
        //=============================================================================================//

        ZMaterial* zmat;
};

#endif
