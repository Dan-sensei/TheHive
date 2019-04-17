// Primera generacion de BT
#include "BehaviorTree.hpp"

BehaviorTree::BehaviorTree(){}
BehaviorTree::BehaviorTree(Behavior* behavior_Root){
  b_Root=behavior_Root; //Asigna el comportamiento raiz
}


void BehaviorTree::tick(){
  b_Root->tick(); //Run de la raiz
}

BehaviorTree::~BehaviorTree(){
}
