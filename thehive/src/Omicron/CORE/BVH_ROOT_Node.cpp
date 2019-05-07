#include "BVH_ROOT_Node.hpp"
#include <glm/gtx/norm.hpp>

glm::vec3* BVH_ROOT_Node::CameraPosition;


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
// #include <Singleton.hpp>
// #include <Omicron/Omicron.hpp>
#include <iostream>

void BVH_ROOT_Node::draw(){
    // Coherent Hierarchical Culling
    glm::vec3 ViewDirection = glm::vec3(-viewMatrix[0][2], 0, -viewMatrix[2][2]);
    TraversalStack.push(&Hierarchy[0]);
    while(!TraversalStack.empty() || !QueryQueue.empty()){
        while ( !QueryQueue.empty() && (QueryResultAvailable(QueryQueue.front()) || TraversalStack.empty()) ) {
            BVH_Node* N = QueryQueue.front();
            QueryQueue.pop();

            unsigned int visiblePixels = 0;
            glGetQueryObjectuiv(N->QueryID, GL_QUERY_RESULT, &visiblePixels);
            if ( visiblePixels > 15 ) {
                PullUpVisibility(N);
                TraverseNode(N);
            }
        }

        if ( !TraversalStack.empty() ) {
            BVH_Node* N = TraversalStack.top();
            TraversalStack.pop();
            if ( N->isInsideFrustrum( ViewDirection ) ) {

                bool wasVisible = N->Visible && (N->LastVisited == FrameID - 1);
                bool opened = wasVisible && !(N->isLeaf());
                N->Visible = false;
                N->LastVisited = FrameID;
                N->ToRender = true;
                if ( !opened ) {
                    if(N->isCameraInside()){
                        PullUpVisibility(N);
                        TraverseNode(N);
                    }
                    else{
                        IssueOcclusionQuery(N);
                        QueryQueue.push(N);
                    }
                }

                if ( wasVisible )
                    TraverseNode(N);
            }
        }
    }
    ++FrameID;

    // glm::mat4 VP = projMatrix * viewMatrix;
    // for(uint8_t i = 0; i < Hierarchy.size(); ++i){
    //     if(Hierarchy[i].isLeaf())
    //         Hierarchy[i].DrawBounding(VP);
    // }
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
        glm::vec3 LocalCameraPosition = *CameraPosition;

        float minA = glm::length2(Hierarchy[N->FirstChild].CORNERS[0] - LocalCameraPosition);
        for(uint8_t i = 1; i < 4; ++i){
            float corner = glm::length2(Hierarchy[N->FirstChild].CORNERS[i] - LocalCameraPosition);
            if(corner < minA){
                minA = corner;
            }
        }

        float minB = glm::length2(Hierarchy[N->FirstChild+1].CORNERS[0] - LocalCameraPosition);
        for(uint8_t i = 1; i < 4; ++i){
            float corner = glm::length2(Hierarchy[N->FirstChild+1].CORNERS[i] - LocalCameraPosition);
            if(corner < minB){
                minB = corner;
            }
        }

        if(minA < minB){
            TraversalStack.push(&Hierarchy[N->FirstChild+1]);
            TraversalStack.push(&Hierarchy[N->FirstChild]);
        }
        else{
            TraversalStack.push(&Hierarchy[N->FirstChild]);
            TraversalStack.push(&Hierarchy[N->FirstChild+1]);
        }
    }
}

void BVH_ROOT_Node::PullUpVisibility(BVH_Node* N) {
    while (!N->Visible) {
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
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);

    glBeginQuery(GL_SAMPLES_PASSED, N->QueryID);
    N->DrawBounding(VP);
    glEndQuery(GL_SAMPLES_PASSED);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
}

void BVH_ROOT_Node::beginDraw(){};
void BVH_ROOT_Node::endDraw(){};

void BVH_ROOT_Node::setCameraPtr(glm::vec3* _PlayerPosition){
    CameraPosition = _PlayerPosition;
}
