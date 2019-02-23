#ifndef TLUZPUNTUAL_H
#define TLUZPUNTUAL_H

#include <Util.hpp>
#include "TLuz.hpp"

//class TLuz{
class TLuzPuntual : public TLuz {
    public:
        TLuzPuntual();
        TLuzPuntual(gg::Color&,gg::Vector3f&);
        virtual ~TLuzPuntual ();

        void setPosicion(gg::Vector3f&);
        gg::Vector3f getPosicion();

        virtual void beginDraw(const uint8_t&);
        virtual void endDraw(const uint8_t&);

    private:
        gg::Vector3f posicion;

};

#endif
