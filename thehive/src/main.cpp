//#include <iostream>

#include <Omicron/Omicron.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include "Singleton.hpp"
#include "GameAI/Pathfinding.hpp"

#include <Omicron/2D/Motor2D.hpp>

#include "States/StateMachine.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include <FMOD/SoundSystem.hpp>
#include <FMOD/SonidoNormal.hpp>
#include <Omicron/ZPlayer.hpp>

int main(int argc, char const *argv[]) {

    Omicron *Engine = Singleton<Omicron>::Instance();
    Engine->resetSceneGraph();

    Singleton<AssetManager>::Instance()->loadInit();

    SoundSystem *Sound = Singleton<SoundSystem>::Instance();

    {
        ZPlayer Player;
        Player.PlayVideo("assets/Video/LOGO.mp4","event:/Musica/Videos/VideoLogoEmpresa");
        Player.PlayVideo("assets/Video/TheHiveLogoAnimation.mp4","event:/Musica/Videos/VideoLogoJuego");
    }

    CTriggerSystem *EventSystem = Singleton<CTriggerSystem>::Instance();
    //Engine->Starto();
    //Engine->HideCursor(false);

    ObjectManager *Manager = Singleton<ObjectManager>::Instance();

    ggDynWorld *world = Singleton<ggDynWorld>::Instance();
    world->inito();

    StateMachine *mainstates = Singleton<StateMachine>::Instance();
    mainstates->AddState(new Game());

    while(Engine->isWindowOpen()) {
        mainstates->UpdateStateMachine();
    }

    Blackboard::ClearGlobalBlackboard();
    Manager->clin();
    world->clean();
    EventSystem->clin();
    mainstates->clin();
    Engine->clean();

    return 0;
}
