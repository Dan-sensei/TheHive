#ifndef _CTRANSFORM_H
#define _CTRANSFORM_H

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>
#include <Util.hpp>


class CTransform : public IComponent {
    public:
        CTransform(const gg::Vector3f &Position, const gg::Vector3f &Rotation);
        CTransform(const CTransform &orig);
        virtual ~CTransform();

        //  Functions of IComponent

        // Functions of this component
        gg::Vector3f getPosition();
        gg::Vector3f getRotation();
        void setPosition(const gg::Vector3f &_Position);
        void setRotation(const gg::Vector3f &_Rotation);
        void setScale(const gg::Vector3f &scale);


    private:
        gg::Vector3f Position;
        gg::Vector3f Rotation;
};

#endif
