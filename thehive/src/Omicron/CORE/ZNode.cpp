#include "ZNode.hpp"

ZNode::ZNode()
:ZNode(nullptr)
{}

ZNode::ZNode(ZNode* P)
:Visibility(false), Padre(P)
{}

ZNode::ZNode(const ZNode &orig)
:Visibility(orig.Visibility), Padre(orig.Padre)
{}

ZNode::~ZNode(){}

void ZNode::setVisibility(bool Flag){
    Visibility = Flag;
};

ZNode* ZNode::getPadre(){
    return Padre;
}
