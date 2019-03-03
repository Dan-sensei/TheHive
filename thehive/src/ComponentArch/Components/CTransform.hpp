#ifndef _CTRANSFORM_H
#define _CTRANSFORM_H

#include <Singleton.hpp>
#include <ComponentArch/IComponent.hpp>
#include <Util.hpp>


class CTransform : public IComponent {
    public:
        CTransform(const glm::vec3 &Position, const glm::vec3 &Rotation);
        CTransform(const CTransform &orig);
        virtual ~CTransform();

        //  Functions of IComponent

        // Functions of this component
        glm::vec3 getPosition();
        glm::vec3 getRotation();
        void setPosition(const glm::vec3 &_Position);
        void setRotation(const glm::vec3 &_Rotation);
        void setScale(const glm::vec3 &scale);


    private:
        glm::vec3 Position;
        glm::vec3 Rotation;
};

#endif
