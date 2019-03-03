#ifndef IMAGEN2D_H
#define IMAGEN2D_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "TNodo.hpp"

class Imagen2D {
    public:
        //Imagen2D();
        Imagen2D(float x,float y,float w,float h,const std::string &Name);

        Imagen2D(const Imagen2D &orig) = delete;
        ~Imagen2D();

        void Draw();
        //void init();
        void setPos(float x,float y,float w,float h);
        void setImage(const std::string &Name);

        void setColor(glm::vec4 _color);
        float getX();
        float getW();
        float getY();
        float getH();





    private:
            glm::vec4 color;
            unsigned int VAO;
            unsigned int VBO;
            unsigned int EBO;
            unsigned int textureID;
            float X,Y,W,H;

};

#endif
