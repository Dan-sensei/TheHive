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

        virtual void beginDraw(const uint8_t&);
        virtual void endDraw(const uint8_t&);

    private:
        glm::vec3 posicion;

};

#endif
