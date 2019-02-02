#ifndef TANIMACION_H
#define TANIMACION_H

#include "TEntidad.hpp"
#include "ZStaticMesh.hpp"
#include <array>

class TAnimacion: public TEntidad {

    public:
        TAnimacion();
        TAnimacion(std::array<ZStaticMesh, 5> &poses_);
        virtual ~TAnimacion ();


        virtual void beginDraw(int);
        virtual void endDraw();

    private:
        std::array<ZStaticMesh, 5> poses;

};

#endif
