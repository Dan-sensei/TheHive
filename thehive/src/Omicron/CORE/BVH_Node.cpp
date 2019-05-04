#include "BVH_Node.hpp"

BVH_Node::BVH_Node()
:BVH_Node(0, 0, nullptr)
{}

BVH_Node::BVH_Node(uint16_t P)
:BVH_Node(P, 0, nullptr)
{}

BVH_Node::BVH_Node(uint16_t P, uint16_t _FirstChild, ZNode* _Leaf)
:Father(P), FirstChild(_FirstChild), Leaf(_Leaf)
{}

bool BVH_Node::isLeaf(){
    return Leaf;
};
