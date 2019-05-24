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

// struct MaterialHelper{
//     MaterialHelper(
//         uint8_t HD = 0, uint8_t ND = 0, uint8_t ED = 0,
//         uint8_t HN = 0, uint8_t NN = 0, uint8_t EN = 0,
//         uint8_t HS = 0, uint8_t NS = 0, uint8_t ES = 0
//     );
//     uint8_t HasDiffuse;
//     uint8_t NameDiffuse;
//     uint8_t ExtensionDiffuse;
//
//     uint8_t HasNormal;
//     uint8_t NameNormal;
//     uint8_t ExtensionNormal;
//
//     uint8_t HasSpecular;
//     uint8_t NameSpecular;
//     uint8_t ExtensionSpecular;
// };
//
// struct Texture{
//     Texture();
//     Texture(unsigned int _TextureID, uint8_t _ZONE);
//     Texture(const Texture &orig);
//
//     unsigned int TextureID;
//     uint8_t ZONE;
// };

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
        void freeTexture(unsigned int Target);

        // void reserveMaterials(uint16_t SIZE);
        // void addMaterial(
        //     uint16_t ID,
        //     uint8_t HD = 0, uint8_t ND = 0, uint8_t ED = 0,
        //     uint8_t HN = 0, uint8_t NN = 0, uint8_t EN = 0,
        //     uint8_t HS = 0, uint8_t NS = 0, uint8_t ES = 0
        // );

    private:

        std::unordered_map<std::string, ZAnimationData>  AnimationMap;
        std::unordered_map<std::string, ZMeshData>       MeshDataMap;
        std::unordered_map<std::string, ZMaterial>       MaterialMap;
        std::unordered_map<std::string, Shader>          ShaderMap;
        std::unordered_map<std::string, unsigned int>         TextureMap;

        std::unordered_map<std::string, unsigned int>    CommonTextures;
        // std::vector<MaterialHelper> MATERIALS;

        AssetManager();
        AssetManager(const AssetManager &orig) = delete;
};

#endif
