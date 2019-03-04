#ifndef TEXTO2D_H
#define TEXTO2D_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "TNodo.hpp"

class Letra2DManager;
class Texto2D {
    public:
        //Texto2D();
        Texto2D(float x,float y,float w,float h,const std::string &Name);
        Texto2D(float x,float y,float w,float h,const std::string &Name,float tam=0.1);
        void getSize(float &_w,float &_h);
        float getSizeX();
        float getSizeY();

        Texto2D(const Texto2D &orig) = delete;
        ~Texto2D();

        void Draw();
        //void init();
        void setPos(float x,float y);
        void setImage(const std::string &Name);

        void setColor(glm::vec4 _color);
        float getX();
        float getW();
        float getY();
        float getH();
        Letra2DManager* Manager;
        float ChangeChar(float x,float y,char cha);

        float  getWid(char car);




    private:
            std::string palabra;
            glm::vec4 color;
            unsigned int VAO;
            unsigned int VBO;
            unsigned int EBO;
            unsigned int textureID;
            float X,Y,W,H;
            float separacion;
            float tamanyo;

};

#endif
