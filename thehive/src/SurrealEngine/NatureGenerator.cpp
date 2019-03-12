#include "NatureGenerator.hpp"


NatureGenerator::NatureGenerator(){
    fabrik = Singleton<Factory>::Instance();
    Manager = Singleton<AssetManager>::Instance();
}

NatureGenerator::~NatureGenerator(){

}

void NatureGenerator::init(const glm::vec3 &Pos){
    std::vector< float > PositionsNormals;
    std::vector< float > UV_Coords;
    std::vector< float > TangentsBitangents;
    std::vector< unsigned short > Indexes;

    std::string Path = "assets/BinaryFiles/BinaryModels/nature_test1.modelgg";
    std::string Path2 = "assets/BinaryFiles/BinaryModels/flor.modelgg";

    bool loaded = BinaryParser::ImportMesh(Path, PositionsNormals, UV_Coords, TangentsBitangents, Indexes);
    if(!loaded){
        std::cout << "No se ha podido cargar la malla de vegetacion - " << Path << '\n';
        return;
    }

    // std::cout << '\n';
    // std::cout << " - PositionNormals       : " << PositionsNormals.size() << '\n';
    // std::cout << " - UV_Coords             : " << UV_Coords.size() << '\n';
    // std::cout << " - TangentsBitangents    : " << TangentsBitangents.size() << '\n';
    // std::cout << " - Indexes               : " << Indexes.size() << '\n';
    // std::cout << '\n';

    // std::cout << "PositionsNormals" << '\n';
    // for (size_t i = 0; i < PositionsNormals.size(); i+=3) {
    //     std::cout << PositionsNormals[i] << "," << PositionsNormals[i+1] << "," << PositionsNormals[i+2] << '\n';
    // }
    // std::cout << '\n';

    glm::vec3 tmp_pos, tmp_rot;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist1(0,360);
    std::uniform_int_distribution<int> dist2(0,10);

    for (size_t i = 0; i < PositionsNormals.size(); i+=6) {
        if(dist2(gen)>9){
            tmp_pos = glm::vec3(
                Pos.x+PositionsNormals[i],
                Pos.y+PositionsNormals[i+1],
                Pos.z+PositionsNormals[i+2]
            );
            tmp_rot = glm::vec3(0,dist1(gen),0);

            fabrik->createNatureMesh(Path2,tmp_pos,tmp_rot);
        }
    }

}

/*
void NatureGenerator::init( const std::string &Path, const glm::vec3 &Pos){
    // Necesito mandar como yuniform:
    //      UV
    //      NORMALES
    //      TANGENTES
    //      BITANGENTES
    PositionsNormals;
    std::vector< float > UV_Coords;
    std::vector< float > TangentsBitangents;
    std::vector< unsigned short > Indexes;

    std::string natureModelPath = "assets/BinaryFiles/BinaryModels/Hero.modelgg";

    bool loaded = BinaryParser::ImportMesh(natureModelPath, PositionsNormals, UV_Coords, TangentsBitangents, Indexes);
    if(!loaded){
        std::cout << "No se ha podido cargar la malla de vegetacion - " << Path << '\n';
        return;
    }

    std::cout << '\n';
    std::cout << " - PositionNormals       : " << PositionsNormals.size() << '\n';
    std::cout << " - UV_Coords             : " << UV_Coords.size() << '\n';
    std::cout << " - TangentsBitangents    : " << TangentsBitangents.size() << '\n';
    std::cout << " - Indexes               : " << Indexes.size() << '\n';
    std::cout << '\n';

    // std::cout << "TangentsBitangents" << '\n';
    // for (size_t i = 0; i < TangentsBitangents.size(); i+=3) {
    //     std::cout << TangentsBitangents[i] << "," << TangentsBitangents[i+1] << "," << TangentsBitangents[i+2] << '\n';
    // }
    // std::cout << '\n';
    //
    // std::cout << "PositionsNormals" << '\n';
    // for (size_t i = 0; i < PositionsNormals.size(); i+=3) {
    //     std::cout << PositionsNormals[i] << "," << PositionsNormals[i+1] << "," << PositionsNormals[i+2] << '\n';
    // }
    // std::cout << '\n';
    //
    // std::cout << "UV_Coords" << '\n';
    // for (size_t i = 0; i < UV_Coords.size(); i+=3) {
    //     std::cout << UV_Coords[i] << "," << UV_Coords[i+1] << "," << UV_Coords[i+2] << '\n';
    // }
    // std::cout << '\n';
    //
    // std::cout << "Indexes" << '\n';
    // for (size_t i = 0; i < Indexes.size(); i+=3) {
    //     std::cout << Indexes[i] << "," << Indexes[i+1] << "," << Indexes[i+2] << '\n';
    // }
    // std::cout << '\n';

    Shader *sh = Manager->getShader("Nature");
    GLuint UL;

    // NORMALES
    tmp_positions = new float[PositionsNormals.size()];
    UL = sh->getUniformLocation("GS_POSITIONS");
    glUniform1fv(UL,1,&tmp_positions[0]);

    UL = sh->getUniformLocation("GS_SIZE");
    glUniform1i(UL,PositionsNormals.size());

    fabrik->createNatureMesh(Path,Pos);
}
*/
