#ifndef TLUZ_H
#define TLUZ_H

#include <Util.hpp>
#include "TEntidad.hpp"
#include "Shader.hpp"


class TLuz : public TEntidad {
    public:
        TLuz();
        TLuz(gg::Color&);
        TLuz(Shader*);
        TLuz(gg::Color&,Shader*);
        virtual ~TLuz ();

        virtual void setIntensidad(gg::Color&);
        virtual gg::Color getIntensidad();

        virtual void beginDraw();
        virtual void endDraw();

    private:
        gg::Color intensidad;
        Shader* light_shader;

};

#endif
