#ifndef TEXTO2D_H
#define TEXTO2D_H

#include <vector>
#include <cstdint>
#include <iostream>
#include <string>
#include <glm/glm.hpp>

class Letra2DManager;
class Shader;

class Texto2D {
    public:
        Texto2D();
        Texto2D(const Texto2D &orig);
        Texto2D& operator=(Texto2D other);

        Texto2D(float x,float y,float w,float h,const std::string &Name,glm::vec4 _color=glm::vec4(1,0,0,1),float tam=20);
        Texto2D(float x,float y, const std::string &Palabra, glm::vec4 _color=glm::vec4(1,0,0,1), float tam = 20);
        void getSize(float &_w,float &_h);
        float getSizeX();
        float getSizeY();

        ~Texto2D();

        void Draw();
        //void init();
        void setPos(float x,float y);
        void setImage(const std::string &Name);
        void setText(std::string pal);

        void setColor(glm::vec4 _color);
        float getX();
        float getW();
        float getY();
        float getH();
        Letra2DManager* Manager;
        void ChangeChar(float &incx,const char &cha);

        float  getWid(char car);

        void printString();


    private:
        Shader* inicio;
        float index;
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
