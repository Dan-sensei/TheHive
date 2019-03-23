#include "NatureGenerator.hpp"


NatureGenerator::NatureGenerator(){
    fabrik = Singleton<Factory>::Instance();
    Manager = Singleton<AssetManager>::Instance();
}

NatureGenerator::~NatureGenerator(){
    // delete tmp_positions;
}


void NatureGenerator::init(const uint8_t &map_zone, const glm::vec3 &Pos){
    std::vector< float > PositionsNormals;
    std::vector< float > UV_Coords;
    std::vector< float > TangentsBitangents;
    std::vector< unsigned short > Indexes;

    std::string Path = "assets/BinaryFiles/BinaryModels/nature_test1.modelgg";
    std::string Path2 = "assets/BinaryFiles/BinaryModels/nature1.modelgg";

    bool loaded = BinaryParser::ImportMesh(Path, PositionsNormals, UV_Coords, TangentsBitangents, Indexes);
    if(!loaded){
        std::cout << "No se ha podido cargar la malla de vegetacion - " << Path << '\n';
        return;
    }

    glm::vec3 tmp_pos, tmp_rot;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist1(0,360);
    std::uniform_int_distribution<int> dist2(0,10);

    // Shader* Shader = Manager->getShader("Nature");
    // Shader* Shader = Manager->getShader("Default");
    // ZMaterial* Material = Manager->getMaterial("Nature");
    // Material->attachShader(Shader);
    // Material->addTexture("DiffuseMap",      "assets/Textures/Nature/plant.png",       		GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    // Material->addTexture("NormalMap",       "assets/Textures/COMOUNPUTOPRO3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
    // Material->addTexture("SpecularMap",     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);

    // ZMaterial* Material = Manager->getMaterial("Morado");
    ZMaterial* Material = Manager->getMaterial("Default");

    for (size_t i = 0; i < PositionsNormals.size(); i+=6) {
        if(dist2(gen)>6){
            tmp_pos = glm::vec3(
                Pos.x+PositionsNormals[i],
                Pos.y+PositionsNormals[i+1],
                Pos.z+PositionsNormals[i+2]
            );
            tmp_rot = glm::vec3(0,dist1(gen),0);

            fabrik->createNatureMesh(Path2,tmp_pos,tmp_rot,Material,map_zone);
        }
    }

}


// void NatureGenerator::init(const glm::vec3 &Pos){
//     // Necesito mandar como yuniform:
//     //      UV
//     //      NORMALES
//     //      TANGENTES
//     //      BITANGENTES
//     std::vector< float > PositionsNormals;
//     std::vector< float > UV_Coords;
//     std::vector< float > TangentsBitangents;
//     std::vector< unsigned short > Indexes;
//
//     std::string Path = "assets/BinaryFiles/BinaryModels/nature_test1.modelgg";
//     std::string natureModelPath = "assets/BinaryFiles/BinaryModels/Hero.modelgg";
//
//     bool loaded = BinaryParser::ImportMesh(natureModelPath, PositionsNormals, UV_Coords, TangentsBitangents, Indexes);
//     if(!loaded){
//         std::cout << "No se ha podido cargar la malla de vegetacion - " << Path << '\n';
//         return;
//     }
//
//     std::cout << '\n';
//     std::cout << " - PositionNormals       : " << PositionsNormals.size() << '\n';
//     std::cout << " - UV_Coords             : " << UV_Coords.size() << '\n';
//     std::cout << " - TangentsBitangents    : " << TangentsBitangents.size() << '\n';
//     std::cout << " - Indexes               : " << Indexes.size() << '\n';
//     std::cout << '\n';
//
//     // std::cout << "TangentsBitangents" << '\n';
//     // for (size_t i = 0; i < TangentsBitangents.size(); i+=3) {
//     //     std::cout << TangentsBitangents[i] << "," << TangentsBitangents[i+1] << "," << TangentsBitangents[i+2] << '\n';
//     // }
//     // std::cout << '\n';
//     //
//     // std::cout << "PositionsNormals" << '\n';
//     // for (size_t i = 0; i < PositionsNormals.size(); i+=3) {
//     //     std::cout << PositionsNormals[i] << "," << PositionsNormals[i+1] << "," << PositionsNormals[i+2] << '\n';
//     // }
//     // std::cout << '\n';
//     //
//     // std::cout << "UV_Coords" << '\n';
//     // for (size_t i = 0; i < UV_Coords.size(); i+=3) {
//     //     std::cout << UV_Coords[i] << "," << UV_Coords[i+1] << "," << UV_Coords[i+2] << '\n';
//     // }
//     // std::cout << '\n';
//     //
//     // std::cout << "Indexes" << '\n';
//     // for (size_t i = 0; i < Indexes.size(); i+=3) {
//     //     std::cout << Indexes[i] << "," << Indexes[i+1] << "," << Indexes[i+2] << '\n';
//     // }
//     // std::cout << '\n';
//
//     // Hero.obj
//     /*
//         - PositionNormals       : 144
//         - UV_Coords             : 48
//         - TangentsBitangents    : 144
//         - Indexes               : 36
//     */
//
//     // tmp_positions = new float[PositionsNormals.size()];
//     float tmp_positions[PositionsNormals.size()];
//     for (size_t i = 0; i < PositionsNormals.size(); i++) {
//         tmp_positions[i] = PositionsNormals[i];
//     }
//
//     // for (size_t i = 0; i < PositionsNormals.size(); i+=6) {
//     //     std::cout << "(" << tmp_positions[i] << "\t," << tmp_positions[i+1] << "\t," << tmp_positions[i+2] << ")" << '\n';
//     // }
//
//     // Lo divido entre 3 ya que el shader tiene un array de vec3
//     GS_SIZE = PositionsNormals.size()/3;
//     // GS_SIZE = -1;
//
//     Shader *sh = Manager->getShader("Nature");
//     sh->Bind();
//
//     GLuint SIZE_LOC = sh->getUniformLocation("GS_SIZE");
//     if(SIZE_LOC == 0xFFFFFFFF)  std::cout << "Cacho mierda, no ha cogido la ubicacion de GS_SIZE" << '\n';
//     else                        glUniform1i(SIZE_LOC,GS_SIZE);
//
//     GLuint POS_LOC = sh->getUniformLocation("GS_POSITIONS");
//     if(POS_LOC == 0xFFFFFFFF)   std::cout << "Cacho mierda, no ha cogido la ubicacion de GS_POSITIONS" << '\n';
//     else                        glUniform1fv(POS_LOC,GS_SIZE,&tmp_positions[0]);
//
//     fabrik->createNatureMesh(Path,Pos,glm::vec3());
//
//     std::cout << " - GS_SIZE:" << GS_SIZE << '\n';
// }

void NatureGenerator::update(){
    // std::cout << "UPDATE NATURE" << '\n';
    // Shader *sh = Manager->getShader("Nature");
    // sh->Bind();
    // GLuint UL;

    // UL = sh->getUniformLocation("GS_POSITIONS");
    // if(UL == 0xFFFFFFFF) std::cout << "Cacho mierda, no ha cogido la ubicacion de GS_POSITIONS" << '\n';
    // glUniform1fv(UL,GS_SIZE,&tmp_positions[0]);

    // UL = sh->getUniformLocation("GS_SIZE");
    // if(UL == 0xFFFFFFFF) std::cout << "Cacho mierda, no ha cogido la ubicacion de GS_SIZE" << '\n';
    // glUniform1i(UL,GS_SIZE);
}
