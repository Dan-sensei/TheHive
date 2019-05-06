#include "BVH_ROOT_Node.hpp"


BVH_ROOT_Node::BVH_ROOT_Node(ZNode* P)
:ZNode(P), FrameID(0)
{
    static_cast<StandardNode*>(P)->addHijo(this);


}


BVH_ROOT_Node::BVH_ROOT_Node(const BVH_ROOT_Node &orig)
:ZNode(orig), Hierarchy(orig.Hierarchy)
{}

BVH_ROOT_Node::~BVH_ROOT_Node(){
    Hierarchy.clear();
}

bool BVH_ROOT_Node::isLeaf(){
    return false;
}
#include <Singleton.hpp>
#include <Omicron/Omicron.hpp>
#include <iostream>
void BVH_ROOT_Node::draw(){
    // Coherent Hierarchical Culling

    glm::vec3 ViewDirection = glm::vec3(-viewMatrix[0][2], 0, -viewMatrix[2][2]);
    TraversalStack.push(&Hierarchy[0]);
    TraversalStack.push(&Hierarchy[1]);

    while(!TraversalStack.empty() || !QueryQueue.empty()){
        while ( !QueryQueue.empty() && (QueryResultAvailable(QueryQueue.front()) || TraversalStack.empty()) ) {
            BVH_Node* N = QueryQueue.front();
            QueryQueue.pop();

            unsigned int visiblePixels = 0;
            glGetQueryObjectuiv(N->QueryID, GL_QUERY_RESULT, &visiblePixels);
            std::cout << "Visible pixels " << visiblePixels << '\n';
            if ( visiblePixels > 5000 ) {
                PullUpVisibility(N);
                TraverseNode(N);
            }
        }

        if ( !TraversalStack.empty() ) {
            BVH_Node* N = TraversalStack.top();
            TraversalStack.pop();
            if ( N->isInsideFrustrum( ViewDirection ) ) {
                // identify previously visible nodes
                bool wasVisible = N->Visible && (N->LastVisited == FrameID - 1);
                // identify previously opened nodes
                bool opened = wasVisible && !(N->isLeaf());
                // reset node’s visibility classification
                N->Visible = false;
                // update node’s visited flag
                N->LastVisited = FrameID;
                N->ToRender = true;
                // skip testing all previously opened nodes
                if ( !opened ) {
                    IssueOcclusionQuery(N);
                    QueryQueue.push(N);
                }
                // traverse a node unless it was invisible
                if ( wasVisible )
                    TraverseNode(N);
            }
        }

    }
    ++FrameID;
}

bool BVH_ROOT_Node::QueryResultAvailable(BVH_Node* N) {
    unsigned int result = 0;
    glGetQueryObjectuiv(N->QueryID, GL_QUERY_RESULT_AVAILABLE, &result);
    return result;
}

void BVH_ROOT_Node::TraverseNode(BVH_Node* N) {
    if ( N->isLeaf() )
        Render(N);
    else{
        TraversalStack.push(&Hierarchy[N->FirstChild]);
        TraversalStack.push(&Hierarchy[N->FirstChild+1]);
    }
}

void BVH_ROOT_Node::PullUpVisibility(BVH_Node* N) {
    while (!N->Visible && (N->Father != 0 && N->Father != 1)) {
        N->Visible = true;
        N = &Hierarchy[N->Father];
    }
}

void BVH_ROOT_Node::Render(BVH_Node* N) {
    if(N->ToRender) {
        N->Leaf->draw();
        N->ToRender = false;
    }
}

void BVH_ROOT_Node::IssueOcclusionQuery(BVH_Node* N) {
    glm::mat4 VP = projMatrix * viewMatrix;
    glBeginQuery(GL_SAMPLES_PASSED, N->QueryID);
    N->DrawBounding(VP);
    glEndQuery(GL_SAMPLES_PASSED);
}

void BVH_ROOT_Node::beginDraw(){};
void BVH_ROOT_Node::endDraw(){};
