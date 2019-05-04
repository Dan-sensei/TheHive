#ifndef _LEAF_H
#define _LEAF_H

#include <Omicron/CORE/ZNode.hpp>
#include <Omicron/CORE/StandardNode.hpp>
#include <Omicron/CORE/TEntidad.hpp>
#include <deque>

class Leaf : public ZNode {
    Leaf();
    Leaf(StandardNode* P, TEntidad* Ent);
    Leaf(const Leaf &orig);
    virtual ~Leaf();

    virtual void draw();
    virtual bool isLeaf();

    TEntidad* entidad;
};

#endif
