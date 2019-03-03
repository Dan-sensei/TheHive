#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <cstdint>

#include <Util.hpp>
#include "TEntidad.hpp"

class TTransform : public TEntidad {
    public:
        TTransform();
        TTransform(glm::mat4);
        virtual ~TTransform();

        void load(glm::mat4);

        void translate(gg::Vector3f);
        void rotate(float, gg::Vector3f);
        void scale(gg::Vector3f);
        void identity();
        void transpose();
        void inverse();

        virtual void beginDraw(const uint8_t&);
        virtual void endDraw(const uint8_t&);

        void setPosition(gg::Vector3f _vec);
        void setRotation(gg::Vector3f _vec);

        glm::mat4 matrix;
        glm::vec3 getDatos();
    private:
        glm::vec3 datos;

};

#endif
