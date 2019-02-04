/*
#include "Game.hpp"
#include <iostream>
#include <string>
#include <Singleton.hpp>
#include "GameAI/Pathfinding.hpp"
#include "GameAI/NavmeshStructs.hpp"
*/

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "GameEngine/Camera.hpp"
#include "Singleton.hpp"
#include "GameAI/Pathfinding.hpp"
#include "GameAI/NavmeshStructs.hpp"

#include "GameEngine/ScreenConsole.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>

#include "States/StateMachine.hpp"
#include "Game.hpp"
#include "MenuState.hpp"


int main(int argc, char const *argv[]) {
    GameEngine *Engine = Singleton<GameEngine>::Instance();
    CTriggerSystem *EventSystem = Singleton<CTriggerSystem>::Instance();

    Engine->Starto();
    //Engine->HideCursor(false);

    ObjectManager *Manager = Singleton<ObjectManager>::Instance();

    ggDynWorld *world = Singleton<ggDynWorld>::Instance();
    world->inito();


    //singleton StateMachine
    //new GameState();
    StateMachine *mainstates = Singleton<StateMachine>::Instance();
    //mainstates->AddState(new GameState());
    //mainstates->AddState(new GameState());
    mainstates->AddState(new MenuState());

    while(Engine->isWindowOpen()) {
        mainstates->ProcessStateChanges();
        mainstates->prueba();
        mainstates->GetActiveState()->Update();
    }

    Blackboard::ClearGlobalBlackboard();
    Manager->clin();
    Engine->clean();
    world->clean();
    EventSystem->clin();
    mainstates->clin();

    return 0;
}

// #include <SurrealEngine/TNodo.hpp>
// #include <SurrealEngine/TEntidad.hpp>
// #include <SurrealEngine/TLuz.hpp>
// #include <SurrealEngine/TTransform.hpp>
//
// int main(int argc, char const *argv[]) {
//     TNodo* Escena = new TNodo();
//
//     TTransform* RL = new TTransform();
//     TTransform* RC = new TTransform();
//
//     TLuz* L = new TLuz();
//
//     TNodo* RotaLuz = new TNodo(Escena, RL);
//     //TNodo* RotaCam = new TNodo(Escena, RC);
//
//     TNodo* NodoLuz = new TNodo(RotaLuz, L);
//
//     RotaLuz->addHijo(NodoLuz);
//     Escena->addHijo(RotaLuz);
//
//     //Escena->addHijo(RotaCam);
//
//
//     //Escena->remHijo(RotaLuz);
//
//     Escena->drawRoot();
//
//
//     //
//     // std::cout << "ESCENA ->          " << Escena << '\n';
//     // std::cout << " RotaLuz - ID    = " << RotaLuz << '\n';
//     // std::cout << " RotaLuz - Padre = " << RotaLuz->getPadre() << '\n';
//     // std::cout << " RotaCam - ID    = " << RotaCam << '\n';
//     // std::cout << " RotaCam - Padre = " << RotaCam->getPadre() << '\n';
//
//     std::cout << "NodoLuz Padre    = " << NodoLuz->getPadre() << '\n';
//     delete Escena;
//     return 0;
// }