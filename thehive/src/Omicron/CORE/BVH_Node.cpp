#include "BVH_Node.hpp"
#include <Singleton.hpp>
#include <Omicron/AssetManager.hpp>
#include <glm/gtx/normalize_dot.hpp>
#include <Omicron/Omicron.hpp>


// BVH_Node::BVH_Node(uint16_t P)
// :BVH_Node(P, 0, BoundingBox(), nullptr)
// {}

#include <iostream>
#define GRADOVISION 0
int v = 0;
BVH_Node::BVH_Node(uint16_t P, uint16_t _FirstChild, const BoundingBox &_AABB, StandardNode* _Leaf)
:AABB(_AABB), Father(P), FirstChild(_FirstChild), Leaf(_Leaf), LastVisited(0), ToRender(true), Visible(false), LastFailedFrustrumCorner(-1)
{
    glGenQueries(1, &QueryID);

    glGenVertexArrays(1, &VAO_Bounding);



    float cube_strip[] = {
        _AABB.AABB[0].x, _AABB.AABB[0].y, _AABB.AABB[0].z,     // Back-bottom-right
        _AABB.AABB[2].x, _AABB.AABB[2].y, _AABB.AABB[2].z,     // Back-bottom-left
        _AABB.AABB[4].x, _AABB.AABB[4].y, _AABB.AABB[4].z,     // Back-top-left
        _AABB.AABB[5].x, _AABB.AABB[5].y, _AABB.AABB[5].z,     // Back-top-right

        _AABB.AABB[3].x, _AABB.AABB[3].y, _AABB.AABB[3].z,     // Front-bottom-right
        _AABB.AABB[1].x, _AABB.AABB[1].y, _AABB.AABB[1].z,     // Front-bottom-left
        _AABB.AABB[6].x, _AABB.AABB[6].y, _AABB.AABB[6].z,     // Front-top-left
        _AABB.AABB[7].x, _AABB.AABB[7].y, _AABB.AABB[7].z,     // Front-top-right
    };


    CORNERS[0] = glm::vec2(_AABB.AABB[0].x, _AABB.AABB[0].z);
    CORNERS[1] = glm::vec2(_AABB.AABB[1].x, _AABB.AABB[1].z);
    CORNERS[2] = glm::vec2(_AABB.AABB[2].x, _AABB.AABB[2].z);
    CORNERS[3] = glm::vec2(_AABB.AABB[3].x, _AABB.AABB[3].z);

    // if(v == 82){
    //     std::cout << cube_strip[0] << ", "<< cube_strip[1] << ", " << cube_strip[2] << '\n';
    //     std::cout << cube_strip[3] << ", "<< cube_strip[4] << ", " << cube_strip[5] << '\n';
    //     std::cout << cube_strip[6] << ", "<< cube_strip[7] << ", " << cube_strip[8] << '\n';
    //     std::cout << cube_strip[9] << ", "<< cube_strip[10] << ", " << cube_strip[11] << '\n';
    //     std::cout << cube_strip[12] << ", "<< cube_strip[13] << ", " << cube_strip[14] << '\n';
    //     std::cout << cube_strip[15] << ", "<< cube_strip[16] << ", " << cube_strip[17] << '\n';
    //     std::cout << cube_strip[18] << ", "<< cube_strip[19] << ", " << cube_strip[20] << '\n';
    //     std::cout << cube_strip[21] << ", "<< cube_strip[22] << ", " << cube_strip[23] << '\n';
    // }

    Min = _AABB.AABB[0];
    Max = _AABB.AABB[6];

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

    QueryShader = Singleton<AssetManager>::Instance()->getShader("Lines");
    col = gg::Color(gg::genIntRandom(0,255), gg::genIntRandom(0,255), gg::genIntRandom(0,255));
    ++v;
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

    QueryShader->Bind();
    glBindVertexArray(VAO_Bounding);
    glUniformMatrix4fv(1,1,GL_FALSE,&VP[0][0]);
    glUniform3f(2, col.R, col.G, col.B);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);

}

bool BVH_Node::isInsideFrustrum(const glm::vec2 &CameraPosition, const glm::vec2 &ViewDirection){

    //frustrum
    glm::vec2 dirobj;

    if(LastFailedFrustrumCorner != -1){
        dirobj = CORNERS[LastFailedFrustrumCorner] - CameraPosition;
        float sol         = glm::fastNormalizeDot(dirobj, ViewDirection);
        if(GRADOVISION < sol) {
            return true;
        }
    }

    for (uint8_t i = 0; i < 4; ++i) {
        if(i == LastFailedFrustrumCorner) continue;

        dirobj = CORNERS[i] - CameraPosition;
        float sol         = glm::fastNormalizeDot(dirobj, ViewDirection);
        if(GRADOVISION < sol) {
            LastFailedFrustrumCorner = i;
            return true;
        }
    }

    LastFailedFrustrumCorner = -1;
    return false;
}


bool BVH_Node::isCameraInside(const glm::vec3 CameraPos) {
    if(CameraPos.x >= Min.x && CameraPos.x <= Max.x  && CameraPos.y >= Min.y && CameraPos.y <= Max.y && CameraPos.z < Min.z && CameraPos.z > Max.z){
        return true;
    }
    return false;
}

