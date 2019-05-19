#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <map>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

#include <Omicron/ZMESHES/ZMeshData.hpp>
#include <Omicron/ZMESHES/ZAnimationData.hpp>
#include <Omicron/ZMaterial.hpp>
#include <Omicron/OpenGEnum.hpp>

template <typename T>
class Singleton;

class AssetManager {
    friend class Singleton<AssetManager>;
    public:

        ~AssetManager();
        void loadInit();

        ZMeshData*      getMeshData(const std::string &Name);
        ZAnimationData* getAnimation(const std::string &Name);
        ZMaterial*      getMaterial(const std::string &Name);
        unsigned int    getTexture(const std::string &Name, int ForceChannels = 0);
        unsigned int    getConstantTexture(const std::string &Name, int ForceChannels = 0);
        Shader*         getShader(const std::string& Name);

        unsigned int getTextureWithoutSavingToMap(const char* TexturePath, int ForceChannels = 0);
        void freeAssets();
        void freeTexture(unsigned int TextureID);

    private:

        std::unordered_map<std::string, ZAnimationData>  AnimationMap;
        std::unordered_map<std::string, ZMeshData>       MeshDataMap;
        std::unordered_map<std::string, ZMaterial>       MaterialMap;
        std::unordered_map<std::string, Shader>          ShaderMap;
        std::unordered_map<std::string, unsigned int>    TextureMap;

        std::unordered_map<std::string, unsigned int>    CommonTextures;

        AssetManager();
        AssetManager(const AssetManager &orig) = delete;
};

#endif
