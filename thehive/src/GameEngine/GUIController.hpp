#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <irrlicht/irrlicht.h>
#include <string>
#include "Singleton.hpp"
#include "Util.hpp"


#include <GameEngine/EnumButtonType.hpp>
#include <GameEngine/KEYCODES.hpp>
#include <States/StateMachine.hpp>
#include <SurrealEngine/SurrealEngine.hpp>

class Motor2D;

class GUIController{
    public:
        GUIController(int _id);
        GUIController();
        void update();
        void setposmax(int p);
    private:
        int dif;
        int dialogue;
        int music;
        int effect;
        int dialogue_max;
        int music_max;
        int effect_max;
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
void PgotoOptions();
void PgotoVideo();
void PgotoMusic();
void PgotoControlls();
void gotoPause();
void moreDialog();
void lessDialog();
void moreMusic();
void lessMusic();
void moreEffect();
void lessEffect();
void initOptions();

void visto();
void novisto();
void viendo();
void ultrasi();
void ultrano();

        int id;

        SurrealEngine* Engine;
        Motor2D* Engine2D;
        using pFunc = void(GUIController::*)();
        pFunc VectorAcciones[Butn];

        void Init();
        GUIController(const GUIController &orig) = delete;
};

#endif
