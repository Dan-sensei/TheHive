#include "BVH_Node.hpp"
#include <Singleton.hpp>
#include <Omicron/AssetManager.hpp>

BVH_Node::BVH_Node(uint16_t P)
:BVH_Node(P, 0, BoundingBox(), nullptr)
{}

#include <iostream>
int v = 0;
BVH_Node::BVH_Node(uint16_t P, uint16_t _FirstChild, const BoundingBox &_AABB, StandardNode* _Leaf)
:Father(P), FirstChild(_FirstChild), Leaf(_Leaf), LastVisited(0), ToRender(true), Visible(false)
{
    glGenQueries(1, &QueryID);

    glGenVertexArrays(1, &VAO_Bounding);
    //vec3(-12.845795, 1.565783, 11.663330)

        static const GLfloat cube_strip0[] = {
            -1.f, 1.f, 1.f,     // Front-top-left
            1.f, 1.f, 1.f,      // Front-top-right
            -1.f, -1.f, 1.f,    // Front-bottom-left
            1.f, -1.f, 1.f,     // Front-bottom-right
            1.f, -1.f, -1.f,    // Back-bottom-right
            1.f, 1.f, 1.f,      // Front-top-right
            1.f, 1.f, -1.f,     // Back-top-right
            -1.f, 1.f, 1.f,     // Front-top-left
            -1.f, 1.f, -1.f,    // Back-top-left
            -1.f, -1.f, 1.f,    // Front-bottom-left
            -1.f, -1.f, -1.f,   // Back-bottom-left
            1.f, -1.f, -1.f,    // Back-bottom-right
            -1.f, 1.f, -1.f,    // Back-top-left
            1.f, 1.f, -1.f      // Back-top-right
        };
        static const GLfloat cube_strip2[] = {
            -1.f, -1.f, 1.f,    // Front-bottom-left
            1.f, -1.f, 1.f,     // Front-bottom-right
            1.f, 1.f, 1.f,      // Front-top-right
            -1.f, 1.f, 1.f,     // Front-top-left
            -1.f, 1.f, -1.f,    // Back-top-left
            1.f, 1.f, -1.f,     // Back-top-right
            1.f, -1.f, -1.f,    // Back-bottom-right
            -1.f, -1.f, -1.f,   // Back-bottom-left
        };

    // static const GLfloat cube_strip[] = {
    //     _AABB.ULF.x, _AABB.ULF.y, _AABB.ULF.z,     // Front-top-left
    //     _AABB.URF.x, _AABB.URF.y, _AABB.URF.z,     // Front-top-right
    //     _AABB.BLF.x, _AABB.BLF.y, _AABB.BLF.z,     // Front-bottom-left
    //     _AABB.BRF.x, _AABB.BRF.y, _AABB.BRF.z,     // Front-bottom-right
    //     _AABB.BRB.x, _AABB.BRB.y, _AABB.BRB.z,     // Back-bottom-right
    //     _AABB.URF.x, _AABB.URF.y, _AABB.URF.z,     // Front-top-right
    //     _AABB.URB.x, _AABB.URB.y, _AABB.URB.z,     // Back-top-right
    //     _AABB.ULF.x, _AABB.ULF.y, _AABB.ULF.z,     // Front-top-left
    //     _AABB.ULB.x, _AABB.ULB.y, _AABB.ULB.z,     // Back-top-left
    //     _AABB.BLF.x, _AABB.BLF.y, _AABB.BLF.z,     // Front-bottom-left
    //     _AABB.BLB.x, _AABB.BLB.y, _AABB.BLB.z,     // Back-bottom-left
    //     _AABB.BRB.x, _AABB.BRB.y, _AABB.BRB.z,     // Back-bottom-right
    //     _AABB.ULB.x, _AABB.ULB.y, _AABB.ULB.z,     // Back-top-left
    //     _AABB.URB.x, _AABB.URB.y, _AABB.URB.z      // Back-top-right
    // };
    static const float cube_strip[] = {
        _AABB.BLF.x, _AABB.BLF.y, _AABB.BLF.z,     // Front-bottom-left
        _AABB.BRF.x, _AABB.BRF.y, _AABB.BRF.z,     // Front-bottom-right
        _AABB.URF.x, _AABB.URF.y, _AABB.URF.z,     // Front-top-right
        _AABB.ULF.x, _AABB.ULF.y, _AABB.ULF.z,     // Front-top-left
        _AABB.ULB.x, _AABB.ULB.y, _AABB.ULB.z,     // Back-top-left
        _AABB.URB.x, _AABB.URB.y, _AABB.URB.z,     // Back-top-right
        _AABB.BRB.x, _AABB.BRB.y, _AABB.BRB.z,     // Back-bottom-right
        _AABB.BLB.x, _AABB.BLB.y, _AABB.BLB.z,     // Back-bottom-left
    };

    uint16_t indices []=
    {
        0,  1,  2,  0,  2,  3,  //front
        2,  5,  6,  2,  6,  1,  //right
        7,  6,  5,  7,  5,  4,  //back
        7,  0,  3,  7,  3,  4,  //left
        2,  3,  4,  2,  4,  5,  //upper
        7,  6,  1,  7,  1,  0   //bottom
    };

    // if(v == 0 || v == 81){
    //     std::cout << v << ". ULF " << _AABB.ULF.x << ", " << _AABB.ULF.y << ", " << _AABB.ULF.z << '\n';
    //     std::cout << "    URF " << _AABB.URF.x << ", " << _AABB.URF.y << ", " << _AABB.URF.z << '\n';
    //     std::cout << "    BLF " << _AABB.BLF.x << ", " << _AABB.BLF.y << ", " << _AABB.BLF.z << '\n';
    //     std::cout << "    BRF " << _AABB.BRF.x << ", " << _AABB.BRF.y << ", " << _AABB.BRF.z << '\n';
    //     std::cout << "    ULB " << _AABB.ULB.x << ", " << _AABB.ULB.y << ", " << _AABB.ULB.z << '\n';
    //     std::cout << "    URB " << _AABB.URB.x << ", " << _AABB.URB.y << ", " << _AABB.URB.z << '\n';
    //     std::cout << "    BLB " << _AABB.BLB.x << ", " << _AABB.BLB.y << ", " << _AABB.BLB.z << '\n';
    //     std::cout << "    BRB " << _AABB.BRB.x << ", " << _AABB.BRB.y << ", " << _AABB.BRB.z << '\n';
    // }
    if(v == 81){
        std::cout << _AABB.BLF.x << ", " << _AABB.BLF.y << ", " << _AABB.BLF.z << '\n';
        std::cout << _AABB.BRF.x << ", " << _AABB.BRF.y << ", " << _AABB.BRF.z << '\n';
        std::cout << _AABB.URF.x << ", " << _AABB.URF.y << ", " << _AABB.URF.z << '\n';
        std::cout << _AABB.ULF.x << ", " << _AABB.ULF.y << ", " << _AABB.ULF.z << '\n';
        std::cout << _AABB.ULB.x << ", " << _AABB.ULB.y << ", " << _AABB.ULB.z << '\n';
        std::cout << _AABB.URB.x << ", " << _AABB.URB.y << ", " << _AABB.URB.z << '\n';
        std::cout << _AABB.BRB.x << ", " << _AABB.BRB.y << ", " << _AABB.BRB.z << '\n';
        std::cout << _AABB.BLB.x << ", " << _AABB.BLB.y << ", " << _AABB.BLB.z << '\n';
    }

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
    v++;
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
