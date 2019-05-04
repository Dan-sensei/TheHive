#ifndef _BVH_ROOT_NODE_H
#define _BVH_ROOT_NODE_H

#include <Omicron/CORE/BVH_Node.hpp>
#include <vector>

class BVH_ROOT_Node : public ZNode {

    public:
        BVH_ROOT_Node();
        BVH_ROOT_Node(ZNode* P);
        BVH_ROOT_Node(const BVH_ROOT_Node &orig);
        ~BVH_ROOT_Node();

        virtual bool isLeaf();
        virtual void draw();

    private:
        std::vector<BVH_Node> Hierarchy;
};

#endif
