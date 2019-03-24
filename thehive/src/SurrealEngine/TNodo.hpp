#ifndef TNODO_H
#define TNODO_H

#include "TEntidad.hpp"
#include <deque>

class TNodo {
    public:
        TNodo();
        TNodo(TNodo*,TEntidad*);
        ~TNodo();

        void addHijo(TNodo*);
        void remHijo(TNodo*);

        bool setEntidad(TEntidad*);
        TEntidad* getEntidad();

        bool setPadre(TNodo*);
        TNodo* getPadre();

        void draw();
        void JustRender();

        void SwitchRasterCulling();
        void drawRoot(void (TNodo::*Target)());

        void setVisibility(bool Flag);

    private:
        TEntidad* entidad;
        std::deque<TNodo*> hijos;
        TNodo* padre;
        bool Visibility;
};

#endif
