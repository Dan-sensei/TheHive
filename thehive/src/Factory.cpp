#include "Factory.hpp"
#include <ComponentArch/Components/ComponentHeaders.hpp>

Factory::Factory() {
    Manager = Singleton<ObjectManager>::Instance();
    Engine = Singleton<GameEngine>::Instance();

}

uint16_t Factory::createHero(const gg::Vector3f &Position,bool _b) {
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    uint16_t hero = Manager->createEntity();
    CTransform* Transform               = new CTransform(gg::Vector3f(0, 0, 10), gg::Vector3f(0, 0, 0));
    Manager->addComponentToEntity(Transform,        gg::TRANSFORM, hero);


    CCamera* Camera                     = new CCamera(_b);
    Camera->setTarget(Transform);
    Manager->addComponentToEntity(Camera,           gg::CAMERA, hero);

    CRigidBody* RigidBody               = new CRigidBody(true, false,"", Position.X, Position.Y, Position.Z, 0,0,0, 50, 0,0,0);
    Manager->addComponentToEntity(RigidBody,        gg::RIGID_BODY, hero);

    CPlayerController* PlayerController = new CPlayerController();
    Manager->addComponentToEntity(PlayerController, gg::PLAYERCONTROLLER, hero);

    Manager->setHeroID(hero);

    return hero;
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

void Factory::LoadNavmeshTestMap1() {
   //factory->createStaticModel("assets/NavMeshes/L4D2Nav.obj", "assets/NavMeshes/L4D2Nav.png", gg::Vector3f(0, 0, 0));

   uint16_t Navmesh = Manager->createEntity();
   Material yelo("assets/NavMeshes/L4D2Nav.png");

   CTransform* Transform = new CTransform(gg::Vector3f(0,0,0), gg::Vector3f(0,0,0));
   Manager->addComponentToEntity(Transform, gg::TRANSFORM, Navmesh);

   CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/NavMeshes/L4D2Nav.obj", yelo);
   Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Navmesh);

   uint16_t NavmeshGround = Manager->createEntity();
   CRigidBody* RigidBody = new CRigidBody(false, false,"", 0, -10, 0, 680,10,800, 0, 0,0,0, 0.2);
   Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, NavmeshGround);


   uint16_t Wall_1 = Manager->createEntity();
   CRigidBody* RigidBody_1 = new CRigidBody(false, false,"", -280, 0, -100, 160, 100,265, 0, 0,0,0, 0.2);
   Manager->addComponentToEntity(RigidBody_1, gg::RIGID_BODY, Wall_1);

   uint16_t Wall_2 = Manager->createEntity();
   CRigidBody* RigidBody_2 = new CRigidBody(false, false,"", -80, 0, 410, 215, 100,320, 0, 0,0,0, 0.2);
   Manager->addComponentToEntity(RigidBody_2, gg::RIGID_BODY, Wall_2);

   uint16_t Wall_3 = Manager->createEntity();
   CRigidBody* RigidBody_3 = new CRigidBody(false, false,"", 110, 0, 70, 80, 100, 32, 0, 0,0,0, 0.2);
   Manager->addComponentToEntity(RigidBody_3, gg::RIGID_BODY, Wall_3);

   uint16_t Wall_4 = Manager->createEntity();
   CRigidBody* RigidBody_4 = new CRigidBody(false, false,"", -25, 0, 17, 100, 125, 28, 0, 0,0,0, 0.2);
   Manager->addComponentToEntity(RigidBody_4, gg::RIGID_BODY, Wall_4);

   //60 -450
   //132 - 550

}
