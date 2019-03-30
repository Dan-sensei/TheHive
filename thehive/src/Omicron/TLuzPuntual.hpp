#ifndef TLUZPUNTUAL_H
#define TLUZPUNTUAL_H

#include <Util.hpp>
#include "TLuz.hpp"

//class TLuz{
class TLuzPuntual : public TLuz {
    public:
        TLuzPuntual();
        TLuzPuntual(gg::Color&,glm::vec3&);
        virtual ~TLuzPuntual ();

        void setPosicion(glm::vec3&);
        glm::vec3 getPosicion();

        virtual void beginDraw();
        virtual void endDraw();

    private:
        glm::vec3 posicion;

};

#endif
