#include "BVH_Node.hpp"
#include <Singleton.hpp>
#include <Omicron/AssetManager.hpp>
#include <glm/gtx/normalize_dot.hpp>
#include <Omicron/Omicron.hpp>

glm::vec3* BVH_Node::PlayerPosition;
glm::vec3* BVH_Node::CameraPosition;

// BVH_Node::BVH_Node(uint16_t P)
// :BVH_Node(P, 0, BoundingBox(), nullptr)
// {}

#include <iostream>
#define GRADOVISION -0.17364817766

BVH_Node::BVH_Node(uint16_t P, uint16_t _FirstChild, const BoundingBox &_AABB, StandardNode* _Leaf)
:Father(P), FirstChild(_FirstChild), Leaf(_Leaf), LastVisited(0), ToRender(true), Visible(false)
{
    glGenQueries(1, &QueryID);

    glGenVertexArrays(1, &VAO_Bounding);

    float cube_strip[] = {
        _AABB.BRB.x, _AABB.BRB.y, _AABB.BRB.z,     // Back-bottom-right
        _AABB.BLB.x, _AABB.BLB.y, _AABB.BLB.z,     // Back-bottom-left
        _AABB.ULB.x, _AABB.ULB.y, _AABB.ULB.z,     // Back-top-left
        _AABB.URB.x, _AABB.URB.y, _AABB.URB.z,     // Back-top-right

        _AABB.BRF.x, _AABB.BRF.y, _AABB.BRF.z,     // Front-bottom-right
        _AABB.BLF.x, _AABB.BLF.y, _AABB.BLF.z,     // Front-bottom-left
        _AABB.ULF.x, _AABB.ULF.y, _AABB.ULF.z,     // Front-top-left
        _AABB.URF.x, _AABB.URF.y, _AABB.URF.z,     // Front-top-right
    };

    CORNERS[0] = _AABB.BRB;
    CORNERS[1] = _AABB.BLB;
    CORNERS[2] = _AABB.BRF;
    CORNERS[3] = _AABB.BLF;

    // if(v == 0 || v == 81){
    //     std::cout << cube_strip[0] << ", "<< cube_strip[1] << ", " << cube_strip[2] << '\n';
    //     std::cout << cube_strip[3] << ", "<< cube_strip[4] << ", " << cube_strip[5] << '\n';
    //     std::cout << cube_strip[6] << ", "<< cube_strip[7] << ", " << cube_strip[8] << '\n';
    //     std::cout << cube_strip[9] << ", "<< cube_strip[10] << ", " << cube_strip[11] << '\n';
    //     std::cout << cube_strip[12] << ", "<< cube_strip[13] << ", " << cube_strip[14] << '\n';
    //     std::cout << cube_strip[15] << ", "<< cube_strip[16] << ", " << cube_strip[17] << '\n';
    //     std::cout << cube_strip[18] << ", "<< cube_strip[19] << ", " << cube_strip[20] << '\n';
    //     std::cout << cube_strip[21] << ", "<< cube_strip[22] << ", " << cube_strip[23] << '\n';
    // }


    uint16_t indices []=
    {
		0, 1, 2, 2, 3, 0,
		1, 5, 6, 6, 2, 1,
		7, 6, 5, 5, 4, 7,
		4, 0, 3, 3, 7, 4,
		4, 5, 1, 1, 0, 4,
		3, 2, 6, 6, 7, 3
    };

    glBindVertexArray(VAO_Bounding);

        glEnableVertexAttribArray(0);
        glGenBuffers(1, &VBO_BoundingVertices);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_BoundingVertices);

        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_strip), cube_strip, GL_STATIC_DRAW);

        glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
        glVertexAttribBinding(0, 0);
        glBindVertexBuffer(0, VBO_BoundingVertices, 0, 12);

        glGenBuffers(1, &IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    QueryShader = Singleton<AssetManager>::Instance()->getShader("Query");
    col = gg::Color(gg::genIntRandom(0,255), gg::genIntRandom(0,255), gg::genIntRandom(0,255));
}

bool BVH_Node::isLeaf(){
    return Leaf;
};

BVH_Node::~BVH_Node(){
    delete Leaf;
    glDeleteQueries(1, &QueryID);
    glDeleteVertexArrays(1, &VAO_Bounding);
    glDeleteBuffers(1, &VBO_BoundingVertices);
    glDeleteBuffers(1, &IndexBuffer);
}

void BVH_Node::DrawBounding(const glm::mat4 &VP){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);
    QueryShader->Bind();
    glBindVertexArray(VAO_Bounding);
    glUniformMatrix4fv(1,1,GL_FALSE,&VP[0][0]);
    glUniform3f(2, col.R, col.G, col.B);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
    Singleton<Omicron>::Instance()->Bind_G_Buffer();
    glDepthMask(GL_TRUE);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

bool BVH_Node::isInsideFrustrum(const glm::vec3 &ViewDirection){

    //frustrum
    glm::vec3 dirobj;
    glm::vec3 campos = *CameraPosition;

    for (uint8_t i = 0; i < 4; ++i) {
        dirobj = CORNERS[i] - campos;
        dirobj.y = 0;
        float sol         = glm::fastNormalizeDot(dirobj, ViewDirection);
        if(GRADOVISION < sol) {
            return true;
        }
    }

    return false;
}


void BVH_Node::setPlayerPtr(glm::vec3* _PlayerPosition){
    PlayerPosition = _PlayerPosition;
}

void BVH_Node::setCameraPtr(glm::vec3* _PlayerPosition){
    CameraPosition = _PlayerPosition;
}
