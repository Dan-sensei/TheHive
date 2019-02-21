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
        void drawRoot();

    private:
        TEntidad* entidad;
        std::deque<TNodo*> hijos;
        TNodo* padre;
        uint8_t tipo_ent;
};

#endif
