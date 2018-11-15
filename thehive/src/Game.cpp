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

#include "EventSystem/CTriggerSystem.hpp"

#include "Bullet/ggDynWorld.hpp"


#define MOVEMENT_SPEED 1.f

//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
void printHexVal(uint16_t val) {
   std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
   for(uint16_t l=0; l < lines; ++l) {
      std::cout << reinterpret_cast<uint16_t*>(p) << " ";
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
         std::cout << " ";
      }
      std::cout << "\n";
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


    /*
    CAgent* pAgent=NULL;
    CAgent* pAgent1=NULL;
    CAgent* pAgent2=NULL;
    CAgent* pAgent3=NULL;
    CAgent* pAgent4=NULL;

    pAgent=new CAgent(kTrig_Gunfire,gg::Vector3f(4,5,0));
    CAgent::hola.push_back(pAgent);
    std::cout << "Id agente 1:"<<pAgent->nCAgentID << std::endl;
    pAgent1=new CAgent(kTrig_EnemyNear,gg::Vector3f(3,2,0));
    CAgent::hola.push_back(pAgent1);
    std::cout << "Id agente 1:"<<pAgent1->nCAgentID << std::endl;

    pAgent2=new CAgent(kTrig_EnemyNear,gg::Vector3f(77,77,0));
    CAgent::hola.push_back(pAgent2);
    std::cout << "Id agente 1:"<<pAgent2->nCAgentID << std::endl;

    pAgent3=new CAgent(kTrig_Gunfire,gg::Vector3f());
    CAgent::hola.push_back(pAgent3);
    std::cout << "Id agente 1:"<<pAgent3->nCAgentID << std::endl;

    pAgent4=new CAgent(kTrig_EnemyNear|kTrig_Gunfire,gg::Vector3f(77,77,0));
    CAgent::hola.push_back(pAgent4);
    std::cout << "Id agente 1:"<<pAgent4->nCAgentID << std::endl;

    CAgent::hola.size();
    TriggerRecordStruct(kTrig_Explosion,6, gg::Vector3f(),4,2,false);
    CTriggerSystem* sistemita = Singleton<CTriggerSystem>::Instance();
    unsigned long id_puesto=sistemita->RegisterTriger(kTrig_Gunfire,3,0,gg::Vector3f(), 10, 2,false);
    id_puesto=sistemita->RegisterTriger(kTrig_EnemyNear,1,0,gg::Vector3f(), 150, 2,false);
    sistemita->Update();
    sistemita->RemoveTrigger(id_puesto);

                        //(EnumTriggerType _eTriggerType,unsigned long _idSource,const Vector _vPos,float _fRadius,
                          //                  unsigned long _fDuration,bool _bDynamicSourcePos);
    irr::core::list<CAgent*>::Iterator it =CAgent::hola.begin();

    while(it!=CAgent::hola.end()){
      std::cout << "Entre" << std::endl;

      it++;
    }
    delete pAgent;
    delete pAgent1;
    delete pAgent2;
    delete pAgent3;
    delete pAgent4;
    */

    Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));
    // Camera camera = engine->createCamera(gg::Vector3f(50, 0, -100), gg::Vector3f(0, 0, 50));
    ////camera.setPosition(gg::Vector3f(-50, 0, 100));
    ////camera.setTarget(gg::Vector3f(0, 0, 50));

    //uint8_t* p;
    //add inf triggers
    //EventSystem->RegisterTriger(kTrig_Explosion,1,0,gg::Vector3f(0,0,0), 20, 0,false);
    EventSystem->RegisterTriger(kTrig_Gunfire,  1,2,gg::Vector3f(100,5,50), 5, 0,false);
    {
        uint16_t hero = Manager->createEntity();
        Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
        Material pipaDeLos90("assets/Textures/arma.jpeg");
        InitCTransform CTransformInitData(0, 4, 0, 0, 0, 0);
        InitCRenderable_3D CRenderable_3DInitData("assets/Models/Cube.obj", moradoDeLos80);
        InitCRigidBody CRigidBodyHero(true,"assets/BoundingBoxes/Cube.bullet",  50,20,0, -1,-1,-1, 50, 0,0,0);
        Manager->addComponentToEntity(gg::TRANSFORM, hero, &CTransformInitData);
        Manager->addComponentToEntity(gg::CAMERA, hero);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, hero, &CRenderable_3DInitData);
        Manager->addComponentToEntity(gg::RIGID_BODY, hero, &CRigidBodyHero);
        Manager->addComponentToEntity(gg::KEYBOARD, hero);

        // InitCGun CGunHero(10,1,50);
        // Manager->addComponentToEntity(gg::GUN, hero, &CGunHero);

        // InitCAgent flagsheroe(kTrig_Explosion);
        // Manager->addComponentToEntity(gg::CAGENT, hero, &flagsheroe);
        //InitCAgent agentArma1(kTrig_Gunfire|kTrig_Explosion);
        //Manager->addComponentToEntity(gg::CAGENT, hero, &agentArma1);

        // ---------------------------------------

        // Cubo pequeño
        uint16_t cube1 = Manager->createEntity();
        InitCTransform CTransformCube1(50,0,0,0,0,0);
        InitCRenderable_3D CRenderableCube1("assets/Models/Cube.obj", moradoDeLos80);
        InitCRigidBody CRigidBodyCube1(true,"assets/BoundingBoxes/Cube.bullet",  10,20,0, -1,-1,-1, 1, 0,0,0);
        Manager->addComponentToEntity(gg::TRANSFORM, cube1, &CTransformCube1);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, cube1, &CRenderableCube1);
        Manager->addComponentToEntity(gg::RIGID_BODY, cube1, &CRigidBodyCube1);



        // Manager->removeEntity(cube1);

        // Cubo grande
        uint16_t cube2 = Manager->createEntity();
        InitCTransform CTransformCube2(0,0,0,0,0,0);
        InitCRenderable_3D CRenderableCube2("assets/Models/cuboGrande.obj", moradoDeLos80);
        //InitCRigidBody CRigidBodyHero(true,"assets/BoundingBoxes/Cube.bullet",  50,20,0, -1,-1,-1, 50, 0,0,0);
        InitCRigidBody CRigidBodyCube2(true,"assets/BoundingBoxes/cuboGrande.bullet", 0,100,50, -1,-1,-1, 50, 0,0,0);
        Manager->addComponentToEntity(gg::TRANSFORM, cube2, &CTransformCube2);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, cube2, &CRenderableCube2);
        Manager->addComponentToEntity(gg::RIGID_BODY, cube2, &CRigidBodyCube2);
        InitCAgent objetoExplosion(kTrig_Explosion);
        Manager->addComponentToEntity(gg::CAGENT, cube2, &objetoExplosion);
        // Manager->removeEntity(cube1);

        // Se usa para el RAYCASTING para el debug visual
        // QUE ESTE SIEMPRE EN LA POSICION 4 DE CREACION
        uint16_t cube3 = Manager->createEntity();
        InitCTransform CTransformCube3(0,20,0,0,0,0);
        InitCRenderable_3D CRenderableCube3("assets/Models/Cube.obj", moradoDeLos80);
        Manager->addComponentToEntity(gg::TRANSFORM, cube3, &CTransformCube3);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, cube3, &CRenderableCube3);


        // Entidad tipo arma
        // En cuanto pasa el heroe por encima, se le anyade una componente arma, si no la tiene
        uint16_t Arma1 = Manager->createEntity();
        InitCTransform CTransformArma1(100,5,50,0,0,0);
        InitCRenderable_3D CRenderableArma1("assets/Models/Cube.obj", pipaDeLos90);
        Manager->addComponentToEntity(gg::TRANSFORM, Arma1, &CTransformArma1);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, Arma1, &CRenderableArma1);


    }

    {
        uint16_t TrainingArea = Manager->createEntity();
        Material AgujeroNegro("assets/Textures/ice.bmp");
        InitCTransform CTransformTraining(0,0,0,0,0,0);
        InitCRenderable_3D InitTrainingArea("assets/Models/TrainingArea2.obj", AgujeroNegro);
        // InitCRigidBody CRigidBodyTraining(true,"assets/BoundingBoxes/trainingArea.bullet",  0,0,0, -1,-1,-1, 0, 0,0,0);
        InitCRigidBody CRigidBodyTraining(false,"",  0,0,0, 500,2,500, 0, 0,0,0, 0.7);
        Manager->addComponentToEntity(gg::TRANSFORM, TrainingArea, &CTransformTraining);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, TrainingArea, &InitTrainingArea);
        Manager->addComponentToEntity(gg::RIGID_BODY, TrainingArea, &CRigidBodyTraining);
    }

    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //std::cout << "--------------\n";

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    //Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");

    //tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

    // Se debe poner la gravedad, aunque al iniciar el mundo tambien se haga
    // Las llamadas que cargan los .bullet se ve que la trastocan
    world->setGravity(0,-200,0);
    std::cout << "BEGIN GAME LOOP" << '\n';
    while(Engine->isWindowOpen()) {
        world->stepSimulation(1.f / 60.f, 10.f);
        Manager->sendMessageToAllEntities(gg::M_UPDATE);
        EventSystem->Update();
        Engine->Dro();
        Engine->DisplayFPS();
    }
}

void Game::CLIN(){
    Manager->clin();
    Engine->clean();
    world->clean();
    EventSystem->clin();
}
