#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include <unordered_map>
#include <string>
#include "Shader.hpp"

class ZMaterial{

    public:
        ZMaterial();
        ZMaterial(const ZMaterial& orig);
        ~ZMaterial();

        void attachShader(Shader* s);
        void addTexture(const std::string &ShaderTarget, const std::string &path, unsigned int mode, unsigned int flags);
        void setUniformData(const std::string &ShaderTarget, float Data_);
        void Bind();

        Shader* getShader(){return shader;}

    private:
        std::unordered_map<int, unsigned int> Textures;
        std::unordered_map<int, float> Data;
        Shader* shader;
};

#endif
