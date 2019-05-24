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
        ZNode* getPadre();

        bool setEntidad(TEntidad*);
        TEntidad* getEntidad();

        bool Visibility;
    protected:
        ZNode* Padre;
        TEntidad* Entidad;
};

#endif
