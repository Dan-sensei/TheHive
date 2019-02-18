#ifndef TCAMARA_H
#define TCAMARA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Util.hpp>
#include "TEntidad.hpp"
#include <iostream>

class TCamara : public TEntidad {
    public:
        TCamara(float,float,float);
        virtual ~TCamara();

        void changeFov(float);
        void setPerspectiva(float);

        virtual void beginDraw();
        virtual void endDraw();

    private:
        float cercano, lejano, fov;
        glm::vec3 target;

        bool inverted;

};

#endif
