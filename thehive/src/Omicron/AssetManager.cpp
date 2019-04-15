#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>

AssetManager::AssetManager(){
    ShaderMap["Nature"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Default"].loadFiles("assets/Shaders/VertexShader.glsl", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Lines"].loadFiles("assets/Shaders/Line_VS.glsl", nullptr, "assets/Shaders/Line_FS.glsl");
    ShaderMap["2D"].loadFiles("assets/Shaders/VertexShader2D.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Bill"].loadFiles("assets/Shaders/VertexShaderBillboard.glsl", nullptr, "assets/Shaders/FragmentShader2D.glsl");
    ShaderMap["Blend"].loadFiles("assets/Shaders/VertexShaderblend.glsl", nullptr, "assets/Shaders/FragmentShaderblend.glsl");
    ShaderMap["Plano"].loadFiles("assets/Shaders/VertexShader2DPlano.glsl", nullptr, "assets/Shaders/FragmentShader2DPlano.glsl");
    ShaderMap["skyboxShader"].loadFiles("assets/Shaders/SkyBox.vs", nullptr, "assets/Shaders/SkyBox.frag");
    ShaderMap["AnimationShader"].loadFiles("assets/Shaders/Animation.vs", nullptr, "assets/Shaders/FragmentShader.glsl");
    ShaderMap["Particles"].loadFiles("assets/Shaders/Particles_VS.glsl", nullptr, "assets/Shaders/Particles_FS.glsl");
    ShaderMap["DEFERRED"].loadFiles("assets/Shaders/Deferred_VS.glsl", nullptr, "assets/Shaders/Deferred_FS.glsl");
}

void AssetManager::loadInit(){
    Shader* shader = getShader("Default");
    ZMaterial* 		MAT = getMaterial("Default");
    MAT->attachShader(shader);
    MAT->addTexture(GN::DIFFUSE_MAP, "assets/Textures/DefaultDiffuse.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP, "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP, "assets/Textures/DefaultSpecular.jpeg",   GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    MAT = getMaterial("Morado");
    MAT->attachShader(shader);
    MAT->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/prueba1.png",       		GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::NORMAL_MAP,       "assets/Textures/COMOUNPUTOPRO3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    MAT->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Blue = getMaterial("Blue");
    Blue->attachShader(shader);
    Blue->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Blue.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Blue->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Blue->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Nav = getMaterial("Nav");
    Nav->attachShader(shader);
    Nav->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/TEST.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Nav->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Nav->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);



    ZMaterial* 		Metal = getMaterial("Metal");
    Metal->attachShader(shader);
    Metal->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/metal.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Metal->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Metal->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Tree = getMaterial("Tree");
    Tree->attachShader(shader);
    Tree->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Tree.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Tree->addTexture(GN::NORMAL_MAP,       "assets/Textures/Tree_Normals.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Tree->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Grey = getMaterial("Grey");
    Grey->attachShader(shader);
    Grey->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/grey.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Grey->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Grey->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Red = getMaterial("Red");
    Red->attachShader(shader);
    Red->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/red.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Red->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Red->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		White = getMaterial("White");
    White->attachShader(shader);
    White->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/white.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    White->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    White->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Ground = getMaterial("Ground");
    Ground->attachShader(shader);
    Ground->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Asfalto_Diffuse.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Ground->addTexture(GN::NORMAL_MAP,       "assets/Textures/Asfalto_Normal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Ground->addTexture(GN::SPECULAR_MAP,     "assets/Textures/Asfalto_Gloss.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Farola = getMaterial("Farola");
    Farola->attachShader(shader);
    Farola->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/farola1.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Farola->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Farola->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Car1 = getMaterial("Car1");
    Car1->attachShader(shader);
    Car1->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/car1.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car1->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car1->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Car2 = getMaterial("Car2");
    Car2->attachShader(shader);
    Car2->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/car2.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car2->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car2->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Car3 = getMaterial("Car3");
    Car3->attachShader(shader);
    Car3->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/car3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car3->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Car3->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Container = getMaterial("Container");
    Container->attachShader(shader);
    Container->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Container.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Container->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Container->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Separador = getMaterial("Separador");
    Separador->attachShader(shader);
    Separador->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Separador.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Separador->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Separador->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Trash = getMaterial("Trash");
    Trash->attachShader(shader);
    Trash->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/Trash.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Trash->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Trash->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		House = getMaterial("House");
    House->attachShader(shader);
    House->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/house.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    House->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    House->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		House2 = getMaterial("House2");
    House2->attachShader(shader);
    House2->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/brown.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    House2->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    House2->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Door = getMaterial("Door");
    Door->attachShader(shader);
    Door->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/door.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Door->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Door->addTexture(GN::SPECULAR_MAP,     "assets/Textures/Asfalto_Gloss.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model2 = getMaterial("Model2");
    Model2->attachShader(shader);
    Model2->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/2_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model2->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/2_n.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model2->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model3 = getMaterial("Model3");
    Model3->attachShader(shader);
    Model3->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/3_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model3->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/3_n.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model3->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model4 = getMaterial("Model4");
    Model4->attachShader(shader);
    Model4->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/4_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model4->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/4_n.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model4->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model4_2 = getMaterial("Model4_2");
    Model4_2->attachShader(shader);
    Model4_2->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/4_2_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model4_2->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/4_n.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model4_2->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model4_3 = getMaterial("Model4_3");
    Model4_3->attachShader(shader);
    Model4_3->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/4_3_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model4_3->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/4_n.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model4_3->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model5 = getMaterial("Model5");
    Model5->attachShader(shader);
    Model5->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/5_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model5->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model5->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model6 = getMaterial("Model6");
    Model6->attachShader(shader);
    Model6->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/6_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model6->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model6->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model6_2 = getMaterial("Model6_2");
    Model6_2->attachShader(shader);
    Model6_2->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/6_2_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model6_2->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model6_2->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model7 = getMaterial("Model7");
    Model7->attachShader(shader);
    Model7->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/7_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model7->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/7_n.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model7->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model8 = getMaterial("Model8");
    Model8->attachShader(shader);
    Model8->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/8_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model8->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/8_n.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model8->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model106 = getMaterial("Model106");
    Model106->attachShader(shader);
    Model106->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/106_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model106->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/106_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model106->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    // ----------------------------------------

    ZMaterial* 		Model9 = getMaterial("Model9");
    Model9->attachShader(shader);
    Model9->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/9_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model9->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model9->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model10 = getMaterial("Model10");
    Model10->attachShader(shader);
    Model10->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/10_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model10->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model10->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model11 = getMaterial("Model11");
    Model11->attachShader(shader);
    Model11->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/11_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model11->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model11->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model12 = getMaterial("Model12");
    Model12->attachShader(shader);
    Model12->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/12_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model12->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model12->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model13 = getMaterial("Model13");
    Model13->attachShader(shader);
    Model13->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/13_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model13->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/13_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model13->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model14 = getMaterial("Model14");
    Model14->attachShader(shader);
    Model14->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/14_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model14->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/14_n.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model14->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model30 = getMaterial("Model30");
    Model30->attachShader(shader);
    Model30->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/30_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model30->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/30_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model30->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model31 = getMaterial("Model31");
    Model31->attachShader(shader);
    Model31->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/31_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model31->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model31->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model32 = getMaterial("Model32");
    Model32->attachShader(shader);
    Model32->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/32_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model32->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model32->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model33 = getMaterial("Model33");
    Model33->attachShader(shader);
    Model33->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/33_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model33->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model33->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model34 = getMaterial("Model34");
    Model34->attachShader(shader);
    Model34->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/34_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model34->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/34_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model34->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model35 = getMaterial("Model35");
    Model35->attachShader(shader);
    Model35->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/35_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model35->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model35->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model36 = getMaterial("Model36");
    Model36->attachShader(shader);
    Model36->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/36_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model36->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model36->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model37 = getMaterial("Model37");
    Model37->attachShader(shader);
    Model37->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/37_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model37->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model37->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model38 = getMaterial("Model38");
    Model38->attachShader(shader);
    Model38->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/38_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model38->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model38->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model39 = getMaterial("Model39");
    Model39->attachShader(shader);
    Model39->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/39_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model39->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/39_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model39->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model40 = getMaterial("Model40");
    Model40->attachShader(shader);
    Model40->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/40_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model40->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model40->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model41 = getMaterial("Model41");
    Model41->attachShader(shader);
    Model41->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/41_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model41->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/41_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model41->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model42 = getMaterial("Model42");
    Model42->attachShader(shader);
    Model42->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/42_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model42->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/42_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model42->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model43 = getMaterial("Model43");
    Model43->attachShader(shader);
    Model43->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/43_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model43->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/43_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model43->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model44 = getMaterial("Model44");
    Model44->attachShader(shader);
    Model44->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/44_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model44->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model44->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model45 = getMaterial("Model45");
    Model45->attachShader(shader);
    Model45->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/45_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model45->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model45->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model46 = getMaterial("Model46");
    Model46->attachShader(shader);
    Model46->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/46_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model46->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/46_n.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model46->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model47 = getMaterial("Model47");
    Model47->attachShader(shader);
    Model47->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/47_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model47->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model47->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model48 = getMaterial("Model48");
    Model48->attachShader(shader);
    Model48->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/48_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model48->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model48->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model49 = getMaterial("Model49");
    Model49->attachShader(shader);
    Model49->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/49_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model49->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/49_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model49->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model50 = getMaterial("Model50");
    Model50->attachShader(shader);
    Model50->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/50_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model50->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/50_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model50->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model51 = getMaterial("Model51");
    Model51->attachShader(shader);
    Model51->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/51_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model51->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/51_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model51->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model52 = getMaterial("Model52");
    Model52->attachShader(shader);
    Model52->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/52_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model52->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/52_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model52->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model53 = getMaterial("Model53");
    Model53->attachShader(shader);
    Model53->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/53_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model53->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/53_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model53->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model54 = getMaterial("Model54");
    Model54->attachShader(shader);
    Model54->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/54_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model54->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/54_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model54->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model55 = getMaterial("Model55");
    Model55->attachShader(shader);
    Model55->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/55_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model55->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/55_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model55->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model57 = getMaterial("Model57");
    Model57->attachShader(shader);
    Model57->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/57_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model57->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/57_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model57->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model101 = getMaterial("Model101");
    Model101->attachShader(shader);
    Model101->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/101_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model101->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/101_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model101->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model103 = getMaterial("Model103");
    Model103->attachShader(shader);
    Model103->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/103_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model103->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/103_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model103->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model104 = getMaterial("Model104");
    Model104->attachShader(shader);
    Model104->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/104_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model104->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/104_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model104->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model105 = getMaterial("Model105");
    Model105->attachShader(shader);
    Model105->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/105_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model105->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model105->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    // ----------------------------------------

    ZMaterial* 		Model109 = getMaterial("Model109");
    Model109->attachShader(shader);
    Model109->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/109_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model109->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/109_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model109->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model110 = getMaterial("Model110");
    Model110->attachShader(shader);
    Model110->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/110_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model110->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/110_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model110->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model112 = getMaterial("Model112");
    Model112->attachShader(shader);
    Model112->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/112_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model112->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model112->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model113 = getMaterial("Model113");
    Model113->attachShader(shader);
    Model113->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/113_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model113->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model113->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model114 = getMaterial("Model114");
    Model114->attachShader(shader);
    Model114->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/114_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model114->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model114->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model115 = getMaterial("Model115");
    Model115->attachShader(shader);
    Model115->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/115_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model115->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model115->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model116 = getMaterial("Model116");
    Model116->attachShader(shader);
    Model116->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/116_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model116->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model116->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model117 = getMaterial("Model117");
    Model117->attachShader(shader);
    Model117->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/117_t.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model117->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model117->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model118 = getMaterial("Model118");
    Model118->attachShader(shader);
    Model118->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/118_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model118->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model118->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model119 = getMaterial("Model119");
    Model119->attachShader(shader);
    Model119->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/119_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model119->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/119_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model119->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model120 = getMaterial("Model120");
    Model120->attachShader(shader);
    Model120->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/120_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model120->addTexture(GN::NORMAL_MAP,       "assets/Textures/UINT8_T_NORMALS/120_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model120->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model121 = getMaterial("Model121");
    Model121->attachShader(shader);
    Model121->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/121_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model121->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model121->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model122 = getMaterial("Model122");
    Model122->attachShader(shader);
    Model122->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/122_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model122->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model122->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model123 = getMaterial("Model123");
    Model123->attachShader(shader);
    Model123->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/123_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model123->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model123->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model124 = getMaterial("Model124");
    Model124->attachShader(shader);
    Model124->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/124_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model124->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model124->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model125 = getMaterial("Model125");
    Model125->attachShader(shader);
    Model125->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/125_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model125->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model125->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model126 = getMaterial("Model126");
    Model126->attachShader(shader);
    Model126->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/126_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model126->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model126->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model127 = getMaterial("Model127");
    Model127->attachShader(shader);
    Model127->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/127_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model127->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model127->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Model128 = getMaterial("Model128");
    Model128->attachShader(shader);
    Model128->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/UINT8_T_TEXTURES/128_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model128->addTexture(GN::NORMAL_MAP,       "assets/Textures/DefaultNormal.jpg",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Model128->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);



    shader = getShader("Blend");

    ZMaterial* 		Build = getMaterial("building");
    Build->attachShader(shader);
    Build->addTexture(GN::BLEND1,      "assets/Textures/edif.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Build->addTexture(GN::BLEND2,      "assets/Textures/edifluz.png",       		     GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    shader = getShader("AnimationShader");
    ZMaterial* Sold = getMaterial("Soldier");
    Sold->attachShader(shader);
    Sold->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/DefaultDiffuse.jpg",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Sold->addTexture(GN::NORMAL_MAP,       "assets/Textures/ALIEN.png",         GN::RGBA, GN::INVERT_Y | GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Sold->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    ZMaterial* 		Hero = getMaterial("Hero");
    Hero->attachShader(shader);
    Hero->addTexture(GN::DIFFUSE_MAP,      "assets/Textures/HERO/HERO_t.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Hero->addTexture(GN::NORMAL_MAP,       "assets/Textures/HERO/HERO_n.png",         GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    Hero->addTexture(GN::SPECULAR_MAP,     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);



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

Shader* AssetManager::createShader(std::string Name) {
    if(ShaderMap.find(Name) == ShaderMap.end())
        ShaderMap[Name];

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
    //std::cout << "Deleting textures..." << '\n';
    auto iterator = TextureMap.begin();
    while(iterator != TextureMap.end()){
        glDeleteTextures(1, &iterator->second);
        ++iterator;
    }
}
