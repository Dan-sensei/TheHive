#include "BinaryParser.hpp"
#include <fstream>
#include <experimental/filesystem>
#include <ComponentArch/Components/ComponentHeaders.hpp>
#include <ComponentArch/ObjectManager.hpp>


template<typename T>
std::istream & GG_Read(std::istream& _istream, T& value){
    return _istream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

void BinaryParser::ReadNavmeshData(
    const std::string &BinaryFile,
    std::vector<Node> &GRAPH,
    std::vector<std::vector<Connection>> &Connections,
    std::vector<Face> &SQUARE_FACES
){

    std::ifstream Navmesh(BinaryFile, std::ios::binary);

    uint16_t GRAPH_SIZE;
    GG_Read(Navmesh, GRAPH_SIZE);

    GRAPH.reserve(GRAPH_SIZE);
    for(uint16_t i = 0; i < GRAPH_SIZE; ++i){

        uint16_t ID;
        GG_Read(Navmesh, ID);

        uint16_t NODE_1;
        GG_Read(Navmesh, NODE_1);

        uint16_t NODE_2;
        GG_Read(Navmesh, NODE_2);

        glm::vec3 Position;
        GG_Read(Navmesh, Position);

        float Radius;
        GG_Read(Navmesh, Radius);

        GRAPH.emplace_back(ID, NODE_1, NODE_2, Position, Radius);
    }

    uint16_t CONNECTIONS_SIZE;
    GG_Read(Navmesh, CONNECTIONS_SIZE);
    Connections.reserve(CONNECTIONS_SIZE);
    Connections.resize(CONNECTIONS_SIZE);

    for(uint16_t i = 0; i < CONNECTIONS_SIZE; ++i){
        uint16_t CONNECTION_X_SIZE;
        GG_Read(Navmesh, CONNECTION_X_SIZE);
        Connections[i].reserve(CONNECTION_X_SIZE);
        for(uint16_t j = 0; j < CONNECTION_X_SIZE; ++j){
            float Value;
            GG_Read(Navmesh, Value);

            uint16_t From;
            GG_Read(Navmesh, From);

            uint16_t To;
            GG_Read(Navmesh, To);

            Connections[i].emplace_back(Value, From, To);
        }
    }

    uint16_t SQUARE_FACES_SIZE;
    GG_Read(Navmesh, SQUARE_FACES_SIZE);

    SQUARE_FACES.reserve(SQUARE_FACES_SIZE);
    for(uint16_t i = 0; i < SQUARE_FACES_SIZE; ++i){
        glm::vec3 TL;
        GG_Read(Navmesh, TL);

        glm::vec3 BR;
        GG_Read(Navmesh, BR);

        SQUARE_FACES.emplace_back(TL, BR);

        uint16_t PORTALS_SIZE;
        GG_Read(Navmesh, PORTALS_SIZE);
        for(uint16_t j = 0; j < PORTALS_SIZE; ++j){
            uint16_t PortalID;
            GG_Read(Navmesh, PortalID);
            SQUARE_FACES.back().Portals.push_back(PortalID);
        }

    }

}


void BinaryParser::LoadLevelData(const std::string &DATA, int8_t map_zone){

    std::ifstream inStream(DATA, std::ios::binary);
    uint8_t NUMBER_OF_OBJECTS = 0;
    GG_Read(inStream, NUMBER_OF_OBJECTS);

    //std::cout << "NUM " << (uint16_t)NUMBER_OF_OBJECTS << '\n';

    for(uint16_t i = 0; i < NUMBER_OF_OBJECTS; ++i){
        uint8_t MODEL = 0;
        GG_Read(inStream, MODEL);
        std::string str = std::to_string(MODEL);
        str+=".modelgg";

        auto Manager = Singleton<ObjectManager>::Instance();
        uint16_t NewEntity = Manager->createEntity();

        //std::cout << "Model->  " << str << '\n';
        float x,y,z;
        GG_Read(inStream, x);
        GG_Read(inStream, y);
        GG_Read(inStream, z);
        glm::vec3 Position(x,y,z);
        //std::cout << "   -Position: " << x << ", " << y << ", " << z << '\n';
        //if(MODEL == 45) std::cout << "Position " << Position.x << ", " << Position.y << ", " << Position.z << '\n';
        GG_Read(inStream, x);
        GG_Read(inStream, y);
        GG_Read(inStream, z);
        glm::vec3 Rotation(x,y,z);
        //if(MODEL == 37) std::cout << "Rotation " << Rotation.x << ", " << Rotation.y << ", " << Rotation.z << '\n';
        //std::cout << "   -Rotation: " << x << ", " << y << ", " << z << '\n';

        bool HasCollider;
        GG_Read(inStream, HasCollider);
        ZMaterial* Dark = AssetManager::getMaterial("Default");
        CStaticModel* Transform = new CStaticModel("assets/BinaryFiles/BinaryModels/"+str, Dark, Position, Rotation, map_zone);
        Manager->addComponentToEntity(Transform, gg::STATICMODEL, NewEntity);

        //std::cout << "Collider? = " << HasCollider << '\n';
        if(HasCollider){
            GG_Read(inStream, x);
            GG_Read(inStream, y);
            GG_Read(inStream, z);

            float rx, ry, rz, rw;
            GG_Read(inStream, rx);
            GG_Read(inStream, ry);
            GG_Read(inStream, rz);
            GG_Read(inStream, rw);
            //if(MODEL == 45) std::cout << "R " << rx << ", " << ry << ", " << rz << '\n';
            //std::cout << "      -Center: " << x << ", " << y << ", " << z << '\n';
            float sx,sz,sy;
            GG_Read(inStream, sx);
            GG_Read(inStream, sy);
            GG_Read(inStream, sz);
            //if(MODEL == 45) std::cout << "Size " << sx << ", " << sy << ", " << sz << '\n';
            //std::cout << "      -Size: " << x << ", " << y << ", " << z << '\n';
            CSimpleStaticRigidBody* RIGID = new CSimpleStaticRigidBody(x, y, z, rx,ry,rz,rw, sx/2, sy/2, sz/2);
            Manager->addComponentToEntity(RIGID, gg::SIMPLESTATICRIGIDBODY, NewEntity);
        }

        //if(MODEL == 45) std::cout << '\n';

    }
}


bool BinaryParser::ImportMesh(
    const std::string& BinaryFile,
    std::vector<float> &PositionsNormals,
    std::vector<float> &uv,
    std::vector<float> &TangentsBitangents,
    std::vector<unsigned short> &index
){

    PositionsNormals.clear();
    uv.clear();
    TangentsBitangents.clear();
    index.clear();

    std::ifstream Model(BinaryFile, std::ios::binary);

    uint16_t i = 0;
    float FloatV;
    GG_Read(Model, i);  // POSITIONS_AND_NORMALS_SIZE
    PositionsNormals.reserve(i);
    while(i--){
        GG_Read(Model, FloatV);
        PositionsNormals.emplace_back(FloatV);
    }

    GG_Read(Model, i);  // UV_COORDS_SIZE
    uv.reserve(i);
    while(i--){
        GG_Read(Model, FloatV);
        uv.emplace_back(FloatV);
    }

    GG_Read(Model, i);  // TANGENTS_AND_BITANGENTS_SIZE
    TangentsBitangents.reserve(i);
    while(i--){
        GG_Read(Model, FloatV);
        TangentsBitangents.emplace_back(FloatV);
    }

    GG_Read(Model, i);  // INDEX_SIZE
    index.reserve(i);
    unsigned short UnsignedShortV = 0;
    while(i--){
        GG_Read(Model, UnsignedShortV);
        index.emplace_back(UnsignedShortV);
    }

    return true;
}

void BinaryParser::ReadEventsData(const std::string &BinaryFile){
    std::ifstream inStream(BinaryFile, std::ios::binary);
    Factory *fac = Singleton<Factory>::Instance();

    uint8_t TOTAL = 0;
    uint8_t EVENT;
    GG_Read(inStream,TOTAL);

    // std::cout << " --- EVENT TOTAL : " << static_cast<int>(TOTAL) << " --- " << '\n';

    for (size_t i=0 ; i<TOTAL; ++i) {
        EVENT = 0;
        GG_Read(inStream,EVENT);

        if(EVENT == 0){
            // Armas
            uint8_t arma;
            GG_Read(inStream,arma);

            float x,y,z;
            GG_Read(inStream,x);
            GG_Read(inStream,y);
            GG_Read(inStream,z);
            glm::vec3 position(x,y,z);

            // std::cout << " - Arma     : " << static_cast<int>(arma) << '\n';
            // std::cout << "   |  - POS : " << "(" << x << "," << y << "," << z << ")" << '\n';
            // std::cout << '\n';

            fac->createCollectableWeapon(position, arma);
        }
        else{
            // Touchables y pickables
            // NOTA INFORMATIVA: NUNCA ningun pickable va solo

            uint8_t obj;
            GG_Read(inStream,obj);

            // Touchable
            float x,y,z;
            float rx,ry,rz;

            // Collider del touchable
            float cx,cy,cz;
            float crx,cry,crz,crw;
            float csx,csy,csz;

            // Toggle del touchable
            float tx,ty,tz;
            float trx,tory,trz;

            // Collider del toggle del touchable
            float tcx,tcy,tcz;
            float tcrx,tcry,tcrz,tcrw;
            float tcsx,tcsy,tcsz;

            // Pickable
            float px,py,pz;

            GG_Read(inStream,x);
            GG_Read(inStream,y);
            GG_Read(inStream,z);

            GG_Read(inStream,rx);
            GG_Read(inStream,ry);
            GG_Read(inStream,rz);

            // std::cout << " - Touchable: " << static_cast<int>(obj) << '\n';
            // std::cout << "   |  - POS : " << "(" << x << "," << y << "," << z << ")" << '\n';
            // std::cout << "   |  - ROT : " << "(" << rx << "," << ry << "," << rz << ")" << '\n';

            uint8_t hasCollider;
            GG_Read(inStream,hasCollider);
            if(hasCollider){
                GG_Read(inStream,cx);
                GG_Read(inStream,cy);
                GG_Read(inStream,cz);

                GG_Read(inStream,crx);
                GG_Read(inStream,cry);
                GG_Read(inStream,crz);
                GG_Read(inStream,crw);

                GG_Read(inStream,csx);
                GG_Read(inStream,csy);
                GG_Read(inStream,csz);

                // std::cout << "   |  Has collider    : " << '\n';
                // std::cout << "      |  - POS        : " << "(" << cx << "," << cy << "," << cz << ")" << '\n';
                // std::cout << "      |  - ROT        : " << "(" << crx << "," << cry << "," << crz << "[" << crw << "])" << '\n';
                // std::cout << "      |  - SIZE       : " << "(" << csx << "," << csy << "," << csz << ")" << '\n';
            }
            else{
                // std::cout << "   |  No collider" << '\n';
            }

            // Toggle
            uint8_t toggleObj;
            GG_Read(inStream,toggleObj);

            GG_Read(inStream,tx);
            GG_Read(inStream,ty);
            GG_Read(inStream,tz);

            // Pongo tory en vez de try porque sino al compilador le peta la cabeza
            GG_Read(inStream,trx);
            GG_Read(inStream,tory);
            GG_Read(inStream,trz);

            // std::cout << "   |  Has toggle      : " << '\n';
            // std::cout << "      |  - OBJ        : " << static_cast<int>(toggleObj) << '\n';
            // std::cout << "      |  - POS        : " << "(" << tx << "," << ty << "," << tz << ")" << '\n';
            // std::cout << "      |  - ROT        : " << "(" << trx << "," << tory << "," << trz << ")" << '\n';

            uint8_t toggleHasCollider;
            GG_Read(inStream,toggleHasCollider);
            if(toggleHasCollider){
                GG_Read(inStream,tcx);
                GG_Read(inStream,tcy);
                GG_Read(inStream,tcz);

                GG_Read(inStream,tcrx);
                GG_Read(inStream,tcry);
                GG_Read(inStream,tcrz);
                GG_Read(inStream,tcrw);

                GG_Read(inStream,tcsx);
                GG_Read(inStream,tcsy);
                GG_Read(inStream,tcsz);

                // std::cout << "      |  Toggle has collider  : " << '\n';
                // std::cout << "         |  - POS             : " << "(" << tcx << "," << tcy << "," << tcz << ")" << '\n';
                // std::cout << "         |  - ROT             : " << "(" << tcrx << "," << tcry << "," << tcrz << "[" << tcrw << "])" << '\n';
                // std::cout << "         |  - SIZE            : " << "(" << tcsx << "," << tcsy << "," << tcsz << ")" << '\n';
            }
            else{
                // std::cout << "      |  Toggle has no collider" << '\n';
            }

            // Pickable?
            uint8_t hasPickable;
            GG_Read(inStream,hasPickable);
            if(hasPickable){
                GG_Read(inStream,px);
                GG_Read(inStream,py);
                GG_Read(inStream,pz);

                // std::cout << "   |  Has pickable    : " << '\n';
                // std::cout << "      |  - POS        : " << "(" << px << "," << py << "," << pz << ")" << '\n';
            }
            else{
                // std::cout << "   |  No Pickable" << '\n';
            }

            auto Manager = Singleton<ObjectManager>::Instance();
            ZMaterial* Dark = AssetManager::getMaterial("Morado");
            uint16_t NewEntity = Manager->createEntity();

            std::string str = "assets/BinaryFiles/BinaryModels/"+std::to_string(obj)+".modelgg";
            glm::vec3 Position(x,y,z);
            glm::vec3 Rotation(rx,ry,rz);

            // PUERTA
            CStaticModel* Transform = new CStaticModel(str, Dark, Position, Rotation);
            Manager->addComponentToEntity(Transform, gg::STATICMODEL, NewEntity);

            if(hasCollider){
                CRigidBody* RIGID = new CRigidBody(cx, cy, cz, crx,cry,crz,crw, csx/2, csy/2, csz/2);
                Manager->addComponentToEntity(RIGID, gg::RIGID_BODY, NewEntity);
            }

            // LLAVE
            uint16_t key = 0;
            if(hasPickable){
                Position = glm::vec3(px,py,pz);
                key = fac->createPickableItem(Position);
            }

            str = "assets/BinaryFiles/BinaryModels/"+std::to_string(toggleObj)+".modelgg";
            Position = glm::vec3(tx,ty,tz);
            Rotation = glm::vec3(trx,tory,trz);
            glm::vec3 Vel(0.0,0.1,0.0);

            // INTERRUPTOR
            uint16_t NewToggle = fac->createTouchableObject(str,Position,Rotation,NewEntity,Vel,3200,key);

            if(toggleHasCollider){
                CSimpleStaticRigidBody* RIGID = new CSimpleStaticRigidBody(tcx, tcy, tcz, tcrx,tcry,tcrz,tcrw, tcsx/2, tcsy/2, tcsz/2);
                Manager->addComponentToEntity(RIGID, gg::SIMPLESTATICRIGIDBODY, NewToggle);
            }



            std::cout << '\n';
        }
    }





}

void BinaryParser::ReadLoadZonesData(const std::string &BinaryFile){
    std::ifstream inStream(BinaryFile, std::ios::binary);
    CTriggerSystem* TS = Singleton<CTriggerSystem>::Instance();

    uint8_t TOTAL;
    GG_Read(inStream,TOTAL);
    std::cout << "TOTAL LOADERS: " << static_cast<int>(TOTAL) << '\n';

    for(int i=0 ; i<TOTAL ; ++i){
        uint8_t ZONE;
        GG_Read(inStream,ZONE);

        float x,y,z;
        GG_Read(inStream,x);
        GG_Read(inStream,y);
        GG_Read(inStream,z);
        glm::vec3 Position(x,y,z);

        TData mes;
        mes.add(kDat_LoadThatZone,ZONE);
        TS->RegisterTriger(kTrig_LoadZone,1,0,Position, 5, 0, false, mes);
    }


}
