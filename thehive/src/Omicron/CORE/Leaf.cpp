#include "Leaf.hpp"

Leaf::Leaf()
:entidad(nullptr){

}

Leaf::Leaf(StandardNode* P, TEntidad* Ent)
:ZNode(P), entidad(Ent)
{

}


Leaf::Leaf(const Leaf &orig)
:ZNode(orig), entidad(orig.entidad)
{

}

Leaf::~Leaf(){
    delete entidad;
}


void Leaf::draw(){
    if(entidad){
        entidad->beginDraw();
        entidad->endDraw();
    }
}

bool Leaf::isLeaf(){
    return true;
}
