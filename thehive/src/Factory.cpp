#include "Factory.hpp"
#include <ComponentArch/Components/CGranade.hpp>
#include <ComponentArch/Components/CGranade0.hpp>
#include <ComponentArch/Components/CGranade1.hpp>
#include <ComponentArch/Components/CGranade2.hpp>

Factory::Factory() {
    Manager = Singleton<ObjectManager>::Instance();
    Engine = Singleton<GameEngine>::Instance();

}

uint16_t Factory::createHero(const gg::Vector3f &Position,bool _b) {
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    uint16_t hero = Manager->createEntity();
    CTransform* Transform               = new CTransform(gg::Vector3f(0, 0, 10), gg::Vector3f(0, 0, 0));
    Manager->addComponentToEntity(Transform,        gg::TRANSFORM, hero);

    CAIEnem::PlayerTransform=Transform;



    CVida* Vida                         = new CVida(1000);
    Manager->addComponentToEntity(Vida,             gg::VIDA, hero);

    CHabilityController* Hab                         = new CHabilityController();
    Manager->addComponentToEntity(Hab,             gg::HAB, hero);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/Models/Hero.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D,    gg::RENDERABLE_3D, hero);

    CRigidBody* RigidBody               = new CRigidBody(false, true,"assets/BoundingBoxes/Hero.bullet", Position.X, Position.Y, Position.Z, -1,-1,-1, 50, 0,0,0);
    Manager->addComponentToEntity(RigidBody,        gg::RIGID_BODY, hero);

    CPlayerController* PlayerController = new CPlayerController();
    Manager->addComponentToEntity(PlayerController, gg::PLAYERCONTROLLER, hero);

    CGun *gun = new CGun(0.4,5,15,0.5,0.5,3);
    Manager->addComponentToEntity(gun, gg::GUN, hero);

    CAgent* Agent                       = new CAgent(kTrig_Gunfire/*|kTrig_Explosion*/|kTrig_Touchable|kTrig_Pickable|kTrig_ExpansiveWave);
    Manager->addComponentToEntity(Agent, gg::AGENT, hero);

    Manager->setHeroID(hero);

    return hero;
}

uint16_t Factory::createSoldier(const gg::Vector3f &Position,const float &health){
    uint16_t Enemy = Manager->createEntity();
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    CTransform* Transform               = new CTransform(Position, gg::Vector3f(0, 0, 0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Enemy);

    CCamera* Camera                     = new CCamera(false);
    Camera->setTarget(Transform);
    Manager->addComponentToEntity(Camera,           gg::CAMERA, Enemy);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/Models/Cube.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Enemy);

    CRigidBody* RigidBody               = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet", Position.X, Position.Y, Position.Z, -1,-1,-1, 80, 0,0,0, 0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Enemy);

    CAgent* Agent                       = new CAgent(kTrig_Aturd|kTrig_EnemyNear|kTrig_Shoot|kTrig_Senyuelo|kTrig_Explosion|kTrig_DeadAlien);
    Manager->addComponentToEntity(Agent, gg::AGENT, Enemy);

    CAIEnem* AIEnem                     = new CAIEnem(gg::SOLDIER,30,Position,false);
    Manager->addComponentToEntity(AIEnem, gg::AIENEM, Enemy);

    CVida* Vida                         = new CVida(health);
    Manager->addComponentToEntity(Vida,   gg::VIDA, Enemy);

    CNavmeshAgent* NavmeshAgent         = new CNavmeshAgent();
    Manager->addComponentToEntity(NavmeshAgent, gg::NAVMESHAGENT, Enemy);

    return Enemy;
}

uint16_t Factory::createTank(const gg::Vector3f &Position,const float &health){
    uint16_t Enemy = Manager->createEntity();
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    CTransform* Transform               = new CTransform(Position, gg::Vector3f(0, 0, 0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Enemy);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/Models/Cube.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Enemy);

    CRigidBody* RigidBody               = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet", Position.X, Position.Y, Position.Z, -1,-1,-1, 50, 0,0,0, 0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Enemy);

    CAgent* Agent                       = new CAgent(kTrig_Aturd|kTrig_EnemyNear|kTrig_Shoot|kTrig_Senyuelo|kTrig_Explosion|kTrig_DeadAlien);
    Manager->addComponentToEntity(Agent, gg::AGENT, Enemy);

    CAIEnem* AIEnem                     = new CAIEnem(gg::TANK,30,Position,true);
    Manager->addComponentToEntity(AIEnem, gg::AIENEM, Enemy);

    CVida* Vida                         = new CVida(health);
    Manager->addComponentToEntity(Vida,   gg::VIDA, Enemy);

    return Enemy;
}

uint16_t Factory::createCollisionableStaticModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const gg::Vector3f &Position) {
    uint16_t CollisionableStaticObject = Manager->createEntity();
    Material yelo(Texture);

    CTransform* Transform = new CTransform(gg::Vector3f(0,0,0),gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, CollisionableStaticObject);

    CRenderable_3D* Renderable_3D = new CRenderable_3D(Path, yelo);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, CollisionableStaticObject);

    CRigidBody* RigidBody = new CRigidBody(false, true,BulletPath, Position.X, Position.Y, Position.Z, -1,-1,-1, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, CollisionableStaticObject);

    return CollisionableStaticObject;
}

uint16_t Factory::createCollisionableDynamicModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const gg::Vector3f &Position) {
    uint16_t CollisionableDynamicObject = Manager->createEntity();
    Material yelo(Texture);

    CTransform* Transform = new CTransform(gg::Vector3f(0,0,0),gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, CollisionableDynamicObject);

    CRenderable_3D* Renderable_3D = new CRenderable_3D(Path, yelo);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, CollisionableDynamicObject);

    CRigidBody* RigidBody = new CRigidBody(true,true,BulletPath, Position.X, Position.Y, Position.Z, -1,-1,-1, 500, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, CollisionableDynamicObject);

    return CollisionableDynamicObject;
}

uint16_t Factory::createStaticModel(const std::string &Path, const std::string &Texture, const gg::Vector3f &Position, const gg::Vector3f &Rotation) {
    uint16_t CollisionableStaticObject = Manager->createEntity();
    Material yelo(Texture);

    CTransform* Transform = new CTransform(Position, Rotation);
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, CollisionableStaticObject);

    CRenderable_3D* Renderable_3D = new CRenderable_3D(Path, yelo);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, CollisionableStaticObject);

    return CollisionableStaticObject;
}

uint16_t Factory::createPathFindingActor(const gg::Vector3f &Position) {
    uint16_t Actor1 = Manager->createEntity();
    Material Blue("assets/Textures/Blue.png");

    CTransform* Transform = new CTransform(Position, gg::Vector3f(0,0,0));   // 300, 0, 700
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Actor1);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/Actor.obj", Blue);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Actor1);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet", Position.X, Position.Y, Position.Z, -1,-1,-1, 50, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Actor1);

    CNavmeshAgent* NavmeshAgent = new CNavmeshAgent();
    Manager->addComponentToEntity(NavmeshAgent, gg::NAVMESHAGENT, Actor1);

    return Actor1;
}

uint16_t Factory::createSenyuelo( const gg::Vector3f &Position, const gg::Vector3f &Impulse) {
    uint16_t holyBomb = Manager->createEntity();
    Material moradoDeLos80("assets/Textures/Blue.png");

    CTransform* Transform = new CTransform(Position, gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, holyBomb);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/bullet.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, holyBomb);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/bullet.bullet",  Position.X,Position.Y,Position.Z, 1,1,1, 5, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, holyBomb);

    CGranade* Granade = new CGranade2();
    Manager->addComponentToEntity(Granade, gg::GRANADE, holyBomb);

    RigidBody->applyCentralForce(Impulse);

    return holyBomb;
}
uint16_t Factory::createMatriuska( const gg::Vector3f &Position, const gg::Vector3f &Impulse) {
    uint16_t holyBomb = Manager->createEntity();
    Material moradoDeLos80("assets/Textures/Blue.png");

    CTransform* Transform = new CTransform(Position, gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, holyBomb);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/bullet.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, holyBomb);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/bullet.bullet",  Position.X,Position.Y,Position.Z, 1,1,1, 5, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, holyBomb);

    CGranade* Granade = new CGranade1();
    Manager->addComponentToEntity(Granade, gg::GRANADE, holyBomb);

    RigidBody->applyCentralForce(Impulse);

    return holyBomb;
}
uint16_t Factory::createHolyBomb( const gg::Vector3f &Position, const gg::Vector3f &Impulse) {
    uint16_t holyBomb = Manager->createEntity();
    Material moradoDeLos80("assets/Textures/Blue.png");

    CTransform* Transform = new CTransform(Position, gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, holyBomb);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/bullet.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, holyBomb);

    CRigidBody* RigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/bullet.bullet",  Position.X,Position.Y,Position.Z, 1,1,1, 5, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, holyBomb);

    CGranade* Granade = new CGranade0();
    Manager->addComponentToEntity(Granade, gg::GRANADE, holyBomb);

    RigidBody->applyCentralForce(Impulse);

    return holyBomb;
}

uint16_t Factory::createCollectableWeapon(const gg::Vector3f &_position, int _weaponType){
    uint16_t weapon = Manager->createEntity();
    Material w_mat("assets/Textures/ice.bmp");

    CTransform *transform = new CTransform(_position, gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(transform, gg::TRANSFORM, weapon);

    CRenderable_3D *renderable = new CRenderable_3D("assets/Models/weapon.obj", w_mat);
    Manager->addComponentToEntity(renderable, gg::RENDERABLE_3D, weapon);

    CRigidBody *rigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/weapon.bullet",  _position.X,_position.Y,_position.Z, -1,-1,-1, 25, 0,0,0);
    Manager->addComponentToEntity(rigidBody, gg::RIGID_BODY, weapon);

    TData mes;
    mes.add(kDat_EntId,weapon);
    mes.add(kDat_WeaponType,_weaponType);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_Gunfire,1,weapon,_position, 3, 0, true, mes);

    return weapon;
}

uint16_t Factory::createPickableItem(const gg::Vector3f &_position){
    uint16_t item = Manager->createEntity();
    Material w_mat("assets/Textures/pese.jpg");

    CTransform *transform = new CTransform(_position, gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(transform, gg::TRANSFORM, item);

    CRenderable_3D *renderable = new CRenderable_3D("assets/Models/weapon.obj", w_mat);
    Manager->addComponentToEntity(renderable, gg::RENDERABLE_3D, item);

    CRigidBody *rigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/weapon.bullet",  _position.X,_position.Y,_position.Z, -1,-1,-1, 25, 0,0,0);
    Manager->addComponentToEntity(rigidBody, gg::RIGID_BODY, item);

    TData mes;
    mes.add(kDat_PickableItemId,item);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_Pickable,1,item,_position, 2.5, 0, true, mes);

    return item;
}

uint16_t Factory::createTouchableObject(const gg::Vector3f &_position, const uint16_t &_id, const gg::Vector3f &vel, const float &_dur, uint16_t _item){
    uint16_t t_obj = Manager->createEntity();
    Material w_mat("assets/Textures/e61.png");

    CTransform *transform = new CTransform(_position, gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(transform, gg::TRANSFORM, t_obj);

    CRenderable_3D *renderable = new CRenderable_3D("assets/Models/Cube.obj", w_mat);
    // CRenderable_3D *renderable = new CRenderable_3D("assets/Models/cuboGrande.obj", w_mat);
    Manager->addComponentToEntity(renderable, gg::RENDERABLE_3D, t_obj);

    // CRigidBody *rigidBody = new CRigidBody(false, true,"assets/BoundingBoxes/Cube.bullet",  _position.X,_position.Y,_position.Z, -1,-1,-1, 25, 0,0,0);
    // Manager->addComponentToEntity(rigidBody, gg::RIGID_BODY, t_obj);

    TData mes;
    mes.add(kDat_EntId,_id);
    mes.add(kDat_Action,Action_MoverObjeto);
    mes.add(kDat_Done,false);
    if(_item){
        mes.add(kDat_PickableItemId,_item);
    }

    Blackboard b;
    BRbData *data = new BRbData(gg::RBActionStruct(vel.X,vel.Y,vel.Z));
    BFloat *data_time = new BFloat(_dur);
    b.GLOBAL_setData("DATA_"+std::to_string(_id)            ,data);
    b.GLOBAL_setData("DATA_"+std::to_string(_id)+"_TIME"    ,data_time);

    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_Touchable,1,t_obj,_position, 5, 0, true, mes);

    return t_obj;
}

uint16_t Factory::createDebugBullet(const gg::Vector3f &_pos){
    uint16_t debug = Manager->createEntity();
    Material moradoDeLos80("assets/Textures/Blue.png");

    CTransform* Transform               = new CTransform(_pos, gg::Vector3f(0, 0, 0));
    Manager->addComponentToEntity(Transform,        gg::TRANSFORM, debug);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/Models/bullet.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D,    gg::RENDERABLE_3D, debug);

    return debug;
}
