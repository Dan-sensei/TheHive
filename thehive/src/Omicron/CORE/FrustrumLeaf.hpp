#ifndef _FRUSTRUMLEAF_H
#define _FRUSTRUMLEAF_H

#include <Omicron/CORE/ZNode.hpp>
#include <Omicron/CORE/StandardNode.hpp>
#include <Omicron/CORE/TEntidad.hpp>


class FrustrumLeaf : public ZNode, public TEntidad {
    friend class Omicron;

    public:
        FrustrumLeaf();
        FrustrumLeaf(StandardNode* P, TEntidad* Ent);
        FrustrumLeaf(const FrustrumLeaf &orig);
        virtual ~FrustrumLeaf();

        bool isInsideFrustrum(const glm::vec2 &ViewDirection);

        virtual void draw();
        virtual bool isLeaf();

        virtual void beginDraw();
        virtual void endDraw();

        glm::vec2 CORNERS[4];
        int8_t LastFailedFrustrumCorner;

        static glm::vec3* CameraPosition;


};

#endif
