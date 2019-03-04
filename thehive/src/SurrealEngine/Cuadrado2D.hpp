#ifndef CUADRADO2D_H
#define CUADRADO2D_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "TNodo.hpp"

class Cuadrado2D {
    public:
        Cuadrado2D(float x,float y,float w,float h);
        Cuadrado2D(const Cuadrado2D &orig) = delete;
        ~Cuadrado2D();

        void Draw();
        void setPos(float x,float y,float w,float h);

        void setColor(glm::vec4 _color);


    private:
            glm::vec4 color;
            unsigned int VAO;
            unsigned int VBO;
            unsigned int EBO;
};

#endif
