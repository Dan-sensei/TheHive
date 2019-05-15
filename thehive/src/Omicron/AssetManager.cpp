#include "AssetManager.hpp"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

AssetManager::AssetManager(){
    ShaderMap["Nature"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Default"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Lines"].loadFiles("assets/Shaders/Line_VS.glsl", nullptr, "assets/Shaders/Line_FS.glsl");
    ShaderMap["2D"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["2D_im"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2D_sinD.glsl");
    ShaderMap["Bill"].loadFiles("assets/Shaders/VertexShaderBillboard.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Blend"].loadFiles("assets/Shaders/VertexShaderblend.glsl", nullptr, "assets/Shaders/FragmentShaderblend.glsl");
    ShaderMap["Plano"].loadFiles("assets/Shaders/VertexShader2DPlano.glsl", nullptr, "assets/Shaders/FragmentShader2DPlano.glsl");
    ShaderMap["skyboxShader"].loadFiles("assets/Shaders/SkyBox.vs", nullptr, "assets/Shaders/SkyBox.frag");
    ShaderMap["AnimationShader"].loadFiles("assets/Shaders/Animation.vs", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Particles"].loadFiles("assets/Shaders/Particles_VS.glsl", nullptr, "assets/Shaders/Particles_FS.glsl");
    ShaderMap["DEFERRED"].loadFiles("assets/Shaders/Deferred_VS.glsl", nullptr, "assets/Shaders/Deferred_FS.glsl");
    ShaderMap["Video"].loadFiles("assets/Shaders/VIDEO_VS.glsl", nullptr, "assets/Shaders/VIDEO_FS.glsl");
    ShaderMap["PostProcessing"].loadFiles("assets/Shaders/Post_Processing_VS.glsl", nullptr, "assets/Shaders/Post_Processing_FS.glsl");
    ShaderMap["Query"].loadFiles("assets/Shaders/Line_VS.glsl", nullptr, nullptr);

    ShaderMap["HUD"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2DHUD.glsl");
}

void AssetManager::loadInit(){
    Shader* shader = getShader("Default");
    ZMaterial* 		MAT = getMaterial("Default");
    MAT->attachShader(shader);
    MAT->addTexture(GN::DIFFUSE_MAP,  getTexture("assets/Textures/DefaultDiffuse.jpg",3));
    MAT->addTexture(GN::NORMAL_MAP,   getTexture("assets/Textures/DefaultNormal.jpg",3));
    MAT->addTexture(GN::SPECULAR_MAP, getTexture("assets/Textures/DefaultSpecular.jpg",1));

    MAT = getMaterial("Morado");
    MAT->attachShader(shader);
    MAT->addTexture(GN::DIFFUSE_MAP,      getTexture("assets/Textures/prueba1.png",3));
    MAT->addTexture(GN::NORMAL_MAP,       getTexture("assets/Textures/COMOUNPUTOPRO3.png",3));
    MAT->addTexture(GN::SPECULAR_MAP,     getTexture("assets/Textures/DefaultSpecular.jpg",1));

    ZMaterial* 		Blue = getMaterial("Blue");
    Blue->attachShader(shader);
    Blue->addTexture(GN::DIFFUSE_MAP,      getTexture("assets/Textures/Blue.png",3));
    Blue->addTexture(GN::NORMAL_MAP,       getTexture("assets/Textures/DefaultNormal.jpg",3));
    Blue->addTexture(GN::SPECULAR_MAP,     getTexture("assets/Textures/DefaultSpecular.jpg",1));

    ZMaterial* 		Nav = getMaterial("Nav");
    Nav->attachShader(shader);
    Nav->addTexture(GN::DIFFUSE_MAP,      getTexture("assets/Textures/TEST.png",3));
    Nav->addTexture(GN::NORMAL_MAP,       getTexture("assets/Textures/DefaultNormal.jpg",3));
    Nav->addTexture(GN::SPECULAR_MAP,     getTexture("assets/Textures/DefaultSpecular.jpg",1));

    ZMaterial* 		Grey = getMaterial("Grey");
    Grey->attachShader(shader);
    Grey->addTexture(GN::DIFFUSE_MAP,      getTexture("assets/Textures/grey.jpg",3));
    Grey->addTexture(GN::NORMAL_MAP,       getTexture("assets/Textures/DefaultNormal.jpg",3));
    Grey->addTexture(GN::SPECULAR_MAP,     getTexture("assets/Textures/DefaultSpecular.jpg",1));

    ZMaterial* 		Red = getMaterial("Red");
    Red->attachShader(shader);
    Red->addTexture(GN::DIFFUSE_MAP,      getTexture("assets/Textures/red.jpg",3));
    Red->addTexture(GN::NORMAL_MAP,       getTexture("assets/Textures/DefaultNormal.jpg",3));
    Red->addTexture(GN::SPECULAR_MAP,     getTexture("assets/Textures/DefaultSpecular.jpg",1));

    shader = getShader("AnimationShader");
    ZMaterial* Sold = getMaterial("Soldier");
    Sold->attachShader(shader);
    Sold->addTexture(GN::DIFFUSE_MAP,      getTexture("assets/Textures/DefaultDiffuse.jpg",3));
    Sold->addTexture(GN::NORMAL_MAP,       getTexture("assets/Textures/ALIEN.png",3));
    Sold->addTexture(GN::SPECULAR_MAP,     getTexture("assets/Textures/DefaultSpecular.jpg",1));

    ZMaterial* 		Hero = getMaterial("Hero");
    Hero->attachShader(shader);
    Hero->addTexture(GN::DIFFUSE_MAP,      getTexture("assets/Textures/HERO/HERO_t.png",3));
    Hero->addTexture(GN::NORMAL_MAP,       getTexture("assets/Textures/HERO/HERO_n.png",3));
    Hero->addTexture(GN::SPECULAR_MAP,     getTexture("assets/Textures/DefaultSpecular.jpg",1));

    ZAnimationData* AnimationData = getAnimation("Soldier_Running");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov5.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov4.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov1.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/SoldierMov0.modelgg");

    AnimationData = getAnimation("Hero_Standing");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Standing3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Standing2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Standing1.modelgg");

    AnimationData = getAnimation("Hero_Walking");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking1.modelgg");

    AnimationData = getAnimation("Hero_Walking_Weapon");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking_Weapon3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking_Weapon2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Walking_Weapon1.modelgg");

    AnimationData = getAnimation("Hero_Jumping");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Jumping4.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Jumping3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Jumping2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Jumping1.modelgg");

    AnimationData = getAnimation("Hero_Jumping_Walking");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Jumping_Walking4.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Jumping_Walking3.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Jumping_Walking2.modelgg");
    AnimationData->addKeyframe("assets/BinaryFiles/BinaryModels/Jumping_Walking1.modelgg");
}

ZMaterial* AssetManager::getMaterial(const std::string &Name) {
    auto it = MaterialMap.find(Name);
    if(it != MaterialMap.end()){
        return &it->second;
    }
    else {
        return &MaterialMap[Name];
    }
}

ZMeshData* AssetManager::getMeshData(const std::string &Name){

    auto it = MeshDataMap.find(Name);
    if(it != MeshDataMap.end())
        return &it->second;
    else{
        ZMeshData* ret = &MeshDataMap[Name];
        ret->load(Name);
        return ret;
    }

}

Shader* AssetManager::getShader(const std::string &Name) {

    auto it = ShaderMap.find(Name);
    if(it != ShaderMap.end())
        return &it->second;
    else{
        //std::cout << "  --No existe ningún Shader llamado '" << Name <<"', devolviendo 'Default'..." << '\n';
        return &ShaderMap["Default"];
    }
}

ZAnimationData* AssetManager::getAnimation(const std::string &Name){

    auto it = AnimationMap.find(Name);
    if(it != AnimationMap.end()){
        return &it->second;
    }
    else {
        return &AnimationMap[Name];
    }
}

unsigned int AssetManager::getTexture(const std::string &Name, int ForceChannels){
    if(TextureMap.find(Name) != TextureMap.end()){
        return TextureMap[Name];
    }
    else {

        unsigned int NewID = 0;
        int width, height, nrChannels;
        unsigned char *data = stbi_load(Name.c_str(), &width, &height, &nrChannels, ForceChannels);

        if (data) {
            if(ForceChannels == 0) ForceChannels = nrChannels;

            glGenTextures(1, &NewID);
            glBindTexture(GL_TEXTURE_2D, NewID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            unsigned int INTERNAL_FORMAT = 0;
            unsigned int     READ_FORMAT = 0;

            if(ForceChannels == 1){
                INTERNAL_FORMAT = GL_R8;
                READ_FORMAT = GL_RED;
            }
            else if(ForceChannels == 2){
                INTERNAL_FORMAT = GL_RG8;
                READ_FORMAT = GL_RG;
            }
            else if(ForceChannels == 3){
                INTERNAL_FORMAT = GL_RGB8;
                READ_FORMAT = GL_RGB;
            }
            else {
                INTERNAL_FORMAT = GL_RGBA8;
                READ_FORMAT = GL_RGBA;
            }

            glTexStorage2D(GL_TEXTURE_2D, 1, INTERNAL_FORMAT, width, height);
            glTextureSubImage2D(NewID, 0,0,0, width, height, READ_FORMAT, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
        }

        TextureMap.insert(std::make_pair(Name, NewID));
        return NewID;
    }
}

AssetManager::~AssetManager(){
    //std::cout << "Deleting textures..." << '\n';
    auto iterator = TextureMap.begin();
    while(iterator != TextureMap.end()){
        glDeleteTextures(1, &iterator->second);
        ++iterator;
    }
    AnimationMap.clear();
    MeshDataMap.clear();
    MaterialMap.clear();
    TextureMap.clear();
}
