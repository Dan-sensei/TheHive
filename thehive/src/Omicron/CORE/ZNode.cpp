#include "ZNode.hpp"

ZNode::ZNode()
:ZNode(nullptr)
{}

ZNode::ZNode(ZNode* P)
:ZNode(P, nullptr)
{}

ZNode::ZNode(ZNode* P, TEntidad* _entidad)
:Padre(P), Entidad(_entidad), Visibility(false)
{}

ZNode::ZNode(const ZNode &orig)
:Padre(orig.Padre), Entidad(orig.Entidad), Visibility(orig.Visibility)
{}

ZNode::~ZNode(){
    delete Entidad;
}

void ZNode::setVisibility(bool Flag){
    Visibility = Flag;
};

ZNode* ZNode::getPadre(){
    return Padre;
}

bool ZNode::setEntidad(TEntidad *_ent){
    if(_ent){
        Entidad = _ent;
        return true;
    }
    return false;
}

TEntidad* ZNode::getEntidad(){
    return Entidad;
}
