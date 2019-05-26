#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <string>
#include "Singleton.hpp"
#include "Util.hpp"


#include <Omicron/2D/EnumButtonType.hpp>
#include <States/StateMachine.hpp>
#include <Omicron/Omicron.hpp>

#include <FMOD/SoundSystem.hpp>

class Motor2D;
template <typename T>
class Singleton;
class ObjectManager;

enum STATUS{
    IGNORE = 0,
    CHANGE_TO_GAME
};

struct Resolution{
    Resolution();
    Resolution(const Resolution &orig);
    int WIDTH;
    int HEIGHT;
};

class GUIController{
    friend class Singleton<GUIController>;
    public:
        GUIController();
        ~GUIController();
        STATUS update();
        STATUS musicaPause();
        STATUS musicaMenuPlay();
        STATUS musicaMenuStop();
        STATUS musicaJuegoStop();
        STATUS musicaMenuPause(bool);
        STATUS musicaJuegoPlay();
        STATUS musicaJuegoPause(bool);
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
        SoundSystem* SS;

        uint8_t LIGHTNING;
        uint8_t CurrentResolution;
        Resolution RESOLUTIONS[6];

STATUS gotoPlay();
STATUS gotoCredits();
STATUS gotoOptions();
STATUS Close();
STATUS gotoVideo();
STATUS gotoMusic();
STATUS gotoControlls();
STATUS StartGame();
STATUS gotoMain();
STATUS dif1();
STATUS dif2();
STATUS dif3();
STATUS Continue();
STATUS ReturnMain();
STATUS PgotoOptions();
STATUS PgotoVideo();
STATUS PgotoMusic();
STATUS PgotoControlls();
STATUS gotoPause();
STATUS moreDialog();
STATUS lessDialog();
STATUS muteDialog();
STATUS moreMusic();
STATUS lessMusic();
STATUS muteMusic();
STATUS moreEffect();
STATUS lessEffect();
STATUS muteEffect();
STATUS initOptions();
STATUS sonido_accion(float);
STATUS invertCamera();
STATUS moreResolution();
STATUS lessResolution();
STATUS moreBrightness();
STATUS lessBrightness();

        ObjectManager * _ObjectManager;
        Omicron* Engine;
        Motor2D* Engine2D;
        using pFunc = STATUS(GUIController::*)();
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
