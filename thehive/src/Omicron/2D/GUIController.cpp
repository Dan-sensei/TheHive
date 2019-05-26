#include "GUIController.hpp"
//#include <iostream>
#include <OptionState.hpp>
#include <Omicron/2D/Motor2D.hpp>
#include <Omicron/ZPlayer.hpp>
#include <PopState.hpp>
#include <MenuState.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Components/CCamera.hpp>
#include <Factory.hpp>

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

STATUS GUIController::update(){
    STATUS S = IGNORE;
    int id =Engine2D->checkbuton();
     if(id!=-1){
         if(VectorAcciones[id] != nullptr)
             S = (this->*VectorAcciones[id])();
     }

     if(!s_musica_menu->isPaused()){
         s_musica_menu->pause(false);
     }
     return S;
}
//but0
STATUS GUIController::gotoPlay(){
    sonido_accion(0);
    dif=1;
    Engine2D->InitMenu2();
    return IGNORE;
}
//but1
STATUS GUIController::gotoCredits(){
    s_musica_menu->pause(true);
    sonido_accion(0);
    ZPlayer Player;
    Player.PlayVideo("assets/Video/creditos.mp4","event:/Musica/Menu/MusicaCreditos");
    return IGNORE;
    //Engine2D->InitMenu3();
}
//but2
STATUS GUIController::gotoOptions(){
    sonido_accion(0);
    Singleton<StateMachine>::Instance()->AddState(new OptionState(),false);
    Engine2D->setVolDialogo(dialogue);
    Engine2D->setVolMusic(music);
    Engine2D->setVolEffect(effect);
    return IGNORE;
}
//but3
STATUS GUIController::Close(){
    Engine->close();
    return IGNORE;
}
//but4
STATUS GUIController::gotoVideo(){
    Engine2D->InitMenu5();
    sonido_accion(0);
    return IGNORE;

}
//but5
STATUS GUIController::gotoMusic(){
    Engine2D->setVolDialogo(dialogue);
    Engine2D->setVolMusic(music);
    Engine2D->setVolEffect(effect);
    sonido_accion(0);
    return IGNORE;
}
//but6
STATUS GUIController::gotoControlls(){
    Engine2D->InitMenu7();
    sonido_accion(0);
    return IGNORE;
}
//but7
STATUS GUIController::StartGame(){
    // s_musica_menu->stop();
    sonido_accion(0);
    // s_musica_basica->play();
    return CHANGE_TO_GAME;
}
//but8
STATUS GUIController::gotoMain(){
    Engine2D->InitMenu();
    sonido_accion(1);
    if(s_musica_cred->isPaused()){
        s_musica_cred->stop();
        s_musica_menu->pause(false);
    }
    return IGNORE;
}
//but9
STATUS GUIController::dif1(){
    dif=1;
    return IGNORE;
}
//but10
STATUS GUIController::dif2(){
    dif=2;
    return IGNORE;
}
//but11
STATUS GUIController::dif3(){
    dif=3;
    return IGNORE;
}
//but12
STATUS GUIController::Continue(){
    Engine->resetClickVariable();
    Singleton<StateMachine>::Instance()->RemoveStates();
    sonido_accion(1);
    return IGNORE;
    // s_musica_basica->pause(false);
}
//but13
STATUS GUIController::ReturnMain(){
    Singleton<StateMachine>::Instance()->RemoveStates(2);
    Singleton<StateMachine>::Instance()->AddState(new MenuState());
    sonido_accion(0);
    return IGNORE;
    // s_musica_basica->stop();
}
//but 14
STATUS GUIController::initOptions(){
    Engine2D->InitOptions();
    sonido_accion(1);
    return IGNORE;
}

//but 14
STATUS GUIController::gotoPause(){
    Engine2D->InitPause();
    return IGNORE;
}

STATUS GUIController::musicaMenuPlay(){
  s_musica_menu->play();
  return IGNORE;
}

STATUS GUIController::musicaMenuStop(){
  s_musica_menu->stop();
  return IGNORE;

}

STATUS GUIController::musicaJuegoStop(){
  s_musica_basica->stop();
  return IGNORE;

}
STATUS GUIController::musicaMenuPause(bool b){
  s_musica_menu->pause(b);
  return IGNORE;
}

STATUS GUIController::musicaJuegoPlay(){
  s_musica_basica->play();
  return IGNORE;

}
STATUS GUIController::musicaJuegoPause(bool b){
  s_musica_basica->pause(b);
  return IGNORE;

}


//but 18
STATUS GUIController::moreDialog(){
    if(dialogue!=dialogue_max){
        dialogue=dialogue + 10;
    }
    Engine2D->setVolDialogo(dialogue);
    Engine2D->InitOptions();
    SS->setVolume(dialogue/40, "bus:/Voces");
    return IGNORE;
}
//but 19
STATUS GUIController::lessDialog(){
    if(dialogue!=0){
        dialogue= dialogue-10;
    }
    Engine2D->setVolDialogo(dialogue);
    Engine2D->InitOptions();
    SS->setVolume(dialogue/40, "bus:/Voces");
    return IGNORE;
}

STATUS GUIController::muteDialog(){
    SS->setMute("bus:/Voces");
    Engine2D->colorMute(MUTEDIALOD);
    return IGNORE;
}
//but 20
STATUS GUIController::moreMusic(){
    if(music!=music_max){
        music = music + 10;
    }
    Engine2D->setVolMusic(music);
    Engine2D->InitOptions();
    SS->setVolume(music/40, "bus:/Musica");
    return IGNORE;
}
//but 21
STATUS GUIController::lessMusic(){
    if(music!=0){
        music = music - 10;
    }
    Engine2D->setVolMusic(music);
    Engine2D->InitOptions();
    SS->setVolume(music/40, "bus:/Musica");
    return IGNORE;
}

STATUS GUIController::muteMusic(){
    SS->setMute("bus:/Musica");
    Engine2D->colorMute(MUTEMUSIC);

    return IGNORE;
}
//but 22
STATUS GUIController::moreEffect(){
    if(effect!=effect_max){
        effect = effect + 10;
    }
    Engine2D->setVolEffect(effect);
    Engine2D->InitOptions();
    SS->setVolume(effect/40, "bus:/SFX");
    return IGNORE;
}
//but 23
STATUS GUIController::lessEffect(){
    if(effect!=0){
        effect = effect - 10;
    }
    Engine2D->setVolEffect(effect);
    Engine2D->InitOptions();
    SS->setVolume(effect/40, "bus:/SFX");
    return IGNORE;

}

STATUS GUIController::muteEffect(){
    SS->setMute("bus:/SFX");
    Engine2D->colorMute(MUTEEFFECT);
    return IGNORE;
}


STATUS GUIController::sonido_accion(float param){
    s_accion->setParameter("Aceptar", param);
    s_accion->play();
    return IGNORE;
}

Resolution::Resolution()
:WIDTH(848), HEIGHT(480)
{}

Resolution::Resolution(const Resolution &orig)
:WIDTH(orig.WIDTH), HEIGHT(orig.HEIGHT)
{}


STATUS GUIController::invertCamera(){
    uint16_t HERO = _ObjectManager->getHeroID();
    IComponent* CAMERA_ICOMPONENT = _ObjectManager->getComponent(gg::CAMERA, HERO);

    if(CAMERA_ICOMPONENT){
        static_cast<CCamera*>(CAMERA_ICOMPONENT)->ToggleCameraInversionY();
    }
    Engine2D->InvertCamera();
    Singleton<Factory>::Instance()->ToggleInvertedCamera();
    Engine2D->InitOptions();
    return IGNORE;

}

STATUS GUIController::moreResolution(){
    if(CurrentResolution > 5) CurrentResolution = 5;
    if(CurrentResolution == 5) return IGNORE;
    ++CurrentResolution;
    Engine->resizeFrameBuffers(RESOLUTIONS[CurrentResolution].WIDTH, RESOLUTIONS[CurrentResolution].HEIGHT);
    Engine2D->InitOptions();
    return IGNORE;
}

STATUS GUIController::lessResolution(){
    if(CurrentResolution < 0) CurrentResolution = 0;
    if(CurrentResolution == 0) return IGNORE;

    --CurrentResolution;
    Engine->resizeFrameBuffers(RESOLUTIONS[CurrentResolution].WIDTH, RESOLUTIONS[CurrentResolution].HEIGHT);
    Engine2D->InitOptions();
    return IGNORE;
}

STATUS GUIController::moreBrightness(){
    if(LIGHTNING > 100) LIGHTNING = 5;
    if(LIGHTNING == 100) return IGNORE;

    LIGHTNING += 5;
    Engine->setGlobalIlumination(LIGHTNING);
    Engine2D->InitOptions();
    return IGNORE;

}

STATUS GUIController::lessBrightness(){
    if(LIGHTNING < 0) LIGHTNING = 0;
    if(LIGHTNING == 0) return IGNORE;

    LIGHTNING -= 5;
    Engine->setGlobalIlumination(LIGHTNING);
    Engine2D->InitOptions();
    return IGNORE;
}
