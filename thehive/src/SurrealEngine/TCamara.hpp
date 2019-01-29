#ifndef TCAMARA_H
#define TCAMARA_H

#include "TEntidad.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

class TCamara : public TEntidad {
    public:
        TCamara(float,float,float);
        virtual ~TCamara();

        void changeFov(float);

        void setPerspectiva(float);

        virtual void beginDraw();
        virtual void endDraw();

    private:
        // Matriz perspectiva
        glm::mat4 projection;

        float cercano, lejano, fov;

        // No creo que haga falta este
        // bool porque siempre va a ser
        // de proyeccion perspectiva y
        // nunca va a ser paralela
        // bool perspectiva;

        bool inverted;
};

#endif
