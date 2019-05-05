#include "Leaf.hpp"

Leaf::Leaf()
{}

Leaf::Leaf(StandardNode* P, TEntidad* Ent)
:ZNode(static_cast<ZNode*>(P), Ent)
{
    static_cast<StandardNode*>(P)->addHijo(this);
}


Leaf::Leaf(const Leaf &orig)
:ZNode(orig.Padre, orig.Entidad)
{

}

Leaf::~Leaf(){}


void Leaf::draw(){
    if(Entidad){
        Entidad->beginDraw();
        Entidad->endDraw();
    }
}

bool Leaf::isLeaf(){
    return true;
}
