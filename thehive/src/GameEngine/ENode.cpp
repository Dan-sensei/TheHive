#include "ENode.hpp"

ENode::ENode(std::string m, std::string t = "NO_PATH"){
    mPath = m;  // Path al modelo
    tPath = t;  // Path a la textura

    mesh = nullptr;
    node = nullptr;
}
ENode::~ENode(){}

void ENode::setAutomaticCulling(int _state){
    node->setAutomaticCulling(_state);
}
