#ifndef TNODO_H
#define TNODO_H

#include "TEntidad.hpp"
#include <vector>

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

    private:
        TEntidad* entidad;
        std::vector<TNodo*> hijos;
        TNodo* padre;
};

#endif
