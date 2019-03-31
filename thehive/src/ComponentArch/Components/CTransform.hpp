#ifndef _CTRANSFORM_H
#define _CTRANSFORM_H

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>
#include <Util.hpp>
#include <glm/gtx/quaternion.hpp>


class CTransform : public IComponent {
    friend class Factory;
    public:
        CTransform(const glm::vec3 &Position, const glm::quat &Rotation);
        CTransform(const CTransform &orig);
        virtual ~CTransform();

        //  Functions of IComponent

        // Functions of this component
        glm::vec3 getPosition();
        glm::quat getRotation();
        void setPosition(const glm::vec3 &_Position);
        void setRotation(const glm::quat &_Rotation);
        glm::quat rotate(const float &Angle_RADs, const glm::vec3 &Axis);
        void setScale(const glm::vec3 &scale);


    private:
        glm::vec3 Position;
        glm::quat Rotation;
};

#endif
