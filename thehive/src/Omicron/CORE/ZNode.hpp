#ifndef _ZNODE_H
#define _ZNODE_H

#include <Omicron/CORE/TEntidad.hpp>
class ZNode{
    public:
        ZNode();
        ZNode(ZNode* P);
        ZNode(ZNode* P, TEntidad* _entidad);
        ZNode(const ZNode &orig);
        virtual ~ZNode();

        virtual void draw() = 0;
        virtual bool isLeaf() = 0;

        void setVisibility(bool Flag);
        inline bool getVisibility() { return Visibility; };
        ZNode* getPadre();

        bool setEntidad(TEntidad*);
        TEntidad* getEntidad();

    protected:
        ZNode* Padre;
        TEntidad* Entidad;
        bool Visibility;
};

#endif
