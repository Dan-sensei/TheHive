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


        virtual void beginDraw(const uint8_t&);
        virtual void endDraw(const uint8_t&);

    private:
        std::array<ZStaticMesh, 5> poses;

};

#endif
