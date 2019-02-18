#ifndef TLUZDIRIGIDA_H
#define TLUZDIRIGIDA_H

#include <Util.hpp>
#include "TLuz.hpp"
//class TLuz{
class TLuzDirigida : public TLuz {
    public:
        TLuzDirigida();
        TLuzDirigida(gg::Color&,gg::Vector3f&);
        virtual ~TLuzDirigida ();

        void setDireccion(gg::Vector3f&);
        gg::Vector3f getDireccion();

        virtual void beginDraw();
        virtual void endDraw();

    private:
        gg::Vector3f direccion;

};

#endif
