/*
#include "Game.hpp"
#include <iostream>
#include <string>
#include <Singleton.hpp>
#include "GameAI/Pathfinding.hpp"
#include "GameAI/NavmeshStructs.hpp"
*/
//
// #include <iostream>
// #include <cstdint>
// #include <string>
// #include <stack>
//
// #include "ComponentArch/ObjectManager.hpp"
// #include "GameEngine/Camera.hpp"
// #include "Singleton.hpp"
// #include "GameAI/Pathfinding.hpp"
// #include "GameAI/NavmeshStructs.hpp"
//
// #include "GameEngine/ScreenConsole.hpp"
//
// #include "Factory.hpp"
// #include <ComponentArch/Components/CNavmeshAgent.hpp>
// #include <EventSystem/Blackboard.hpp>
//
// #include "States/StateMachine.hpp"
// #include "Game.hpp"
// #include "MenuState.hpp"
//
//
// int main(int argc, char const *argv[]) {
//     GameEngine *Engine = Singleton<GameEngine>::Instance();
//     CTriggerSystem *EventSystem = Singleton<CTriggerSystem>::Instance();
//
//     Engine->Starto();
//     //Engine->HideCursor(false);
//
//     ObjectManager *Manager = Singleton<ObjectManager>::Instance();
//
//     ggDynWorld *world = Singleton<ggDynWorld>::Instance();
//     world->inito();
//
//
//     //singleton StateMachine
//     //new GameState();
//     StateMachine *mainstates = Singleton<StateMachine>::Instance();
//     //mainstates->AddState(new GameState());
//     //mainstates->AddState(new GameState());
//     mainstates->AddState(new MenuState());
//
//     while(Engine->isWindowOpen()) {
//         mainstates->ProcessStateChanges();
//         mainstates->prueba();
//         mainstates->GetActiveState()->Update();
//     }
//
//     Blackboard::ClearGlobalBlackboard();
//     Manager->clin();
//     Engine->clean();
//     world->clean();
//     EventSystem->clin();
//     mainstates->clin();
//
//     return 0;
// }

#include <SurrealEngine/TNodo.hpp>
#include <SurrealEngine/TEntidad.hpp>
#include <SurrealEngine/TLuz.hpp>
#include <SurrealEngine/TCamara.hpp>
#include <SurrealEngine/TTransform.hpp>

int main(int argc, char const *argv[]) {

    TNodo* Escena = new TNodo();

    TTransform* RL = new TTransform();
    TTransform* RC = new TTransform();

    TTransform* TL = new TTransform();
    TTransform* TC = new TTransform();

    TLuz* L = new TLuz();
    TCamara* C = new TCamara(2.0,3.0,4.0);

    RL->rotate(2.0,gg::Vector3f(0, 5, 0));
    RC->rotate(2.9,gg::Vector3f(1, 3, 0));

    TL->translate(gg::Vector3f(2,3,4));
    TC->translate(gg::Vector3f(2,3,4));

    TNodo* RotaLuz = new TNodo(Escena, RL);
    TNodo* RotaCam = new TNodo(Escena, RC);

    TNodo* TraslaLuz = new TNodo(RotaLuz, TL);
    TNodo* TraslaCam = new TNodo(RotaCam, TC);


    TNodo* Luz = new TNodo(TraslaLuz, L);
    TNodo* Cam = new TNodo(TraslaLuz, C);

    TraslaLuz->addHijo(Luz);
    TraslaCam->addHijo(Cam);

    RotaLuz->addHijo(TraslaLuz);
    RotaCam->addHijo(TraslaCam);

    Escena->addHijo(RotaLuz);
    Escena->addHijo(RotaCam);


    //Escena->remHijo(RotaLuz);

    Escena->drawRoot();


    //
    // std::cout << "ESCENA ->          " << Escena << '\n';
    // std::cout << " RotaLuz - ID    = " << RotaLuz << '\n';
    // std::cout << " RotaLuz - Padre = " << RotaLuz->getPadre() << '\n';
    // std::cout << " RotaCam - ID    = " << RotaCam << '\n';
    // std::cout << " RotaCam - Padre = " << RotaCam->getPadre() << '\n';

    std::cout << "NodoLuz Padre    = " << Luz->getPadre() << '\n';
    delete Escena;
    return 0;
}
