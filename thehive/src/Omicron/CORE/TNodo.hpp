#ifndef TNODO_H
#define TNODO_H

#include <Omicron/CORE/TEntidad.hpp>
#include <deque>

class TNodo {
    public:
        TNodo();
        TNodo(TNodo*,TEntidad*);
        virtual ~TNodo();

        void addHijo(TNodo*);
        void remHijo(TNodo*);

        bool setEntidad(TEntidad*);
        TEntidad* getEntidad();

        bool setPadre(TNodo*);
        TNodo* getPadre();

        void draw();
        void drawRoot_M();
        void drawRoot();

        void setVisibility(bool Flag);

        void ROOT_OkameraUpdate();
        void ROOT_LightsUpdate();

    private:
        TEntidad* entidad;
        std::deque<TNodo*> hijos;
        TNodo* padre;
        bool Visibility;
};

#endif
