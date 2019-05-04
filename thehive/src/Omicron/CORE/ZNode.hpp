#ifndef _ZNODE_H
#define _ZNODE_H

class ZNode{
    public:
        ZNode();
        ZNode(ZNode* P);
        ZNode(const ZNode &orig);
        virtual ~ZNode();

        virtual void draw() = 0;
        virtual bool isLeaf() = 0;

        void setVisibility(bool Flag);
        ZNode* getPadre();

    protected:
        ZNode* Padre;
        bool Visibility;
};

#endif
