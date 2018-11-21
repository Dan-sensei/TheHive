#include <iostream>
#include <cstdint>
#include <iomanip>
#include <map>
#include <string>

#include "Arena.hpp"
#include "ComponentArch/ObjectManager.hpp"
#include "ComponentArch/InitStructs.hpp"
#include "GameEngine/Camera.hpp"
#include "Game.hpp"
#include "Util.hpp"
#include "Singleton.hpp"

#include "ComponentArch/Components/CAgent.hpp"
#include <EventSystem/EnumTriggerType.hpp>
#include "GameAI/Pathfinding.hpp"

#include "EventSystem/CTriggerSystem.hpp"

#include "Bullet/ggDynWorld.hpp"

#include "BT/BehaviorTree.hpp"
#include "BT/RandomSelector.hpp"
#include "BT/RandomSequence.hpp"
#include "BT/Action.hpp"


#define MOVEMENT_SPEED 1.f


//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
void printHexVal(uint16_t val) {
   // std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
   for(uint16_t l=0; l < lines; ++l) {
      // std::cout << reinterpret_cast<uint16_t*>(p) << " ";
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
         // std::cout << " ";
      }
      // std::cout << "\n";
   }
}
//============================================================================================

Game::Game(){
    Engine = Singleton<GameEngine>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();

    Engine->Starto();
    Engine->HideCursor(true);

    Manager = Singleton<ObjectManager>::Instance();
    Manager->initObjectManager();

    world = Singleton<ggDynWorld>::Instance();
    world->inito();
}

Game::~Game(){

}

void Game::RUN(){






        Action andar_r= Action(ANDAR_RAND);
        Action rango= Action(RANGO);
        Action giro= Action(GIRAR);
        Action move_to= Action(MOVER);
        Action com= Action(COMER);

        RandomSequence sec1= RandomSequence();
        sec1.addChild(&rango);
        sec1.addChild(&giro);

        RandomSequence  sec2= RandomSequence();
        sec2.addChild(&sec1);
        sec2.addChild(&move_to);
        sec2.addChild(&com);

        RandomSelector selec1=  RandomSelector();
        selec1.addChild(&andar_r);
        selec1.addChild(&sec2);

        BehaviorTree BT(&selec1);

        BT.tick();
        BT.tick();
std::cout << "bt generado" << '\n';



    Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));
    // Camera camera = engine->createCamera(gg::Vector3f(50, 0, -100), gg::Vector3f(0, 0, 50));
    ////camera.setPosition(gg::Vector3f(-50, 0, 100));
    ////camera.setTarget(gg::Vector3f(0, 0, 50));

    //uint8_t* p;
    //add inf triggers
    //EventSystem->RegisterTriger(kTrig_Gunfire,  1,0,gg::Vector3f(100,5,50), 5, 0,false,NULL);
    // EventSystem->RegisterTriger(kTrig_Explosion,1,0,gg::Vector3f(0,0,0), 20, 0,false);
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

{

    InitCRigidBody CRigidBodyEnemy(true,"assets/BoundingBoxes/Cube.bullet",  100,80,0, -1,-1,-1, 50, 0,0,0);
    uint16_t Enemy = Manager->createEntity();
    InitCTransform CTransformInitDataEnemy(0, 0, 10, 0, 0, 0);
    InitCRenderable_3D CRenderable_3DInitDataEnemy("assets/Models/Cube.obj", moradoDeLos80);
    InitCAgent agentEnemy(kTrig_EnemyNear);
    Manager->addComponentToEntity(gg::TRANSFORM, Enemy, &CTransformInitDataEnemy);
    Manager->addComponentToEntity(gg::RENDERABLE_3D, Enemy, &CRenderable_3DInitDataEnemy);
    Manager->addComponentToEntity(gg::RIGID_BODY, Enemy, &CRigidBodyEnemy);
    Manager->addComponentToEntity(gg::AGENT, Enemy, &agentEnemy);
    InitCAIEnem cIAEnem(gg::SOLDIER,30,gg::Vector3f(),false);
    Manager->addComponentToEntity(gg::AIENEM, Enemy, &cIAEnem);
}

    {
        InitCRigidBody CRigidBodyHero(true,"assets/BoundingBoxes/Cube.bullet",  100,80,0, -1,-1,-1, 50, 0,0,0);
        uint16_t hero = Manager->createEntity();
        InitCTransform CTransformInitData(0, 0, 10, 0, 0, 0);
        InitCRenderable_3D CRenderable_3DInitData("assets/Models/Cube.obj", moradoDeLos80);
        Manager->addComponentToEntity(gg::TRANSFORM, hero, &CTransformInitData);
        Manager->addComponentToEntity(gg::CAMERA, hero);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, hero, &CRenderable_3DInitData);
        Manager->addComponentToEntity(gg::RIGID_BODY, hero, &CRigidBodyHero);
        Manager->addComponentToEntity(gg::PLAYERCONTROLLER, hero);

        InitCAgent agentHero(kTrig_Gunfire|kTrig_Explosion);
        Manager->addComponentToEntity(gg::AGENT, hero, &agentHero);

        // ---------------------------------------

        // Cubo pequeño
        // uint16_t cube1 = Manager->createEntity();
        // InitCTransform CTransformCube1(50,0,0,0,0,0);
        // InitCRenderable_3D CRenderableCube1("assets/Models/Cube.obj", moradoDeLos80);
        // InitCRigidBody CRigidBodyCube1(true,"assets/BoundingBoxes/Cube.bullet",  50,20,10, -1,-1,-1, 10, 0,0,0);
        // Manager->addComponentToEntity(gg::TRANSFORM, cube1, &CTransformCube1);
        // Manager->addComponentToEntity(gg::RENDERABLE_3D, cube1, &CRenderableCube1);
        // Manager->addComponentToEntity(gg::RIGID_BODY, cube1, &CRigidBodyCube1);
        //
        // InitCAgent objetoExplosion(kTrig_Explosion);
        // Manager->addComponentToEntity(gg::CAGENT, cube1, &objetoExplosion);

        // Cubo grande
        // uint16_t cube2 = Manager->createEntity();
        // InitCTransform CTransformCube2(0,0,0,0,0,0);
        // InitCRenderable_3D CRenderableCube2("assets/Models/cuboGrande.obj", moradoDeLos80);
        // InitCRigidBody CRigidBodyCube2(true,"assets/BoundingBoxes/cuboGrande.bullet", 0,100,50, -1,-1,-1, 50, 0,0,0);
        // // InitCRigidBody CRigidBodyCube2(false,"",  0,100,50, 50,50,50, 50, 0,0,0);
        // Manager->addComponentToEntity(gg::TRANSFORM, cube2, &CTransformCube2);
        // Manager->addComponentToEntity(gg::RENDERABLE_3D, cube2, &CRenderableCube2);
        // Manager->addComponentToEntity(gg::RIGID_BODY, cube2, &CRigidBodyCube2);
        //
        // // Se usa para el RAYCASTING para el debug visual
        // // QUE ESTE SIEMPRE EN LA POSICION 4 DE CREACION
        // uint16_t cube3 = Manager->createEntity();
        // InitCTransform CTransformCube3(0,20,0,0,0,0);
        // InitCRenderable_3D CRenderableCube3("assets/Models/Cube.obj", moradoDeLos80);
        // Manager->addComponentToEntity(gg::TRANSFORM, cube3, &CTransformCube3);
        // Manager->addComponentToEntity(gg::RENDERABLE_3D, cube3, &CRenderableCube3);
        //

        //    Material pipaDeLos90("assets/Textures/arma.jpeg");


        // // Entidad tipo arma
        // // En cuanto pasa el heroe por encima, se le anyade una componente arma, si no la tiene
        // uint16_t Arma1 = Manager->createEntity();
        // InitCTransform CTransformArma1(100,5,50,0,0,0);
        // InitCRenderable_3D CRenderableArma1("assets/Models/Cube.obj", pipaDeLos90);
        // Manager->addComponentToEntity(gg::TRANSFORM, Arma1, &CTransformArma1);
        // Manager->addComponentToEntity(gg::RENDERABLE_3D, Arma1, &CRenderableArma1);


    }

    {
        uint16_t TrainingArea = Manager->createEntity();
        Material yelo("assets/Textures/ice.bmp");
        InitCTransform CTransformTraining(0,0,0,0,0,0);
        InitCRenderable_3D InitTrainingArea("assets/Models/prueba.obj", yelo);
        InitCRigidBody CRigidBodyTraining(true,"assets/BoundingBoxes/prueba.bullet",  100,75,0, -1,-1,-1, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(gg::TRANSFORM, TrainingArea, &CTransformTraining);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, TrainingArea, &InitTrainingArea);
        Manager->addComponentToEntity(gg::RIGID_BODY, TrainingArea, &CRigidBodyTraining);

        uint16_t Actor1 = Manager->createEntity();
        Material Blue("assets/Textures/Blue.png");
        InitCTransform Actor1Transform(-100,0,0,0,0,0);
        InitCRenderable_3D CRenderableCube1("assets/Models/Actor.obj", Blue);
        Manager->addComponentToEntity(gg::TRANSFORM, Actor1, &Actor1Transform);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, Actor1, &CRenderableCube1);
        //Manager->addComponentToEntity(gg::PATHFINDING, Actor1);
    }

     {
         Material Wireframe("assets/NavMeshes/Navmesh.png");
         uint16_t Navmesh = Manager->createEntity();
         InitCTransform init(0,0,0,0,0,0);
         InitCRenderable_3D InitTrainingArea("assets/NavMeshes/Test.obj", Wireframe);
         Manager->addComponentToEntity(gg::TRANSFORM, Navmesh, &init);
         Manager->addComponentToEntity(gg::RENDERABLE_3D, Navmesh, &InitTrainingArea);
     }

    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //// std::cout << "--------------\n";

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    //Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");
    //tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

    // std::cout << "BEGIN GAME LOOP" << '\n';
    world->setDebug(false);
    while(Engine->isWindowOpen()) {

        world->stepSimulation(1.f / 11.f, 10.f);

        EventSystem->Update();

        Engine->BeginDro();
        Manager->sendMessageToAllEntities(gg::M_UPDATE);
        Engine->Dro();
        Engine->DisplayFPS();
        Singleton<ggDynWorld>::Instance()->debugDrawWorld();
        Singleton<Pathfinding>::Instance()->DroNodes();

        Engine->EndDro();
    }
}

void Game::CLIN(){
    Manager->clin();
    Engine->clean();
    world->clean();
    EventSystem->clin();
}
