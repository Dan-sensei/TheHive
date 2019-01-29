#include "ZMaterial.hpp"
#include <iostream>
//#include "vendor/stb_image.h"
#include <SOIL2/SOIL2.h>

ZMaterial::ZMaterial()
{
}

// ZMaterial::ZMaterial(const ZMaterial& orig){
//     std::cout << "Copiando ZMaterial" << '\n';
//     auto iterator = orig.Textures.begin();
//     while(iterator != orig.Textures.end()){
//         Textures[iterator->first] = iterator->second;
//         ++iterator;
//     }
// }

ZMaterial::~ZMaterial(){
    std::cout << "Deleting textures..." << '\n';
    auto iterator = Textures.begin();
    while(iterator != Textures.end()){
        glDeleteTextures(1, &iterator->first);
        ++iterator;
    }
}

void ZMaterial::attachShader(Shader *s){
    shader = s;
}

void ZMaterial::addTexture(const std::string &target, const char *path, unsigned int mode, unsigned int flags){

    unsigned int TextureID = SOIL_load_OGL_texture(path, mode, SOIL_CREATE_NEW_ID, flags );
    Textures[TextureID] = shader->getUniformLocation(target);
    //std::cout << "TexureID " << TextureID << '\n';
}

void ZMaterial::setUniformData(const std::string &target, float Data_){
    Data[shader->getUniformLocation(target)] = Data_;
}

void ZMaterial::Bind(){
    shader->Bind();
    uint8_t i = 0;
    auto iterator = Textures.begin();
    while(iterator != Textures.end()){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, iterator->first);
        glUniform1i(iterator->second, i);
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
