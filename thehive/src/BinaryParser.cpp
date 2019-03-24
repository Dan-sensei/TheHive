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

    ////std::cout << "NUM " << (uint16_t)NUMBER_OF_OBJECTS << '\n';

    for(uint16_t i = 0; i < NUMBER_OF_OBJECTS; ++i){
        uint8_t MODEL = 0;
        GG_Read(inStream, MODEL);
        std::string str = std::to_string(MODEL);
        std::string lod = str + "_LOD1.modelgg";
        auto Manager = Singleton<ObjectManager>::Instance();
        uint16_t NewEntity = Manager->createEntity();

        float x,y,z;
        GG_Read(inStream, x);
        GG_Read(inStream, y);
        GG_Read(inStream, z);
        glm::vec3 Position(x,y,z);

        GG_Read(inStream, x);
        GG_Read(inStream, y);
        GG_Read(inStream, z);
        glm::vec3 Rotation(x,y,z);

        bool HasCollider;
        GG_Read(inStream, HasCollider);
        ZMaterial* Dark;
        //if(MODEL==2){
        //     Dark = AssetManager::getMaterial("building");
        //}else{
        //     Dark = AssetManager::getMaterial("Default");
        //}
        Dark = AssetManager::getMaterial("Default");
        std::string B = "assets/BinaryFiles/BoundingBoxes/"+str+".bb";
        CStaticModel* Transform = new CStaticModel("assets/BinaryFiles/BinaryModels/"+str+".modelgg", Dark, Position, Rotation, map_zone, B);
        Manager->addComponentToEntity(Transform, gg::STATICMODEL, NewEntity);
        Transform->addLOD("assets/BinaryFiles/BinaryModels/"+lod);

        if(HasCollider){
            GG_Read(inStream, x);
            GG_Read(inStream, y);
            GG_Read(inStream, z);

            float rx, ry, rz, rw;
            GG_Read(inStream, rx);
            GG_Read(inStream, ry);
            GG_Read(inStream, rz);
            GG_Read(inStream, rw);

            float sx,sz,sy;
            GG_Read(inStream, sx);
            GG_Read(inStream, sy);
            GG_Read(inStream, sz);

            CSimpleStaticRigidBody* RIGID = new CSimpleStaticRigidBody(x, y, z, rx,ry,rz,rw, sx/2, sy/2, sz/2);
            Manager->addComponentToEntity(RIGID, gg::SIMPLESTATICRIGIDBODY, NewEntity);
        }

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
    if (!Model.is_open()) return false;

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

bool BinaryParser::ReadBoundingBox(const std::string &BinaryFile, BoundingBox* THE_BOX){
    std::ifstream Model(BinaryFile, std::ios::binary);
    if (!Model.is_open()) return false;

    GG_Read(Model, THE_BOX->BLF.x); GG_Read(Model, THE_BOX->BLF.y); GG_Read(Model, THE_BOX->BLF.z);
    GG_Read(Model, THE_BOX->BRF.x); GG_Read(Model, THE_BOX->BRF.y); GG_Read(Model, THE_BOX->BRF.z);
    GG_Read(Model, THE_BOX->URF.x); GG_Read(Model, THE_BOX->URF.y); GG_Read(Model, THE_BOX->URF.z);
    GG_Read(Model, THE_BOX->ULF.x); GG_Read(Model, THE_BOX->ULF.y); GG_Read(Model, THE_BOX->ULF.z);
    GG_Read(Model, THE_BOX->ULB.x); GG_Read(Model, THE_BOX->ULB.y); GG_Read(Model, THE_BOX->ULB.z);
    GG_Read(Model, THE_BOX->URB.x); GG_Read(Model, THE_BOX->URB.y); GG_Read(Model, THE_BOX->URB.z);
    GG_Read(Model, THE_BOX->BRB.x); GG_Read(Model, THE_BOX->BRB.y); GG_Read(Model, THE_BOX->BRB.z);
    GG_Read(Model, THE_BOX->BLB.x); GG_Read(Model, THE_BOX->BLB.y); GG_Read(Model, THE_BOX->BLB.z);

    return true;
}


void BinaryParser::ReadEventsData(const std::string &BinaryFile){
    std::ifstream inStream(BinaryFile, std::ios::binary);
    Factory *fac = Singleton<Factory>::Instance();

    uint8_t TOTAL = 0;
    uint8_t EVENT;
    GG_Read(inStream,TOTAL);

    // //std::cout << "EVENT TOTAL : " << static_cast<int>(TOTAL) << " --- " << '\n';

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

            // //std::cout << " - Arma     : " << static_cast<int>(arma) << '\n';
            // //std::cout << "   |  - POS : " << "(" << x << "," << y << "," << z << ")" << '\n';
            // //std::cout << '\n';

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

            // //std::cout << " - Touchable: " << static_cast<int>(obj) << '\n';
            // //std::cout << "   |  - POS : " << "(" << x << "," << y << "," << z << ")" << '\n';
            // //std::cout << "   |  - ROT : " << "(" << rx << "," << ry << "," << rz << ")" << '\n';

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

                // //std::cout << "   |  Has collider    : " << '\n';
                // //std::cout << "      |  - POS        : " << "(" << cx << "," << cy << "," << cz << ")" << '\n';
                // //std::cout << "      |  - ROT        : " << "(" << crx << "," << cry << "," << crz << "[" << crw << "])" << '\n';
                // //std::cout << "      |  - SIZE       : " << "(" << csx << "," << csy << "," << csz << ")" << '\n';
            }
            else{
                // //std::cout << "   |  No collider" << '\n';
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

            // //std::cout << "   |  Has toggle      : " << '\n';
            // //std::cout << "      |  - OBJ        : " << static_cast<int>(toggleObj) << '\n';
            // //std::cout << "      |  - POS        : " << "(" << tx << "," << ty << "," << tz << ")" << '\n';
            // //std::cout << "      |  - ROT        : " << "(" << trx << "," << tory << "," << trz << ")" << '\n';

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

                // //std::cout << "      |  Toggle has collider  : " << '\n';
                // //std::cout << "         |  - POS             : " << "(" << tcx << "," << tcy << "," << tcz << ")" << '\n';
                // //std::cout << "         |  - ROT             : " << "(" << tcrx << "," << tcry << "," << tcrz << "[" << tcrw << "])" << '\n';
                // //std::cout << "         |  - SIZE            : " << "(" << tcsx << "," << tcsy << "," << tcsz << ")" << '\n';
            }
            else{
                // //std::cout << "      |  Toggle has no collider" << '\n';
            }

            // Pickable?
            uint8_t hasPickable;
            GG_Read(inStream,hasPickable);
            if(hasPickable){
                GG_Read(inStream,px);
                GG_Read(inStream,py);
                GG_Read(inStream,pz);

                // //std::cout << "   |  Has pickable    : " << '\n';
                // //std::cout << "      |  - POS        : " << "(" << px << "," << py << "," << pz << ")" << '\n';
            }
            else{
                // //std::cout << "   |  No Pickable" << '\n';
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

            //std::cout << '\n';
        }
    }
}

void BinaryParser::ReadLoadZonesData(const std::string &BinaryFile){
    std::ifstream inStream(BinaryFile, std::ios::binary);
    CTriggerSystem* TS = Singleton<CTriggerSystem>::Instance();

    uint8_t TOTAL;
    GG_Read(inStream,TOTAL);
    //std::cout << "TOTAL LOADERS: " << static_cast<int>(TOTAL) << '\n';

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
        TS->RegisterTriger(kTrig_LoadZone,1,0,Position, 8, 0, false, mes);
        //std::cout << " - LOAD ZONE " << static_cast<int>(ZONE) << " ON " << glm::to_string(Position) << '\n';
    }
}

void BinaryParser::ReadUnLoadZonesData(const std::string &BinaryFile){
    std::ifstream inStream(BinaryFile, std::ios::binary);
    CTriggerSystem* TS = Singleton<CTriggerSystem>::Instance();

    uint8_t TOTAL;
    GG_Read(inStream,TOTAL);
    //std::cout << "TOTAL UNLOADERS: " << static_cast<int>(TOTAL) << '\n';

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
        TS->RegisterTriger(kTrig_UnLoadZone,1,0,Position, 8, 0, false, mes);
        //std::cout << " - UNLOAD ZONE " << static_cast<int>(ZONE) << " ON " << glm::to_string(Position) << '\n';
    }
}

uint16_t BinaryParser::ReadRespawnNodesData(const std::string &BinaryFile){
    std::ifstream inStream(BinaryFile, std::ios::binary);
    Factory *fac = Singleton<Factory>::Instance();
    AIDirector *Director = Singleton<AIDirector>::Instance();

    uint8_t TOTAL;
    GG_Read(inStream,TOTAL);

    // std::cout << "TOTAL NODES: " << static_cast<int>(TOTAL) << '\n';

    float x,y,z;
    GG_Read(inStream,x);
    GG_Read(inStream,y);
    GG_Read(inStream,z);
    glm::vec3 Position(x,y,z);

    uint16_t HERO = fac->createHero(Position,-1);

    std::vector<AINode*> nodes;
    nodes.reserve(TOTAL);

    for(int i=0 ; i<TOTAL ; ++i){
        GG_Read(inStream,x);
        GG_Read(inStream,y);
        GG_Read(inStream,z);
        Position = glm::vec3(x,y,z);

        nodes.emplace_back(Director->createNode(Position,5));
    }

    auto it = nodes.begin();
    while(it != nodes.end()){
        auto it2 = nodes.begin();

        while(it2 != nodes.end()){
            if(it != it2)   (*it2)->addNode(*it);
            ++it2;
        }
        ++it;
    }

    Director->init();
    nodes.clear();

    return HERO;
}

void BinaryParser::ReadNatureData(const std::string &BinaryFile){
    std::ifstream inStream(BinaryFile, std::ios::binary);
    // Factory *fac = Singleton<Factory>::Instance();
    NatureGenerator nat;

    uint8_t TOTAL,TOTAL_ZONES,ZONE_NUMBER;
    GG_Read(inStream,TOTAL_ZONES);
    // std::cout << "TOTAL_ZONES: " << static_cast<int>(TOTAL_ZONES) << '\n';

    float x,y,z;
    glm::vec3 Position;
    for(int i=0 ; i<TOTAL_ZONES ; ++i){
        GG_Read(inStream,ZONE_NUMBER);
        GG_Read(inStream,TOTAL);
        // std::cout << " | ZONE_NUMBER: " << static_cast<int>(ZONE_NUMBER) << '\n';
        // std::cout << "   | TOTAL_SPAWNS: " << static_cast<int>(TOTAL) << '\n';

        for(int j=0 ; j<TOTAL ; ++j){

            GG_Read(inStream,x);
            GG_Read(inStream,y);
            GG_Read(inStream,z);

            Position = glm::vec3(x,y,z);
            nat.init(ZONE_NUMBER,Position);
            // std::cout << "     | POSITION: " << glm::to_string(Position) << '\n';

        }
    }
}
