#ifndef _BVH_NODE_H
#define _BVH_NODE_H

#include <Omicron/CORE/StandardNode.hpp>
#include <Omicron/ZMESHES/BoundingBox.hpp>
#include <Omicron/ZMESHES/ZMesh.hpp>
#include <cstdint>
#include <Util.hpp>

class BVH_Node {
    friend class BVH_ROOT_Node;
    public:
        //BVH_Node(uint16_t P);
        BVH_Node(uint16_t P, uint16_t _FirstChild, const BoundingBox &_AABB, StandardNode* _Leaf = nullptr);
        BVH_Node(const BVH_Node &orig);
        virtual ~BVH_Node();

        virtual bool isLeaf();
        void DrawBounding(const glm::mat4 &VP);
        bool isInsideFrustrum(const glm::vec2 &CameraPosition, const glm::vec2 &ViewDirection);
        bool isCameraInside(const glm::vec3 CameraPos);

        StandardNode* Leaf;
        Shader* QueryShader;

        glm::vec3 Min;
        glm::vec3 Max;

        BoundingBox AABB;
        glm::vec2 CORNERS[4];
        unsigned int QueryID;
        unsigned int VAO_Bounding;
        unsigned int VBO_BoundingVertices;
        unsigned int IndexBuffer;

        uint8_t Father;
        uint8_t FirstChild;
        uint8_t LastVisited;
        bool ToRender;
        bool Visible;
        int8_t LastFailedFrustrumCorner;

        //gg::Color col;
};

#endif
