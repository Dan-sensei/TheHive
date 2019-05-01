#ifndef TLUZ_H
#define TLUZ_H

#include <Util.hpp>
#include <Omicron/CORE/TEntidad.hpp>
#include "Shader.hpp"

class TLuz : public TEntidad {
    public:
        static unsigned char * buffer;
        TLuz();
        TLuz(gg::Color&);//,unsigned char * buff);
        TLuz(Shader*);
        TLuz(gg::Color&,Shader*);
        virtual ~TLuz ();

        virtual void setColor(gg::Color&);
        virtual gg::Color getColor();

        virtual void beginDraw();
        virtual void endDraw();

        void  setIntensidad(float &_color);
        float getIntensidad();

    protected:
        gg::Color color;
        float intensidad;
        Shader* light_shader;

};

#endif
