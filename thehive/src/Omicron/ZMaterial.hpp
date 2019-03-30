#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include <unordered_map>
#include <string>
#include "Shader.hpp"
#include "OpenGEnum.hpp"

class ZMaterial{

    public:
        ZMaterial();
        ZMaterial(const ZMaterial& orig);
        ~ZMaterial();

        void attachShader(Shader* s);
        void addTexture(GN::ShadersIDs ID, const std::string &path, unsigned int mode = 0, unsigned int flags = 0);
        void setUniformData(const std::string &ShaderTarget, float Data_);
        void Bind();
        void clear();

        inline Shader* getShader(){ return shader; };

    private:
        std::vector<std::pair<int, unsigned int>> Textures;
        std::unordered_map<int, float> Data;
        Shader* shader;
};

#endif
