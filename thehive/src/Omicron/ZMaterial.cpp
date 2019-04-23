#include "ZMaterial.hpp"
#include <GL/glew.h>
//#include <iostream>
//#include "vendor/stb_image.h"
#include <Omicron/AssetManager.hpp>
#include <Singleton.hpp>


ZMaterial::ZMaterial()
:shader(nullptr)
{
    Textures[0] = 0;
    Textures[1] = 0;
    Textures[2] = 0;
}

ZMaterial::ZMaterial(const ZMaterial& orig)
{

    Textures[0] = orig.Textures[0];
    Textures[1] = orig.Textures[1];
    Textures[2] = orig.Textures[2];

    // auto it = orig.Data.begin();
    // while(it != orig.Data.end()){
    //     Data[it->first] = it->second;
    //     ++it;
    // }
}

ZMaterial::~ZMaterial(){

}

void ZMaterial::attachShader(Shader *s){
    shader = s;
}

void ZMaterial::addTexture(GN::ShadersIDs ID, const std::string &path){
    unsigned int TextureID = Singleton<AssetManager>::Instance()->getTexture(path);
    Textures[ID] = TextureID;
}

void ZMaterial::Bind(){
    shader->Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, Textures[1]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, Textures[2]);

    //
    // if(Data.size() == 0) return;
    //
    // auto DataIterator = Data.begin();
    // while(DataIterator != Data.end()){
    //     glUniform1f(DataIterator->first, DataIterator->second);
    //     ++DataIterator;
    // }
}
