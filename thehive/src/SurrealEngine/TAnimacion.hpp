#ifndef TANIMACION_H
#define TANIMACION_H

#include "TEntidad.hpp"
#include "ZStaticMesh.hpp"
#include <Singleton.hpp>
#include "AssetManager.hpp"
#include <vector>
#include <cstdint>

class TAnimacion: public TEntidad {

    public:
        TAnimacion();
        TAnimacion(std::vector<ZMeshData> &poses_);
        virtual ~TAnimacion ();

        void Interpolate();

        virtual void beginDraw(const uint8_t&);
        virtual void endDraw(const uint8_t&);

    private:
        std::vector<ZMeshData> poses;
        Shader* shader;
        ZMaterial* zmat;
        int         it;
        unsigned int size;
        unsigned int VAO;

};

#endif
