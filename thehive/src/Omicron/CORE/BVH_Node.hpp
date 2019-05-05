#ifndef _BVH_NODE_H
#define _BVH_NODE_H

#include <Omicron/CORE/StandardNode.hpp>
#include <Omicron/ZMESHES/BoundingBox.hpp>
#include <cstdint>
#include <Util.hpp>

class BVH_Node {
    friend class BVH_ROOT_Node;
    public:
        BVH_Node(uint16_t P);
        BVH_Node(uint16_t P, uint16_t _FirstChild, const BoundingBox &_AABB, StandardNode* _Leaf = nullptr);
        virtual ~BVH_Node();

        virtual bool isLeaf();
        void DrawBounding(const glm::mat4 &VP);

        StandardNode* Leaf;
        Shader* QueryShader;

        unsigned int QueryID;
        unsigned int VAO_Bounding;
        unsigned int VBO_BoundingVertices;
        unsigned int IndexBuffer;
        
        uint16_t Father;
        uint16_t FirstChild;
        uint8_t LastVisited;
        bool ToRender;
        bool Visible;
        gg::Color col;
};

#endif
