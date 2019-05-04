#ifndef _BVH_NODE_H
#define _BVH_NODE_H

#include <Omicron/CORE/ZNode.hpp>
#include <cstdint>

class BVH_Node {
    friend class BVH_ROOT_Node;
    public:
        BVH_Node();
        BVH_Node(uint16_t P);
        BVH_Node(uint16_t P, uint16_t _FirstChild, ZNode* _Leaf = nullptr);

        virtual bool isLeaf();

    private:
        ZNode* Leaf;
        uint16_t Father;
        uint16_t FirstChild;
};

#endif
