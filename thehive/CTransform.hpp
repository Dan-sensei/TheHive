#ifndef _CTRANSFORM_H
#define _CTRANSFORM_H

#include "IComponent.hpp"
#include "Util.hpp"

class CTransform : public IComponent {
    public:
        CTransform();
        CTransform(const CTransform &orig);
        virtual ~CTransform();

        static void initComponent();

        gg::Vector3f getPosition();

        void setPosition(const gg::Vector3f &position);
        void setRotation(const gg::Vector3f &rotation);
        void setScale(const gg::Vector3f &scale);

        //virtual gg::EMessageStatus processMessage();

    private:
        float  x,  y,  z;
        float rx, ry, rz;
        float sx, sy, sz;

};

#endif
