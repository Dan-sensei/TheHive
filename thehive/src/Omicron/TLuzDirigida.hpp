#ifndef TLUZDIRIGIDA_H
#define TLUZDIRIGIDA_H

#include <Util.hpp>
#include "TLuz.hpp"
//class TLuz{
class TLuzDirigida : public TLuz {
    public:
        TLuzDirigida();
        TLuzDirigida(gg::Color&,glm::vec3&);
        virtual ~TLuzDirigida ();

        void setDireccion(glm::vec3&);
        glm::vec3 getDireccion();

        virtual void beginDraw();
        virtual void endDraw();

    private:
        glm::vec3 direccion;

};

#endif
