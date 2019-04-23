#ifndef MATERIAL_H
#define MATERIAL_H

#include <unordered_map>
#include <string>
#include "Shader.hpp"
#include <Omicron/OpenGEnum.hpp>

class ZMaterial{

    public:
        ZMaterial();
        ZMaterial(const ZMaterial& orig);
        ~ZMaterial();

        void attachShader(Shader* s);
        void addTexture(GN::ShadersIDs ID, const unsigned int &TextureID);
        void Bind();

        inline Shader* getShader(){ return shader; };

    private:
        unsigned int Textures[3];
        //std::unordered_map<int, float> Data;
        Shader* shader;
};

#endif
