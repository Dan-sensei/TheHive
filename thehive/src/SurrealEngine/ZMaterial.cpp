#include "ZMaterial.hpp"
#include <iostream>
//#include "vendor/stb_image.h"
#include "AssetManager.hpp"

ZMaterial::ZMaterial()
{
}

ZMaterial::ZMaterial(const ZMaterial& orig){
    std::cout << "Copiando ZMaterial" << '\n';
    auto iterator = orig.Textures.begin();
    while(iterator != orig.Textures.end()){
        Textures[iterator->first] = iterator->second;
        ++iterator;
    }
}

ZMaterial::~ZMaterial(){

}

void ZMaterial::attachShader(Shader *s){
    shader = s;
}

void ZMaterial::addTexture(const std::string &ShaderTarget, const std::string &path, unsigned int mode, unsigned int flags){

    unsigned int TextureID = AssetManager::getTexture(path, mode, flags);
    Textures[shader->getUniformLocation(ShaderTarget)] = TextureID;
    //std::cout << "TexureID " << TextureID << '\n';
}

void ZMaterial::setUniformData(const std::string &ShaderTarget, float Data_){
    Data[shader->getUniformLocation(ShaderTarget)] = Data_;
}

void ZMaterial::Bind(){
    shader->Bind();
    uint8_t i = 0;
    auto iterator = Textures.begin();
    while(iterator != Textures.end()){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, iterator->second);
        glUniform1i(iterator->first, i);
        ++iterator;
        ++i;
    }

    if(Data.size() == 0) return;

    auto DataIterator = Data.begin();
    while(DataIterator != Data.end()){
        glUniform1f(DataIterator->first, DataIterator->second);
        ++DataIterator;
    }
}
