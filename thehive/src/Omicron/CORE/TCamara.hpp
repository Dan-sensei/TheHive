#ifndef TCAMARA_H
#define TCAMARA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Util.hpp>
#include <Omicron/CORE/TEntidad.hpp>
//#include <iostream>

class TCamara : public TEntidad {
    public:
        TCamara(float,float,float);
        virtual ~TCamara();

        void changeFov(float);
        void setPerspectiva(float);
        void setTarget(glm::vec3 &t_pos);

        virtual void beginDraw();
        virtual void endDraw();

        inline glm::vec3* getPositionPtr(){ return &CameraPos; };
        //glm::mat4 GetViewMatrix();

    private:
        float cercano, lejano, fov;
        glm::vec3 CameraPos;
        glm::vec3 target;

        bool inverted;
        bool hasTarget;

};

#endif
