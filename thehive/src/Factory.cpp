#include "Factory.hpp"

Factory::Factory() {
    Manager = Singleton<ObjectManager>::Instance();
    Engine = Singleton<GameEngine>::Instance();

    ComponentInitializer();

}

#include <ComponentArch/Components/ComponentInitializer>

void Factory::createHero(const gg::Vector3f &Position) {
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    uint16_t hero = Manager->createEntity();
    CTransform* Transform               = new CTransform(gg::Vector3f(0, 0, 10), gg::Vector3f(0, 0, 0));
    Manager->addComponentToEntity(Transform,        gg::TRANSFORM, hero);

    CCamera* Camera                     = new CCamera();
    Manager->addComponentToEntity(Camera,           gg::CAMERA, hero);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/Models/Cube.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D,    gg::RENDERABLE_3D, hero);

    CRigidBody* RigidBody               = new CRigidBody(true,"assets/BoundingBoxes/Cube.bullet", Position.X, Position.Y, Position.Z, -1,-1,-1, 50, 0,0,0);
    Manager->addComponentToEntity(RigidBody,        gg::RIGID_BODY, hero);

    CPlayerController* PlayerController = new CPlayerController();
    Manager->addComponentToEntity(PlayerController, gg::PLAYERCONTROLLER, hero);

    CAgent* Agent                       = new CAgent(kTrig_Gunfire|kTrig_Explosion);
    Manager->addComponentToEntity(Agent, gg::AGENT, hero);
}

void Factory::createEnemy(const gg::Vector3f &Position){
    uint16_t Enemy = Manager->createEntity();
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    CTransform* Transform               = new CTransform(Position, gg::Vector3f(0, 0, 0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Enemy);

    CRenderable_3D* Renderable_3D       = new CRenderable_3D("assets/Models/Cube.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Enemy);

    CRigidBody* RigidBody               = new CRigidBody(true,"assets/BoundingBoxes/Cube.bullet", Position.X, Position.Y, Position.Z, -1,-1,-1, 50, 0,0,0, 0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Enemy);

    CAgent* Agent                       = new CAgent(kTrig_EnemyNear|kTrig_Shoot);
    Manager->addComponentToEntity(Agent, gg::AGENT, Enemy);

    CAIEnem* AIEnem                     = new CAIEnem(gg::SOLDIER,30,gg::Vector3f(),false);
    Manager->addComponentToEntity(AIEnem, gg::AIENEM, Enemy);
}

void Factory::createCollisionableStaticModel(const std::string &Path, const std::string &BulletPath, const std::string &Texture, const gg::Vector3f &Position) {
    uint16_t CollisionableStaticObject = Manager->createEntity();
    Material yelo(Texture);

    CTransform* Transform = new CTransform(gg::Vector3f(0,0,0),gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, CollisionableStaticObject);

    CRenderable_3D* Renderable_3D = new CRenderable_3D(Path, yelo);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, CollisionableStaticObject);

    CRigidBody* RigidBody = new CRigidBody(true,BulletPath, Position.X, Position.Y, Position.Z, -1,-1,-1, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, CollisionableStaticObject);
}

void Factory::createStaticModel(const std::string &Path, const std::string &Texture, const gg::Vector3f &Position, const gg::Vector3f &Rotation) {
    uint16_t CollisionableStaticObject = Manager->createEntity();
    Material yelo(Texture);

    CTransform* Transform = new CTransform(Position, Rotation);
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, CollisionableStaticObject);

    CRenderable_3D* Renderable_3D = new CRenderable_3D(Path, yelo);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, CollisionableStaticObject);
}

void Factory::createPathFindingActor(const gg::Vector3f &Position) {
    uint16_t Actor1 = Manager->createEntity();
    Material Blue("assets/Textures/Blue.png");

    CTransform* Transform = new CTransform(Position, gg::Vector3f(0,0,0));   // 300, 0, 700
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Actor1);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/Actor.obj", Blue);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Actor1);

    CRigidBody* RigidBody = new CRigidBody(true,"assets/BoundingBoxes/Cube.bullet", Position.X, Position.Y, Position.Z, -1,-1,-1, 50, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, Actor1);

    CPathfinding* Pathfinding = new CPathfinding();
    Manager->addComponentToEntity(Pathfinding, gg::PATHFINDING, Actor1);
}

void Factory::createHolyBomb(float _damage, float _radius,float _tipo, const gg::Vector3f &Position, const gg::Vector3f &Impulse) {
    uint16_t holyBomb = Manager->createEntity();
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    CTransform* Transform = new CTransform(Position, gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, holyBomb);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/Cube.obj", moradoDeLos80);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, holyBomb);

    CRigidBody* RigidBody = new CRigidBody(false,"",  Position.X,Position.Y,Position.Z, 3,3,3, 1, 0,0,0);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, holyBomb);

    CGranade* Granade = new CGranade(_damage, _radius, _tipo);
    Manager->addComponentToEntity(Granade, gg::GRANADE, holyBomb);

    RigidBody->applyCentralForce(Impulse);
}

void Factory::createCollectableWeapon(const gg::Vector3f &_position, int _weaponType){
    uint16_t weapon = Manager->createEntity();
    Material w_mat("assets/Textures/ice.bmp");

    CTransform *transform = new CTransform(_position, gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(transform, gg::TRANSFORM, weapon);

    CRenderable_3D *renderable = new CRenderable_3D("assets/Models/Cube.obj", w_mat);
    Manager->addComponentToEntity(renderable, gg::RENDERABLE_3D, weapon);

    CRigidBody *rigidBody = new CRigidBody(false,"",  _position.X,_position.Y,_position.Z, 1.5,1.5,1.5, 1, 0,0,0);
    Manager->addComponentToEntity(rigidBody, gg::RIGID_BODY, weapon);

    TData mes;
    mes.add(kDat_EntId,weapon);
    mes.add(kDat_WeaponType,_weaponType);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_Gunfire,1,weapon,_position, 5, 0, true, mes);
}
