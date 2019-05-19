#ifndef TLUZ_H
#define TLUZ_H

#include <Util.hpp>
#include <Omicron/CORE/TEntidad.hpp>
#include <Omicron/Shader.hpp>

class TLuz : public TEntidad {
    public:
        static unsigned char * buffer;
        TLuz();
        TLuz(const glm::vec3 &_color);//,unsigned char * buff);
        TLuz(Shader*);
        TLuz(const glm::vec3 &_color, Shader*);
        virtual ~TLuz ();

        virtual void setColor(const glm::vec3 &_color);
        virtual glm::vec3 getColor();

        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;

        void  setIntensidad(float &_color);
        float getIntensidad();
        void setN(int ene);

    protected:
        glm::vec3 Color;
        Shader* light_shader;
        float intensidad;
        int N;

};

#endif
