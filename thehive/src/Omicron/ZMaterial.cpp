#include "ZMaterial.hpp"
#include <GL/glew.h>
//#include <iostream>
//#include "vendor/stb_image.h"
#include <Omicron/AssetManager.hpp>

ZMaterial::ZMaterial()
{
}

ZMaterial::ZMaterial(const ZMaterial& orig)
{
    Textures.reserve(orig.Textures.size());
    for(uint8_t i = 0; i < orig.Textures.size(); ++i)
        Textures[i] = orig.Textures[i];

    auto it = orig.Data.begin();
    while(it != orig.Data.end()){
        Data[it->first] = it->second;
        ++it;
    }
}

ZMaterial::~ZMaterial(){

}

void ZMaterial::attachShader(Shader *s){
    shader = s;
    Textures.clear();
    Data.clear();
}

void ZMaterial::addTexture(GN::ShadersIDs ID, const std::string &path, unsigned int mode, unsigned int flags){
    unsigned int TextureID = Singleton<AssetManager>::Instance()->getTexture(path, mode, flags);
    Textures.emplace_back(std::make_pair(ID, TextureID));
    ////std::cout << "TexureID " << TextureID << '\n';
}

void ZMaterial::setUniformData(const std::string &ShaderTarget, float Data_){
    Data[shader->getUniformLocation(ShaderTarget)] = Data_;
}

void ZMaterial::Bind(){
    shader->Bind();

    for(uint8_t i = 0; i < Textures.size(); ++i){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, Textures[i].second);
        glUniform1i(Textures[i].first, i);
    }

    if(Data.size() == 0) return;

    auto DataIterator = Data.begin();
    while(DataIterator != Data.end()){
        glUniform1f(DataIterator->first, DataIterator->second);
        ++DataIterator;
    }
}

void ZMaterial::clear(){
    Textures.clear();
}
