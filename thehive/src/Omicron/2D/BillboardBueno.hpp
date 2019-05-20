#ifndef BILLBOARDBUENO_H
#define BILLBOARDBUENO_H

#include <vector>
#include <cstdint>
#include <string>
#include <glm/glm.hpp>
#include <Omicron/CORE/TEntidad.hpp>

class Omicron;
class Shader;

class BillboardBueno  : public TEntidad {
    public:
        //BillboardBueno();
        BillboardBueno(float x,float y,float z,const std::string &Name);

        BillboardBueno(const BillboardBueno &orig) = delete;
        ~BillboardBueno();

        void Draw();
        //void init();
        void setPos(float x,float y,float z);
        void setImage(const std::string &Name);

        float getX();
        float getW();
        float getY();
        float getH();

        virtual void beginDraw();
        virtual void endDraw();

    private:
            Shader* inicio;
            Omicron* engine;
            glm::vec3 centro;
            unsigned int VAO;
            unsigned int VBO;
            unsigned int EBO;
            unsigned int textureID;
            float X,Y,W,H;

};

#endif
