#ifndef _STANDARDNODE_H
#define _STANDARDNODE_H

#include <Omicron/CORE/ZNode.hpp>
#include <Omicron/CORE/TEntidad.hpp>
#include <deque>

class StandardNode : public ZNode {
    public:
        StandardNode();
        StandardNode(ZNode* P, TEntidad* _ent);
        virtual ~StandardNode();

        void addHijo(ZNode*);
        void remHijo(ZNode*);

        bool setEntidad(TEntidad*);
        TEntidad* getEntidad();

        bool setPadre(ZNode*);

        virtual void draw();
        virtual bool isLeaf();
        void drawRoot();

        void setVisibility(bool Flag);

        void ROOT_OkameraUpdate();
        void ROOT_LightsUpdate();
        void ROOT_ObjectsUpdate();

    private:
        TEntidad* entidad;
        std::deque<ZNode*> hijos;
        bool Visibility;
};

#endif
