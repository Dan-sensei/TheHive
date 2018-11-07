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

#include "EventSystem/Agent.hpp"
#include "EventSystem/GameState.hpp"






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
    engine = Singleton<GameEngine>::Instance();
    engine->Starto();
    engine->HideCursor(true);
}

Game::~Game(){

}

void Game::RUN(){


    //
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
    //
    engine->createCamera(gg::Vector3f(0, 0, 0), gg::Vector3f(0, 0, 50));
    // Camera camera = engine->createCamera(gg::Vector3f(50, 0, -100), gg::Vector3f(0, 0, 50));
    ////camera.setPosition(gg::Vector3f(-50, 0, 100));
    ////camera.setTarget(gg::Vector3f(0, 0, 50));

    //uint8_t* p;

    ObjectManager* Manager = Singleton<ObjectManager>::Instance();
    Manager->initObjectManager();

    uint16_t hero = Manager->createEntity();
    std::cout << "Hero " << hero << std::endl;


    {
        Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
        InitCTransform CTransformInitData(0, 0, 10, 0, 0, 0, 0, 0, 0);
        InitCRenderable_3D CRenderable_3DInitData("assets/Models/obradearte/algo.obj", moradoDeLos80);
        Manager->addComponentToEntity(gg::TRANSFORM, hero, &CTransformInitData);
        Manager->addComponentToEntity(gg::KEYBOARD, hero);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, hero, &CRenderable_3DInitData);
        Manager->addComponentToEntity(gg::CAMERA, hero);

        uint16_t cube1 = Manager->createEntity();
        InitCTransform CTransformCube1(50,0,0,0,0,0,0,0,0);
        InitCRenderable_3D CRenderableCube1("assets/Models/Cube.obj", moradoDeLos80);
        Manager->addComponentToEntity(gg::TRANSFORM, cube1, &CTransformCube1);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, cube1, &CRenderableCube1);
    }

    {
        Material AgujeroNegro("assets/Textures/ice.bmp");
        InitCRenderable_3D InitTrainingArea("assets/Models/TrainingArea.obj", AgujeroNegro);
        uint16_t TrainingArea = Manager->createEntity();
        Manager->addComponentToEntity(gg::RENDERABLE_3D, TrainingArea, &InitTrainingArea);
    }

    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //std::cout << "--------------\n";

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    //Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");

    //tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

    std::cout << "BEGIN GAME LOOP" << '\n';
    Manager->LastPreprocessingInitData();
    while(engine->isWindowOpen()) {
        Manager->sendMessageToAllEntities(gg::M_UPDATE);
        engine->Dro();
        engine->DisplayFPS();
    }
}

void Game::CLIN(){
    engine->clean();
}
