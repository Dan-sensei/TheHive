#include "GUIController.hpp"
//#include <iostream>
#include <Game.hpp>
#include <OptionState.hpp>
#include <Omicron/2D/Motor2D.hpp>
#include <PopState.hpp>
#include <MenuState.hpp>
#include <ComponentArch/ObjectManager.hpp>

//#include <SMaterial>
GUIController::GUIController()
:Engine(nullptr), _ObjectManager(nullptr), CurrentResolution(1), LIGHTNING(25)
{
  Init();
}
GUIController::~GUIController(){
  delete s_accion;
  delete s_musica_menu;
  delete s_musica_cred;
  delete s_musica_basica;
}
void GUIController::setposmax(int p){
    cursorpos=0;
    posmax=p;
}
void GUIController::Init(){

    SS = Singleton<SoundSystem>::Instance();
    _ObjectManager = Singleton<ObjectManager>::Instance();

    s_accion = new SonidoNormal();
    SS->createSound("event:/SFX/Menu/Aceptar",s_accion);

    s_musica_menu = new SonidoNormal();
    SS->createSound("event:/Musica/Menu/MusicaMenu",s_musica_menu);

    s_musica_cred = new SonidoNormal();
    SS->createSound("event:/Musica/Menu/MusicaCreditos",s_musica_cred);

    s_musica_basica = new SonidoNormal();
    SS->createSound("event:/Musica/Ciudad/MusicaBasica",s_musica_basica);

    reproduce = false;
    dif=1;

    dialogue = SS->getVolume("bus:/Voces") + 49;
    SS->setVolume(dialogue/40,"bus:/Voces");

    music = SS->getVolume("bus:/Musica") + 49;
    SS->setVolume(music/40,"bus:/Musica");

    effect = SS->getVolume("bus:/SFX") + 49;
    SS->setVolume(effect/40,"bus:/SFX");

    cursorpos=0;
    music_max=100;
    effect_max=100;
    dialogue_max=100;
    posmax=0;
    arriba_pulsado=false;
    bajo_pulsado=false;
    enter_pulsado=false;
    back_pulsado=false;
    esc_pulsado=false;
    Engine = Singleton<Omicron>::Instance();
    Engine2D = Singleton<Motor2D>::Instance();
    VectorAcciones[GOPLAY] =    &GUIController::gotoPlay;
    VectorAcciones[GOCREDITS] = &GUIController::gotoCredits;
    VectorAcciones[GOOPTIONS] = &GUIController::gotoOptions;
    VectorAcciones[CLOSE] =     &GUIController::Close;
    VectorAcciones[GOVIDEO] =   &GUIController::gotoVideo;
    VectorAcciones[GOMUSIC] =   &GUIController::gotoMusic;
    VectorAcciones[GOCONTROLLS] = &GUIController::gotoControlls;
    VectorAcciones[START] =     &GUIController::StartGame;
    VectorAcciones[GOMAIN] =    &GUIController::gotoMain;
    VectorAcciones[DIFF1] =     &GUIController::dif1;
    VectorAcciones[DIFF2] =     &GUIController::dif2;
    VectorAcciones[DIFF3] =     &GUIController::dif3;
    VectorAcciones[CONTINUE] =  &GUIController::Continue;
    VectorAcciones[RETURNMENU] = &GUIController::ReturnMain;
    VectorAcciones[GOPAUSE] =   &GUIController::gotoPause;
    VectorAcciones[MOREDIALOD] = &GUIController::moreDialog;
    VectorAcciones[LESSDIALOD] = &GUIController::lessDialog;
    VectorAcciones[MUTEDIALOD] = &GUIController::muteDialog;
    VectorAcciones[MOREMUSIC] = &GUIController::moreMusic;
    VectorAcciones[LESSMUSIC] = &GUIController::lessMusic;
    VectorAcciones[MUTEMUSIC] = &GUIController::muteMusic;
    VectorAcciones[MOREEFFECT] = &GUIController::moreEffect;
    VectorAcciones[LESSEFFECT] = &GUIController::lessEffect;
    VectorAcciones[MUTEEFFECT] = &GUIController::muteEffect;
    VectorAcciones[GOINITOPTIONS] = &GUIController::initOptions;

    VectorAcciones[INVERTCAMERA] = &GUIController::invertCamera;
    VectorAcciones[MORERESOLUTION] = &GUIController::moreResolution;
    VectorAcciones[LESSRESOLUTION] = &GUIController::lessResolution;
    VectorAcciones[MOREBRIGHTNESS] = &GUIController::moreBrightness;
    VectorAcciones[LESSBRIGHTNESS] = &GUIController::lessBrightness;

    RESOLUTIONS[0].WIDTH = 640;
    RESOLUTIONS[0].HEIGHT = 360;

    RESOLUTIONS[1].WIDTH = 848;
    RESOLUTIONS[1].HEIGHT = 480;

    RESOLUTIONS[2].WIDTH = 1280;
    RESOLUTIONS[2].HEIGHT = 720;

    RESOLUTIONS[3].WIDTH = 1366;
    RESOLUTIONS[3].HEIGHT = 768;

    RESOLUTIONS[4].WIDTH = 1920;
    RESOLUTIONS[4].HEIGHT = 1080;

    RESOLUTIONS[5].WIDTH = 2560;
    RESOLUTIONS[5].HEIGHT = 1440;
}

void GUIController::update(){

    int id =Engine2D->checkbuton();
     if(id!=-1){
         if(VectorAcciones[id] != nullptr)
             (this->*VectorAcciones[id])();
     }
}
//but0
void GUIController::gotoPlay(){
    sonido_accion(0);
    dif=1;
    Engine2D->InitMenu2();
}
//but1
void GUIController::gotoCredits(){
    s_musica_menu->pause(true);
    s_musica_cred->play();
    sonido_accion(0);
    Engine2D->InitMenu3();
}
//but2
void GUIController::gotoOptions(){
    sonido_accion(0);
    Singleton<StateMachine>::Instance()->AddState(new OptionState(),false);
    Engine2D->setVolDialogo(dialogue);
    Engine2D->setVolMusic(music);
    Engine2D->setVolEffect(effect);
}
//but3
void GUIController::Close(){
    Engine->close();
}
//but4
void GUIController::gotoVideo(){
    Engine2D->InitMenu5();
    sonido_accion(0);

}
//but5
void GUIController::gotoMusic(){
    Engine2D->setVolDialogo(dialogue);
    Engine2D->setVolMusic(music);
    Engine2D->setVolEffect(effect);
    sonido_accion(0);
}
//but6
void GUIController::gotoControlls(){
    Engine2D->InitMenu7();
    sonido_accion(0);
}
//but7
void GUIController::StartGame(){
    // s_musica_menu->stop();
    sonido_accion(0);
    Singleton<StateMachine>::Instance()->AddState(new Game(), true);
    // s_musica_basica->play();
}
//but8
void GUIController::gotoMain(){
    Engine2D->InitMenu();
    sonido_accion(1);
    if(s_musica_cred->isPaused()){
        s_musica_cred->stop();
        s_musica_menu->pause(false);
    }
}
//but9
void GUIController::dif1(){
    dif=1;
}
//but10
void GUIController::dif2(){
    dif=2;
}
//but11
void GUIController::dif3(){
    dif=3;
}
//but12
void GUIController::Continue(){
    Engine->resetClickVariable();
    Singleton<StateMachine>::Instance()->RemoveStates();
    sonido_accion(1);
    // s_musica_basica->pause(false);
}
//but13
void GUIController::ReturnMain(){
    Singleton<StateMachine>::Instance()->RemoveStates(2);
    Singleton<StateMachine>::Instance()->AddState(new MenuState());
    sonido_accion(0);
    // s_musica_basica->stop();
}
//but 14
void GUIController::initOptions(){
    Engine2D->InitOptions();
    sonido_accion(1);
}

//but 14
void GUIController::gotoPause(){
    Engine2D->InitPause();
}

void GUIController::musicaMenuPlay(){
  s_musica_menu->play();
}

void GUIController::musicaMenuStop(){
  s_musica_menu->stop();

}

void GUIController::musicaJuegoStop(){
  s_musica_basica->stop();

}
void GUIController::musicaMenuPause(bool b){
  s_musica_menu->pause(b);
}

void GUIController::musicaJuegoPlay(){
  s_musica_basica->play();

}
void GUIController::musicaJuegoPause(bool b){
  s_musica_basica->pause(b);

}


//but 18
void GUIController::moreDialog(){
    if(dialogue!=dialogue_max){
        dialogue=dialogue + 10;
    }
    Engine2D->setVolDialogo(dialogue);
    Engine2D->InitOptions();
    SS->setVolume(dialogue/40, "bus:/Voces");
}
//but 19
void GUIController::lessDialog(){
    if(dialogue!=0){
        dialogue= dialogue-10;
    }
    Engine2D->setVolDialogo(dialogue);
    Engine2D->InitOptions();
    SS->setVolume(dialogue/40, "bus:/Voces");
}

void GUIController::muteDialog(){
    SS->setMute("bus:/Voces");
    Engine2D->colorMute(MUTEDIALOD);
}
//but 20
void GUIController::moreMusic(){
    if(music!=music_max){
        music = music + 10;
    }
    Engine2D->setVolMusic(music);
    Engine2D->InitOptions();
    SS->setVolume(music/40, "bus:/Musica");
}
//but 21
void GUIController::lessMusic(){
    if(music!=0){
        music = music - 10;
    }
    Engine2D->setVolMusic(music);
    Engine2D->InitOptions();
    SS->setVolume(music/40, "bus:/Musica");
}

void GUIController::muteMusic(){
    SS->setMute("bus:/Musica");
    Engine2D->colorMute(MUTEMUSIC);

}
//but 22
void GUIController::moreEffect(){
    if(effect!=effect_max){
        effect = effect + 10;
    }
    Engine2D->setVolEffect(effect);
    Engine2D->InitOptions();
    SS->setVolume(effect/40, "bus:/SFX");
}
//but 23
void GUIController::lessEffect(){
    if(effect!=0){
        effect = effect - 10;
    }
    Engine2D->setVolEffect(effect);
    Engine2D->InitOptions();
    SS->setVolume(effect/40, "bus:/SFX");
}

void GUIController::muteEffect(){
    SS->setMute("bus:/SFX");
    Engine2D->colorMute(MUTEEFFECT);
}


void GUIController::sonido_accion(float param){
    s_accion->setParameter("Aceptar", param);
    s_accion->play();
}

Resolution::Resolution()
:WIDTH(848), HEIGHT(480)
{}

Resolution::Resolution(const Resolution &orig)
:WIDTH(orig.WIDTH), HEIGHT(orig.HEIGHT)
{}


void GUIController::invertCamera(){
    uint16_t HERO = _ObjectManager->getHeroID();
    IComponent* CAMERA_ICOMPONENT = _ObjectManager->getComponent(gg::CAMERA, HERO);

    if(CAMERA_ICOMPONENT){
        static_cast<CCamera*>(CAMERA_ICOMPONENT)->ToggleCameraInversionY();
    }
    Engine2D->InvertCamera();
    Singleton<Factory>::Instance()->ToggleInvertedCamera();
    Engine2D->InitOptions();

}

void GUIController::moreResolution(){
    if(CurrentResolution > 5) CurrentResolution = 5;
    if(CurrentResolution == 5) return;
    ++CurrentResolution;
    Engine->resizeFrameBuffers(RESOLUTIONS[CurrentResolution].WIDTH, RESOLUTIONS[CurrentResolution].HEIGHT);
    Engine2D->InitOptions();
}

void GUIController::lessResolution(){
    if(CurrentResolution < 0) CurrentResolution = 0;
    if(CurrentResolution == 0) return;

    --CurrentResolution;
    Engine->resizeFrameBuffers(RESOLUTIONS[CurrentResolution].WIDTH, RESOLUTIONS[CurrentResolution].HEIGHT);
    Engine2D->InitOptions();
}

void GUIController::moreBrightness(){
    if(LIGHTNING > 100) LIGHTNING = 5;
    if(LIGHTNING == 100) return;

    LIGHTNING += 5;
    Engine->setGlobalIlumination(LIGHTNING);
    Engine2D->InitOptions();

}

void GUIController::lessBrightness(){
    if(LIGHTNING < 0) LIGHTNING = 0;
    if(LIGHTNING == 0) return;

    LIGHTNING -= 5;
    Engine->setGlobalIlumination(LIGHTNING);
    Engine2D->InitOptions();

}
