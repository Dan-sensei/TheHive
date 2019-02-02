#ifndef TLUZ_H
#define TLUZ_H

#include <Util.hpp>

class TLuz{
//class TLuz : public TEntidad {
    public:
        TLuz();
        TLuz(gg::Color&);
        virtual ~TLuz ();

        void setIntensidad(gg::Color&);
        //void setDireccion(gg::Vector3f&);
        gg::Color getIntensidad();

        virtual void beginDraw();
        virtual void endDraw();

    private:
        gg::Color intensidad;
        //gg::Vector3f direccion;

};

#endif
