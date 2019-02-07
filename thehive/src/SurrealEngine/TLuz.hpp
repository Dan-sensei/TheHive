#ifndef TLUZ_H
#define TLUZ_H

#include <Util.hpp>
#include "TEntidad.hpp"
//class TLuz{
class TLuz : public TEntidad {
    public:
        TLuz();
        TLuz(gg::Color&);
        virtual ~TLuz ();

        virtual void setIntensidad(gg::Color&);
        virtual gg::Color getIntensidad();

        virtual void beginDraw();
        virtual void endDraw();

    private:
        gg::Color intensidad;

};

#endif
