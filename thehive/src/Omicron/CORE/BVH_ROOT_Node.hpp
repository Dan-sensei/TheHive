#ifndef _BVH_ROOT_NODE_H
#define _BVH_ROOT_NODE_H

#include <Omicron/CORE/BVH_Node.hpp>
#include <stack>
#include <vector>
#include <queue>

class BVH_ROOT_Node : public ZNode, public TEntidad {

    public:
        BVH_ROOT_Node(ZNode* P);
        BVH_ROOT_Node(const BVH_ROOT_Node &orig);
        virtual ~BVH_ROOT_Node();

        void addNode(BoundingBox _AABB, ZNode* _Leaf, uint16_t _Father, uint16_t _FirstChild);
        virtual bool isLeaf();
        virtual void draw();

        virtual void beginDraw();
        virtual void endDraw();

        std::vector<BVH_Node> Hierarchy;

    private:

        bool QueryResultAvailable(BVH_Node* N);
        void TraverseNode(BVH_Node* N);
        void PullUpVisibility(BVH_Node* N);
        void Render(BVH_Node* N);
        void IssueOcclusionQuery(BVH_Node* N);

        std::stack<BVH_Node*> TraversalStack;
        std::queue<BVH_Node*> QueryQueue;


        uint8_t FrameID;

};

#endif
