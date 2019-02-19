#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>


std::unordered_map<std::string, ZMeshData> AssetManager::MeshDataMap;
std::unordered_map<std::string, ZMaterial> AssetManager::MaterialMap;
std::unordered_map<std::string, Shader> AssetManager::ShaderMap;
std::unordered_map<std::string, unsigned int> AssetManager::TextureMap;

AssetManager::AssetManager(){
    ShaderMap["Default"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
}

ZMaterial* AssetManager::getMaterial(const std::string &Name) {

    auto it = MaterialMap.find(Name);
    if(it != MaterialMap.end())
        return &it->second;
    else {
        ZMaterial* newMat = &MaterialMap[Name];
        newMat->attachShader(&ShaderMap["Default"]);
        newMat->addTexture("DiffuseTextureSampler", "assets/Textures/DefaultDiffuse.jpg",      GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        newMat->addTexture("NormalTextureSampler", "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        newMat->addTexture("SpecularTextureSampler", "assets/Textures/DefaultSpecular.jpeg",   GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

        return newMat;
    }
}

ZMeshData* AssetManager::getMeshData(const std::string &Name){

    auto it = MeshDataMap.find(Name);
    if(it != MeshDataMap.end())
        return &it->second;
    else{
        MeshDataMap[Name].load(Name);
        return &MeshDataMap[Name];
    }

}

Shader* AssetManager::getShader(const std::string &Name) {

    auto it = ShaderMap.find(Name);
    if(it != ShaderMap.end())
        return &it->second;
    else{
        std::cout << "  --No existe ningún Shader llamado '" << Name <<"', devolviendo 'Default'..." << '\n';
        return &ShaderMap["Default"];
    }

}

Shader* AssetManager::createShader(std::string Name) {
    if(ShaderMap.find(Name) == ShaderMap.end())
        ShaderMap[Name];
    else
        std::cout << "  --Ya hay un shader con ese nombre" << '\n';

    return &ShaderMap[Name];
}

unsigned int AssetManager::getTexture(const std::string &Name, unsigned int mode, unsigned int flags){
    if(TextureMap.find(Name) != TextureMap.end()){
        return TextureMap[Name];
    }
    else {
        unsigned int NewID = SOIL_load_OGL_texture(Name.c_str(), mode, SOIL_CREATE_NEW_ID, flags );
        TextureMap.insert(std::make_pair(Name, NewID));
        return NewID;
    }
}

AssetManager::~AssetManager(){
    std::cout << "Deleting textures..." << '\n';
    auto iterator = TextureMap.begin();
    while(iterator != TextureMap.end()){
        glDeleteTextures(1, &iterator->second);
        ++iterator;
    }
}
