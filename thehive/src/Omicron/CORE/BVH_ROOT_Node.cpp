#include "BVH_ROOT_Node.hpp"

BVH_ROOT_Node::BVH_ROOT_Node()
{}

BVH_ROOT_Node::BVH_ROOT_Node(ZNode* P)
:ZNode(P)
{}


BVH_ROOT_Node::BVH_ROOT_Node(const BVH_ROOT_Node &orig)
:ZNode(orig), Hierarchy(orig.Hierarchy)
{}

BVH_ROOT_Node::~BVH_ROOT_Node(){
    Hierarchy.clear();
}

bool BVH_ROOT_Node::isLeaf(){
    return false;
}

void BVH_ROOT_Node::draw(){
    // Coherent Hierarchical Culling


}
