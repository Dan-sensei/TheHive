#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <irrlicht/irrlicht.h>
#include <string>
#include "Singleton.hpp"
#include "Util.hpp"

#include <GameEngine/GameEngine.hpp>
#include <GameEngine/ScreenConsole.hpp>
#include <GameEngine/EnumButtonType.hpp>
#include <GameEngine/KEYCODES.hpp>
#include <States/StateMachine.hpp>
#include <GameState.hpp>

class GameEngine;


class GUIController{
    public:
        GUIController();
        void update();
        void setposmax(int p);
    private:
        int dif;
        int cursorpos;
        int posmax;
        bool arriba_pulsado;
        bool bajo_pulsado;
        bool enter_pulsado;
        bool back_pulsado;
        bool esc_pulsado;

void gotoPlay();
void gotoCredits();
void gotoOptions();
void Close();
void gotoVideo();
void gotoMusic();
void gotoControlls();
void StartGame();
void gotoMain();
void dif1();
void dif2();
void dif3();
void Continue();
void ReturnMain();


        GameEngine* Engine;
        using pFunc = void(GUIController::*)();
        pFunc VectorAcciones[Butn];

        void Init();
        GUIController(const GUIController &orig) = delete;
};

#endif
