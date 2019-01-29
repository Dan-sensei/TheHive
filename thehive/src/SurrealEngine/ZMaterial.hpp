#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include <unordered_map>
#include <string>
#include "Shader.hpp"

class ZMaterial{

    public:
        ZMaterial();
        ZMaterial(const ZMaterial& orig) = delete;
        ~ZMaterial();

        void attachShader(Shader* s);
        void addTexture(const std::string &target, const char *path, unsigned int mode, unsigned int flags);
        void setUniformData(const std::string &target, float Data_);
        void Bind();

    private:
        std::unordered_map<unsigned int, int> Textures;
        std::unordered_map<int, float> Data;
        Shader* shader;
};

#endif
