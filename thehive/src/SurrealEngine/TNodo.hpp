#ifndef TNODO_H
#define TNODO_H

#include "TEntidad.hpp"
#include <deque>

class TNodo {
    public:
        TNodo(int8_t _tipo = -1);
        TNodo(TNodo*,TEntidad*,int8_t _tipo = -1);
        ~TNodo();

        void addHijo(TNodo*);
        void remHijo(TNodo*);

        bool setEntidad(TEntidad*);
        TEntidad* getEntidad();

        bool setPadre(TNodo*);
        TNodo* getPadre();

        void draw(const uint8_t&);
        void drawRoot();
        void drawRoot(const uint8_t&);

        void setVisibility(bool Flag);

        int8_t getMapNode(){return map_node;}

    private:
        TEntidad* entidad;
        std::deque<TNodo*> hijos;
        TNodo* padre;
        int8_t map_node;
        bool Visibility;
};

#endif
