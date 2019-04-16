#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <string>
#include "Singleton.hpp"
#include "Util.hpp"


#include <Omicron/2D/EnumButtonType.hpp>
#include <Omicron/KEYCODES.hpp>
#include <States/StateMachine.hpp>
#include <Omicron/Omicron.hpp>

#include <FMOD/SoundSystem.hpp>

class Motor2D;
template <typename T>
class Singleton;

class GUIController{
    friend class Singleton<GUIController>;
    public:
        GUIController();
        ~GUIController();
        void update();
        void setposmax(int p);
        void musicaPause();
        void musicaMenuPlay();
        void musicaMenuStop();
        void musicaJuegoStop();
        void musicaMenuPause(bool);
        void musicaJuegoPlay();
        void musicaJuegoPause(bool);
    private:
        int dif;
        float dialogue;
        float music;
        float effect;
        float dialogue_max;
        float music_max;
        float effect_max;
        int cursorpos;
        int posmax;
        bool arriba_pulsado;
        bool bajo_pulsado;
        bool enter_pulsado;
        bool back_pulsado;
        bool esc_pulsado;
        SoundSystem* SS;

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
void sonido_accion(float);


        Omicron* Engine;
        Motor2D* Engine2D;
        using pFunc = void(GUIController::*)();
        pFunc VectorAcciones[Butn];

        SoundEvent* s_accion;
        SoundEvent* s_musica_menu;
        SoundEvent* s_musica_cred;
        SoundEvent* s_musica_basica;
        bool reproduce;

        void Init();
        GUIController(const GUIController &orig) = delete;
};

#endif
