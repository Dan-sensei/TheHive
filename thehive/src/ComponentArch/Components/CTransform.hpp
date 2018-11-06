#ifndef _CTRANSFORM_H
#define _CTRANSFORM_H

#include <ComponentArch/IComponent.hpp>
#include <Util.hpp>

class CTransform : public IComponent {
    public:
        CTransform();
        CTransform(const CTransform &orig);
        virtual ~CTransform();


        //  Functions of IComponent
        static void initComponent();
        virtual void initializeComponentData(const void* data);
        //virtual gg::EMessageStatus processMessage();


        // Functions of this component
        gg::Vector3f getPosition();
        gg::Vector3f getRotation();
        void setPosition(const gg::Vector3f &position);
        void setRotation(const gg::Vector3f &rotation);
        void setScale(const gg::Vector3f &scale);


    private:
        float  x,  y,  z;
        float rx, ry, rz;
        float sx, sy, sz;

};

#endif
