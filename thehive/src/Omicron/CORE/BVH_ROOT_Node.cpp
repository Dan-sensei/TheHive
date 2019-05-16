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

    // std::cout << "BEGINDRAW" << '\n';
    glm::vec2 ViewDirection = glm::vec2(-viewMatrix[0][2], -viewMatrix[2][2]);
    glm::vec2 CameraPos = glm::vec2((*CameraPosition).x, (*CameraPosition).z);
    TraversalStack.push(&Hierarchy[0]);
    while(!TraversalStack.empty() || !QueryQueue.empty()){
        while ( !QueryQueue.empty() && (QueryResultAvailable(QueryQueue.front()) || TraversalStack.empty()) ) {
            BVH_Node* N = QueryQueue.front();
            QueryQueue.pop();

            unsigned int visiblePixels = 0;
            glGetQueryObjectuiv(N->QueryID, GL_QUERY_RESULT, &visiblePixels);
            //std::cout << "VISIBLE PIXELS IN " << N   << " " << visiblePixels << '\n';
            if ( visiblePixels > 15 ) {
                PullUpVisibility(N);
                TraverseNode(N);
            }
        }

        if ( !TraversalStack.empty() ) {
            BVH_Node* N = TraversalStack.top();
            TraversalStack.pop();
            //std::cout << "Node = " << N << '\n';
            if ( N->isInsideFrustrum( CameraPos, ViewDirection ) ) {

                uint8_t PREV_FRAMEID = FrameID - 1;
                //std::cout << "CHECKING NODE " << N << " N->Visible = " << N->Visible << " | N->LastVisited = " << (uint16_t)N->LastVisited << '\n';
                bool wasVisible = N->Visible && (N->LastVisited == PREV_FRAMEID);
                bool opened = wasVisible && !(N->isLeaf());
                N->Visible = false;
                N->LastVisited = FrameID;
                N->ToRender = true;
                if ( !opened ) {
                    if(N->isCameraInside(*CameraPosition)){
                        //std::cout << " --INSIDE" << '\n';
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
    //std::cout << "ENDDRAW" << '\n' << '\n';

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

        float minA = glm::length2(Hierarchy[N->FirstChild].AABB.AABB[0] - LocalCameraPosition);
        for(uint8_t i = 1; i < 8; ++i){
            float corner = glm::length2(Hierarchy[N->FirstChild].AABB.AABB[i] - LocalCameraPosition);
            if(corner < minA){
                minA = corner;
            }
        }

        float minB = glm::length2(Hierarchy[N->FirstChild+1].AABB.AABB[0] - LocalCameraPosition);
        for(uint8_t i = 1; i < 8; ++i){
            float corner = glm::length2(Hierarchy[N->FirstChild+1].AABB.AABB[i] - LocalCameraPosition);
            if(corner < minB){
                minB = corner;
            }
        }

        if(minA < minB){
            //std::cout << &Hierarchy[N->FirstChild] << " -> " << &Hierarchy[N->FirstChild+1] << '\n';
            TraversalStack.push(&Hierarchy[N->FirstChild+1]);
            TraversalStack.push(&Hierarchy[N->FirstChild]);
        }
        else{
            //std::cout << &Hierarchy[N->FirstChild+1] << " -> " << &Hierarchy[N->FirstChild] << '\n';
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
        //std::cout << "DRAW " << N << '\n';
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
