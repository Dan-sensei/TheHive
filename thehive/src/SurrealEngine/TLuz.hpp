#ifndef TLUZ_H
#define TLUZ_H

#include <Util.hpp>

class TLuz {
    public:
        TLuz();
        TLuz(gg::Color&);
        virtual ~TLuz ();

        void setIntensidad(gg::Color&);
        gg::Color getIntensidad();

        virtual void beginDraw();
        virtual void endDraw();

    private:
        gg::Color intensidad;

};

#endif
