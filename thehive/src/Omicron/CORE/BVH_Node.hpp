#ifndef _BVH_NODE_H
#define _BVH_NODE_H

#include <Omicron/CORE/StandardNode.hpp>
#include <Omicron/ZMESHES/BoundingBox.hpp>
#include <cstdint>
#include <Util.hpp>

class BVH_Node {
    friend class BVH_ROOT_Node;
    public:
        //BVH_Node(uint16_t P);
        BVH_Node(uint16_t P, uint16_t _FirstChild, const BoundingBox &_AABB, StandardNode* _Leaf = nullptr);
        virtual ~BVH_Node();

        virtual bool isLeaf();
        void DrawBounding(const glm::mat4 &VP);
        bool isInsideFrustrum(const glm::vec3 &ViewDirection);

        static void setPlayerPtr(glm::vec3* _PlayerPosition);
        static void setCameraPtr(glm::vec3* _PlayerPosition);

        StandardNode* Leaf;
        Shader* QueryShader;
        static glm::vec3* PlayerPosition;
        static glm::vec3* CameraPosition;


        glm::vec3 CORNERS[4];
        unsigned int QueryID;
        unsigned int VAO_Bounding;
        unsigned int VBO_BoundingVertices;
        unsigned int IndexBuffer;

        uint8_t Father;
        uint8_t FirstChild;
        uint8_t LastVisited;
        bool ToRender;
        bool Visible;

        gg::Color col;
};

#endif
