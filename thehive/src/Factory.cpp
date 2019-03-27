#include "Factory.hpp"
#include <ComponentArch/Components/CGranade.hpp>
#include <ComponentArch/Components/CGranade0.hpp>
#include <ComponentArch/Components/CGranade1.hpp>
#include <ComponentArch/Components/CGranade2.hpp>
#include <SurrealEngine/ZMaterial.hpp>
#include <SurrealEngine/AssetManager.hpp>
#include <SurrealEngine/ZStaticMesh.hpp>

Factory::Factory() {
    Manager = Singleton<ObjectManager>::Instance();
    Engine = Singleton<SurrealEngine>::Instance();

}

uint16_t Factory::createHero(const glm::vec3 &Position,int8_t _b) {


    ZMaterial* moradoDeLos80 = Singleton<AssetManager>::Instance()->getMaterial("Hero");

    uint16_t hero = Manager->createEntity();
    CTransform* Transform               = new CTransform(glm::vec3(Position.x, Position.y, Position.z), glm::vec3(0, 0, 0));
    Manager->addComponentToEntity(Transform,        gg::TRANSFORM, hero);

    ZStaticMesh::setPlayerPtr(&(Transform->Position));
    CAIEnem::PlayerTransform=Transform;

    CCamera* Camera                     = new CCamera(_b);
    Camera->setTarget(Transform);
    Manager->addComponentToEntity(Camera,           gg::CAMERA, hero);
    ZStaticMesh::setCameraPtr(&(Camera->CurrentPosition));

    CVida* Vida                         = new CVida(1000);
    Manager->addComponentToEntity(Vida,             gg::VIDA, hero);

    CHabilityController* Hab                         = new CHabilityController();
    Manager->addComponentToEntity(Hab,             gg::HAB, hero);

    CDynamicModel* DynamicModel       = new CDynamicModel(moradoDeLos80);
    Manager->addComponentToEntity(DynamicModel, gg::DYNAMICMODEL, hero);
    DynamicModel->AddAnimation(Singleton<AssetManager>::Instance()->getAnimation("Hero_Standing"));
    DynamicModel->AddAnimation(Singleton<AssetManager>::Instance()->getAnimation("Hero_Walking"));
    DynamicModel->ToggleAnimation(0, 2);

    CRigidBody* RigidBody               = new CRigidBody(false, false,"", Position.x, Position.y, Position.z, 0.581/2,1.89/2, 0.314/2, 50, 0,0,0);
    Manager->addComponentToEntity(RigidBody,        gg::RIGID_BODY, hero);

    CPlayerController* PlayerController = new CPlayerController();
    Manager->addComponentToEntity(PlayerController, gg::PLAYERCONTROLLER, hero);

    // std::string Disparo_pistola = "event:/SFX/Armas/Pistola/PistolaDisparo";
    // std::string Recarga_pistola = "event:/SFX/Armas/Pistola/PistolaRecarga";
    // std::string Desen_pistola = "event:/SFX/Armas/Pistola/PistolaDesenfundado";
    // std::string Vacia_pistola = "event:/SFX/Armas/Pistola/PistolaVacia";

    std::string sonido_disparo,sonido_recarga,sonido_desenfundado,sonido_vacia,img;
    float dmg,cdc,relDT,rng;
    int tb;
    int _type = 0;
    gg::getWeaponInformation(dmg,cdc,relDT,rng,tb,_type,sonido_disparo,sonido_recarga,sonido_desenfundado, sonido_vacia,img);





    CGun *gun = new CGun(dmg,cdc,tb,relDT,rng,_type, sonido_disparo, sonido_recarga, sonido_desenfundado, sonido_vacia);
    Manager->addComponentToEntity(gun, gg::GUN, hero);

    Singleton<Motor2D>::Instance()->setWeaponImg(0,img);
    Singleton<Motor2D>::Instance()->setbullet(0,gun->getBullets(),gun->getTotalBullets());

    CAgent* Agent                       = new CAgent(kTrig_Gunfire/*|kTrig_Explosion*/|kTrig_Touchable|kTrig_Pickable|kTrig_ExpansiveWave|kTrig_LoadZone|kTrig_UnLoadZone);
    Manager->addComponentToEntity(Agent, gg::AGENT, hero);

    Manager->setHeroID(hero);

    return hero;
}

uint16_t Factory::createSoldierWandering(const glm::vec3 &Position,const float &health){
    uint16_t Enemy =createSoldier(Position,health);

    CAIEnem* AIEnem                     = new CAIEnem(gg::SOLDIER,30,Position,false);
    Manager->addComponentToEntity(AIEnem, gg::AIENEM, Enemy);

    CNavmeshAgent* NavmeshAgent         = new CNavmeshAgent();
    Manager->addComponentToEntity(NavmeshAgent, gg::NAVMESHAGENT, Enemy);

    return Enemy;

}
uint16_t Factory::createSoldierHorda(const glm::vec3 &Position,const float &health,const glm::vec3 &Position2){
    uint16_t Enemy =createSoldier(Position,health);

    CAIEnem* AIEnem                     = new CAIEnem(gg::SOLDIER,30,Position2,true);
    Manager->addComponentToEntity(AIEnem, gg::AIENEM, Enemy);

    CNavmeshAgent* NavmeshAgent         = new CNavmeshAgent();
    Manager->addComponentToEntity(NavmeshAgent, gg::NAVMESHAGENT, Enemy);

    return Enemy;

}
uint16_t Factory::createSoldier(const glm::vec3 &Position,const float &health){
    uint16_t Enemy = Manager->createEntity();
    ZMaterial* moradoDeLos80 = Singleton<AssetManager>::Instance()->getMaterial("Soldier");


    CTransform* Transform               = new CTransform(Position, glm::vec3(0, 0, 0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Enemy);

    CDynamicModel* DynamicModel       = new CDynamicModel(moradoDeLos80);
    Manager->addComponentToEntity(DynamicModel, gg::DYNAMICMODEL, Enemy);
    DynamicModel->AddAnimation(Singleton<AssetManager>::Instance()->getAnimation("Soldier_Running"));
    DynamicModel->ToggleAnimation(0, 2);

    CRigidBody* RigidBody               = new CRigidBody(false, true,"assets/BoundingBoxes/Hero.bullet", Position.x, Position.y, Position.z, -1,-1,-1, 80, 0,0,0, 0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Enemy);

    CAgent* Agent                       = new CAgent(kTrig_ExpansiveForce|kTrig_Aturd|kTrig_EnemyNear|kTrig_Shoot|kTrig_Senyuelo|kTrig_Explosion|kTrig_DeadAlien);
    Manager->addComponentToEntity(Agent, gg::AGENT, Enemy);


    CVida* Vida                         = new CVida(health);
    Manager->addComponentToEntity(Vida,   gg::VIDA, Enemy);

    return Enemy;
}

uint16_t Factory::createRusher(const glm::vec3 &Position,const float &health){
    uint16_t Enemy = Manager->createEntity();
    ZMaterial* moradoDeLos80 = Singleton<AssetManager>::Instance()->getMaterial("Morado");


    CTransform* Transform               = new CTransform(Position, glm::vec3(0, 0, 0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Enemy);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/BinaryFiles/BinaryModels/SOLDIER.modelgg", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Enemy);

    CRigidBody* RigidBody               = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet", Position.x, Position.y, Position.z, -1,-1,-1, 80, 0,0,0, 0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Enemy);

    CAgent* Agent                       = new CAgent(kTrig_ExpansiveForce|kTrig_Aturd|kTrig_EnemyNear|kTrig_Shoot|kTrig_Senyuelo|kTrig_Explosion|kTrig_DeadAlien);
    Manager->addComponentToEntity(Agent, gg::AGENT, Enemy);

    CAIEnem* AIEnem                     = new CAIEnem(gg::RUSHER,30,Position,false);
    Manager->addComponentToEntity(AIEnem, gg::AIENEM, Enemy);

    CVida* Vida                         = new CVida(health);
    Manager->addComponentToEntity(Vida,   gg::VIDA, Enemy);

    CNavmeshAgent* NavmeshAgent         = new CNavmeshAgent();
    Manager->addComponentToEntity(NavmeshAgent, gg::NAVMESHAGENT, Enemy);

    return Enemy;
}

uint16_t Factory::createTank(const glm::vec3 &Position,const float &health){
    uint16_t Enemy = Manager->createEntity();
    ZMaterial* moradoDeLos80 = Singleton<AssetManager>::Instance()->getMaterial("Morado");


    CTransform* Transform               = new CTransform(Position, glm::vec3(0, 0, 0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Enemy);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/BinaryFiles/BinaryModels/Cube.modelgg", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Enemy);

    CRigidBody* RigidBody               = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet", Position.x, Position.y, Position.z, -1,-1,-1, 50, 0,0,0, 0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Enemy);

    CAgent* Agent                       = new CAgent(kTrig_ExpansiveForce|kTrig_Aturd|kTrig_EnemyNear|kTrig_Shoot|kTrig_Senyuelo|kTrig_Explosion|kTrig_DeadAlien);
    Manager->addComponentToEntity(Agent, gg::AGENT, Enemy);

    CAIEnem* AIEnem                     = new CAIEnem(gg::TANK,30,Position,false);
    Manager->addComponentToEntity(AIEnem, gg::AIENEM, Enemy);

    CVida* Vida                         = new CVida(health);
    Manager->addComponentToEntity(Vida,   gg::VIDA, Enemy);

    CNavmeshAgent* NavmeshAgent         = new CNavmeshAgent();
    Manager->addComponentToEntity(NavmeshAgent, gg::NAVMESHAGENT, Enemy);

    return Enemy;
}

uint16_t Factory::createSingleSwarm(const glm::vec3 &Position,const float &health){
    uint16_t Enemy = Manager->createEntity();
    ZMaterial* moradoDeLos80 = Singleton<AssetManager>::Instance()->getMaterial("Morado");

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    CTransform* Transform               = new CTransform(Position, glm::vec3(0, 0, 0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Enemy);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/BinaryFiles/BinaryModels/Cube.modelgg", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Enemy);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/bullet.bullet",  Position.x,Position.y,Position.z, 1,1,1, 5, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Enemy);

    CAgent* Agent                       = new CAgent(kTrig_ExpansiveForce|kTrig_Aturd|kTrig_EnemyNear|kTrig_Shoot|kTrig_Senyuelo|kTrig_Explosion|kTrig_DeadAlien);
    Manager->addComponentToEntity(Agent, gg::AGENT, Enemy);

    CAIEnem* AIEnem                     = new CAIEnem(gg::SWARM,30,Position,false);
    Manager->addComponentToEntity(AIEnem, gg::AIENEM, Enemy);

    CVida* Vida                         = new CVida(health);
    Manager->addComponentToEntity(Vida,   gg::VIDA, Enemy);

    CNavmeshAgent* NavmeshAgent         = new CNavmeshAgent();
    Manager->addComponentToEntity(NavmeshAgent, gg::NAVMESHAGENT, Enemy);

    //    return RigidBody;
    return Enemy;
}
uint16_t Factory::createSwarm( const glm::vec3 &Position,const float &health) {
    uint16_t holyBomb = createSingleSwarm(Position,health);



    CFlock* cFlock = new CFlock(true,holyBomb);
    float rango=15;
    for (size_t i = 0; i < 15; i++) {
        auto deltapos = glm::vec3(gg::genIntRandom(0, 2*rango)-rango,0,gg::genIntRandom(0, 2*rango)-rango);
        cFlock->addNewFlocked(createSingleSwarm(Position+deltapos,health));//4
    }
        Manager->addComponentToEntity(cFlock, gg::FLOCK, holyBomb);

    return holyBomb;
}
// uint16_t Factory::createCollisionableStaticModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const glm::vec3 &Position) {
//     uint16_t CollisionableStaticObject = Manager->createEntity();
//     Material yelo(Texture);
//
//     CTransform* Transform = new CTransform(glm::vec3(0,0,0),glm::vec3(0,0,0));
//     Manager->addComponentToEntity(Transform, gg::TRANSFORM, CollisionableStaticObject);
//
//     CRenderable_3D* Renderable_3D = new CRenderable_3D(Path, yelo);
//     Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, CollisionableStaticObject);
//
//     CRigidBody* RigidBody = new CRigidBody(false, true,BulletPath, Position.x, Position.y, Position.z, -1,-1,-1, 0, 0,0,0, 0.2);
//     Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, CollisionableStaticObject);
//
//     return CollisionableStaticObject;
// }

// uint16_t Factory::createCollisionableDynamicModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const glm::vec3 &Position) {
//     uint16_t CollisionableDynamicObject = Manager->createEntity();
//     Material yelo(Texture);
//
//     CTransform* Transform = new CTransform(glm::vec3(0,0,0),glm::vec3(0,0,0));
//     Manager->addComponentToEntity(Transform, gg::TRANSFORM, CollisionableDynamicObject);
//
//     CRenderable_3D* Renderable_3D = new CRenderable_3D(Path, yelo);
//     Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, CollisionableDynamicObject);
//
//     CRigidBody* RigidBody = new CRigidBody(true,true,BulletPath, Position.x, Position.y, Position.z, -1,-1,-1, 500, 0,0,0);
//     Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, CollisionableDynamicObject);
//
//     return CollisionableDynamicObject;
// }
//
// uint16_t Factory::createStaticModel(const std::string &Path, const std::string &Texture, const glm::vec3 &Position, const glm::vec3 &Rotation) {
//     uint16_t CollisionableStaticObject = Manager->createEntity();
//     Material yelo(Texture);
//
//     CTransform* Transform = new CTransform(Position, Rotation);
//     Manager->addComponentToEntity(Transform, gg::TRANSFORM, CollisionableStaticObject);
//
//     CRenderable_3D* Renderable_3D = new CRenderable_3D(Path, yelo);
//     Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, CollisionableStaticObject);
//
//     return CollisionableStaticObject;
// }

uint16_t Factory::createPathFindingActor(const glm::vec3 &Position) {
    uint16_t Actor1 = Manager->createEntity();
    ZMaterial* Blue = Singleton<AssetManager>::Instance()->getMaterial("Blue");


    CTransform* Transform = new CTransform(Position, glm::vec3(0,0,0));   // 300, 0, 700
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Actor1);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/BinaryFiles/BinaryModels/Cube.modelgg", Blue);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Actor1);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet", Position.x, Position.y, Position.z, -1,-1,-1, 50, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Actor1);

    CNavmeshAgent* NavmeshAgent = new CNavmeshAgent();
    Manager->addComponentToEntity(NavmeshAgent, gg::NAVMESHAGENT, Actor1);

    return Actor1;
}

uint16_t Factory::createSenyuelo( const glm::vec3 &Position, const glm::vec3 &Impulse) {
    uint16_t holyBomb = Manager->createEntity();
    ZMaterial* Blue = Singleton<AssetManager>::Instance()->getMaterial("Blue");


    CTransform* Transform = new CTransform(Position, glm::vec3(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, holyBomb);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/BinaryFiles/BinaryModels/Cube.modelgg", Blue);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, holyBomb);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/bullet.bullet",  Position.x,Position.y,Position.z, 1,1,1, 5, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, holyBomb);

    CGranade* Granade = new CGranade2();
    Manager->addComponentToEntity(Granade, gg::GRANADE, holyBomb);

    RigidBody->applyCentralForce(Impulse);

    return holyBomb;
}
uint16_t Factory::createMatriuska( const glm::vec3 &Position, const glm::vec3 &Impulse) {
    uint16_t holyBomb = Manager->createEntity();
    ZMaterial* Blue = Singleton<AssetManager>::Instance()->getMaterial("Blue");

    CTransform* Transform = new CTransform(Position, glm::vec3(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, holyBomb);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/BinaryFiles/BinaryModels/Cube.modelgg", Blue);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, holyBomb);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/bullet.bullet",  Position.x,Position.y,Position.z, 1,1,1, 5, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, holyBomb);

    CGranade* Granade = new CGranade1();
    Manager->addComponentToEntity(Granade, gg::GRANADE, holyBomb);

    RigidBody->applyCentralForce(Impulse);

    return holyBomb;
}
uint16_t Factory::createHolyBomb( const glm::vec3 &Position, const glm::vec3 &Impulse) {
    uint16_t holyBomb = Manager->createEntity();
    ZMaterial* Blue = Singleton<AssetManager>::Instance()->getMaterial("Blue");

    CTransform* Transform = new CTransform(Position, glm::vec3(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, holyBomb);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/BinaryFiles/BinaryModels/Cube.modelgg", Blue);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, holyBomb);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/bullet.bullet",  Position.x,Position.y,Position.z, 1,1,1, 5, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, holyBomb);

    CGranade* Granade = new CGranade0();
    Manager->addComponentToEntity(Granade, gg::GRANADE, holyBomb);

    RigidBody->applyCentralForce(Impulse);

    return holyBomb;
}

uint16_t Factory::createCollectableWeapon(const glm::vec3 &_position, int _weaponType){
    uint16_t weapon = Manager->createEntity();
    ZMaterial* Blue = Singleton<AssetManager>::Instance()->getMaterial("Blue");

    CTransform *transform = new CTransform(_position, glm::vec3(0,0,0));
    Manager->addComponentToEntity(transform, gg::TRANSFORM, weapon);

    CRenderable_3D *renderable = new CRenderable_3D("assets/BinaryFiles/BinaryModels/escopeta.modelgg", Blue);
    Manager->addComponentToEntity(renderable, gg::RENDERABLE_3D, weapon);

    CRigidBody *rigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet",  _position.x,_position.y,_position.z, -1,-1,-1, 25, 0,0,0);
    Manager->addComponentToEntity(rigidBody, gg::RIGID_BODY, weapon);

    TData mes;
    mes.add(kDat_EntId,weapon);
    mes.add(kDat_WeaponType,_weaponType);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_Gunfire,1,weapon,_position, 3, 0, true, mes);

    return weapon;
}

uint16_t Factory::createPickableItem(const glm::vec3 &_position){
    uint16_t item = Manager->createEntity();
    ZMaterial* moradoDeLos80 = Singleton<AssetManager>::Instance()->getMaterial("Morado");


    CTransform *transform = new CTransform(_position, glm::vec3(0,0,0));
    Manager->addComponentToEntity(transform, gg::TRANSFORM, item);

    CRenderable_3D *renderable = new CRenderable_3D("assets/BinaryFiles/BinaryModels/fusible.modelgg", moradoDeLos80);
    Manager->addComponentToEntity(renderable, gg::RENDERABLE_3D, item);

    // CRigidBody *rigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/weapon.bullet",  _position.x,_position.y,_position.z, -1,-1,-1, 25, 0,0,0);
    // Manager->addComponentToEntity(rigidBody, gg::RIGID_BODY, item);
    CSimpleStaticRigidBody* RIGID = new CSimpleStaticRigidBody(_position.x, _position.y, _position.z, 0,0,0,1, 0.5, 0.5, 0.5);
    Manager->addComponentToEntity(RIGID, gg::SIMPLESTATICRIGIDBODY, item);

    TData mes;
    mes.add(kDat_PickableItemId,item);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_Pickable,1,item,_position, 2.5, 0, true, mes);

    return item;
}

uint16_t Factory::createTouchableObject(const std::string &_path, const glm::vec3 &_position, const glm::vec3 &_rotation, const uint16_t &_id, const glm::vec3 &vel, const int &_dur, int type, uint16_t _item){
    uint16_t t_obj = Manager->createEntity();
    ZMaterial* moradoDeLos80=Singleton<AssetManager>::Instance()->getMaterial("Grey");

    if (type==1)
    moradoDeLos80 = Singleton<AssetManager>::Instance()->getMaterial("Grey");

    else
    moradoDeLos80 = Singleton<AssetManager>::Instance()->getMaterial("Red");

    // t_obj    : Objeto que va a disparar el evento
    // _position: Posicion del interruptor
    //   _id    : "Puerta" que se va a abrir
    //   vel    : Vector movimiento del evento
    //  _dur    : Duracion de la animacion
    // _item    : Objeto en concreto para disparar el evento

    CTransform *transform = new CTransform(_position, _rotation);
    Manager->addComponentToEntity(transform, gg::TRANSFORM, t_obj);

    CRenderable_3D *renderable = new CRenderable_3D(_path, moradoDeLos80);
    Manager->addComponentToEntity(renderable, gg::RENDERABLE_3D, t_obj);

    // CRigidBody *rigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet",  _position.x,_position.y,_position.z, -1,-1,-1, 25, 0,0,0);
    // Manager->addComponentToEntity(rigidBody, gg::RIGID_BODY, t_obj);

    TData mes;
    mes.add(kDat_EntId,_id);
    mes.add(kDat_Action,Action_MoverObjeto);
    mes.add(kDat_Done,false);
    if(_item){
        mes.add(kDat_PickableItemId,_item);
    }

    Blackboard b;
    BRbData *data = new BRbData(gg::RBActionStruct(vel.x,vel.y,vel.z));
    BFloat *data_time = new BFloat(_dur);
    b.GLOBAL_setData("DATA_"+std::to_string(_id)            ,data);
    b.GLOBAL_setData("DATA_"+std::to_string(_id)+"_TIME"    ,data_time);

    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_Touchable,1,t_obj,_position, 5, 0, true, mes);

    return t_obj;
}

uint16_t Factory::createDebugBullet(const glm::vec3 &_pos){
    uint16_t debug = Manager->createEntity();
    ZMaterial* Blue = Singleton<AssetManager>::Instance()->getMaterial("Blue");

    CTransform* Transform               = new CTransform(_pos, glm::vec3(0, 0, 0));
    Manager->addComponentToEntity(Transform,        gg::TRANSFORM, debug);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/BinaryFiles/BinaryModels/Cube.modelgg", Blue);
    Manager->addComponentToEntity(Renderable_3D,    gg::RENDERABLE_3D, debug);

    return debug;
}

uint16_t Factory::createNatureMesh(const std::string &Path, const glm::vec3 &Position, const glm::vec3 &Rotation, ZMaterial *Material, const uint8_t &map_zone){
    uint16_t Nature = Manager->createEntity();

    // CTransform* Transform               = new CTransform(Position,Rotation);
    // Manager->addComponentToEntity(Transform, gg::TRANSFORM, Nature);

    CStaticModel* Transform = new CStaticModel(Path, Material, Position, Rotation, map_zone);
    Manager->addComponentToEntity(Transform, gg::STATICMODEL, Nature);

    // Por ahora se deja para debugear por si no se ve en pantalla
    // CRigidBody* RigidBody               = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet", Position.x, Position.y, Position.z, -1,-1,-1, 80, 0,0,0, 0);
    // Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Nature);

    return Nature;
}
