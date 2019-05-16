#include "MenuState.hpp"

//#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"

#include <Omicron/2D/Motor2D.hpp>
#include <States/StateMachine.hpp>
#include <BinaryParser.hpp>

MenuState::MenuState()
:Engine(Singleton<Omicron>::Instance()), Menu(200/1280.f, 72/720.f, 1091/1280.f, 286/720.f, "assets/HUD/THEHIVE.png")
// :Engine(Singleton<Omicron>::Instance()), Menu(561/1280.f, 467/720.f, 723/1280.f, 569/720.f, "assets/HUD/PLAY.png")
{
    cont = Singleton<GUIController>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    Engine->HideCursor(false);
    Manager = Singleton<ObjectManager>::Instance();
    world = Singleton<ggDynWorld>::Instance();
}

MenuState::~MenuState(){
    //CLIN();
}

void MenuState::Init(){
    Engine->resizeFrameBuffers(Engine->getWindowsWidth(), Engine->getWindowsHeight());

    Engine->HideCursor(false);

    cont->musicaMenuPlay();

    Engine->createZones(8);

    //Los eventos son propios de cada zona!
    BinaryParser::LoadLevelData("assets/BinaryFiles/MENU/MENU_MODELS.data", 1);

    glm::vec3 Position = glm::vec3();

    BinaryParser::MENU_getCameraPositionRotation("assets/BinaryFiles/MENU/MenuCam.cam", Position, OriginalTarget);

    auto sF = Singleton<Factory>::Instance();
    Engine->crearCamara(90,0.15f,100.f, Position, glm::quat(), 16.f/9.f);
    Camera = Engine->getMainCameraEntity();
    gg::Color c;
    StandardNode* luz = Engine->crearLuz(c,glm::vec3(5, 6, 0),glm::vec3(), Singleton<AssetManager>::Instance()->getShader("Default"));
    Engine->setPosition(luz, glm::vec3(125.964005, 10, -46.611977));
    //MainCamera = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, h));

    ParticleSystem_Data PS_D;
    PS_D.Texture = Singleton<AssetManager>::Instance()->getTexture("assets/Textures/Particles/Smoke.png");
    PS_D.SpawnTime = 0.25;
    PS_D.ParticleLifeTime = 5;
    PS_D.MaxParticles = 1/PS_D.SpawnTime * PS_D.ParticleLifeTime;

    BinaryParser::LoadParticleSystem(PS_D, "assets/BinaryFiles/MENU/ParticleMenu.ps");
    Engine->CreateParticleSystem(Singleton<Omicron>::Instance()->FORWARD_LAYER, PS_D);

    RandomTarget = glm::vec3(
        gg::genFloatRandom(OriginalTarget.x-1, OriginalTarget.x+1),
        gg::genFloatRandom(OriginalTarget.y-1, OriginalTarget.y+1),
        gg::genFloatRandom(OriginalTarget.z-1, OriginalTarget.z+1)
    );
    CurrentTarget = OriginalTarget;
    Singleton<Motor2D>::Instance()->InitMenu();

}

void MenuState::Resume() {
    Singleton<Motor2D>::Instance()->InitMenu();
    Engine->HideCursor(false);

    // cont->musicaMenuPause(false);
}

void MenuState::Update(){

    float DeltaTime = MasterClock.Restart().Seconds();

    if(glm::length(RandomTarget - CurrentTarget) < 0.5){
        RandomTarget = glm::vec3(
            gg::genFloatRandom(OriginalTarget.x-2, OriginalTarget.x+2),
            gg::genFloatRandom(OriginalTarget.y-2, OriginalTarget.y+2),
            gg::genFloatRandom(OriginalTarget.z-2, OriginalTarget.z+2)
        );
    }
    else{
        glm::vec3 Dir = glm::normalize(RandomTarget - CurrentTarget);

        CurrentTarget += Dir*0.5f*DeltaTime;
    }

    Engine->PollEvents();

    Engine->BeginDraw();
    // cont->update();
    SS->update();

    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    //Engine2D->draw();
    //Engine2D->checkbuton();

    Camera->setTarget(CurrentTarget);
    Engine->draw();
    glClear(GL_DEPTH_BUFFER_BIT);

    cont->update();
    Singleton<Motor2D>::Instance()->draw();
    Singleton<Motor2D>::Instance()->aplyhover();

    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glUniform1f(3,-0.995);
    Menu.Draw();
    glEnable (GL_FALSE);

    Engine->EndDraw();
    Engine->resetClickVariable();
}

void MenuState::CLIN(){
    std::cout << "CLEAN" << '\n';
    Singleton<Motor2D>::Instance()->CLINMenu();
    cont->musicaMenuStop();
    Manager->clin();
    world->clear();
    Singleton<AssetManager>::Instance()->~AssetManager();

    Engine->resetSceneGraph();


    //EventSystem->clin();
}
//
// void MenuState::Pause(){
//   cont->musicaMenuPause(true);
// }
