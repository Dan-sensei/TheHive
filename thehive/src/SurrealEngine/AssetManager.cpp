#include "AssetManager.hpp"

std::map<std::string, ZMeshData> AssetManager::MeshDataMap;
std::map<std::string, ZMaterial> AssetManager::MaterialMap;

ZMaterial* AssetManager::getMaterial(const std::string &Name) {

    if(MaterialMap.find(Name) != MaterialMap.end())
        return &MaterialMap[Name];
    else {
        ZMaterial* newMat = &MaterialMap[Name];
        newMat->addTexture("DiffuseTextureSampler", "assets/Textures/DefaultDiffuse.jpg",      GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        newMat->addTexture("NormalTextureSampler", "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
        newMat->addTexture("SpecularTextureSampler", "assets/Textures/DefaultSpecular.jpeg",   GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

        return newMat;
    }
}

ZMeshData* AssetManager::getMeshData(const std::string &Name){

    if(MeshDataMap.find(Name) != MeshDataMap.end())
        return &MeshDataMap[Name];
    else{
        MeshDataMap[Name].load(Name);
        return &MeshDataMap[Name];
    }

}
