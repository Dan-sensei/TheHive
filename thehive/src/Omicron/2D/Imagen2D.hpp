#ifndef IMAGEN2D_H
#define IMAGEN2D_H

#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

class Shader;
class Imagen2D {
    public:
        //Imagen2D();
        Imagen2D(float x,float y,float w,float h, unsigned int _TextureID);

        Imagen2D(const Imagen2D &orig);
        ~Imagen2D();
        void setZindex(float res);
        void Draw();
        //void init();
        void setPos(float x,float y,float w,float h);
        void setImage(unsigned int _TexureID);
        unsigned int getImage();

        float getX();
        float getW();
        float getY();
        float getH();
        void setSesgado(float res);
        void setShader(Shader* S);

    private:
        Shader* inicio;

        float index;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        unsigned int textureID;
        float X,Y,W,H;

};

#endif
