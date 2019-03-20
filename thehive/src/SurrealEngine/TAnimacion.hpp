#ifndef TANIMACION_H
#define TANIMACION_H

#include "TEntidad.hpp"
#include "ZStaticMesh.hpp"
#include <array>
#include <cstdint>

class TAnimacion: public TEntidad {

    public:
        TAnimacion();
        TAnimacion(std::array<ZStaticMesh, 5> &poses_);
        virtual ~TAnimacion ();


        virtual void beginDraw();
        virtual void endDraw();

    private:
        std::array<ZStaticMesh, 5> poses;

};

#endif
