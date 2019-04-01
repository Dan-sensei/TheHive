#ifndef TTRANSFORM_H
#define TTRANSFORM_H



#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cstdint>

#include <Util.hpp>
#include "TEntidad.hpp"

class TTransform : public TEntidad {
    public:
        TTransform();
        TTransform(glm::mat4);
        virtual ~TTransform();

        void load(glm::mat4);

        void translate(glm::vec3);
        void rotate(float, glm::vec3);
        void scale(glm::vec3);
        void identity();
        void transpose();
        void inverse();

        virtual void beginDraw();
        virtual void endDraw();

        void setPosition(glm::vec3 _vec);
        void setRotation(glm::quat _vec);

        glm::mat4 matrix;
        glm::vec3 getDatos();
    private:
        glm::vec3 datos;

};

#endif
