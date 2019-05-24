#ifndef _OPTIONSTATE_H
#define _OPTIONSTATE_H

#include <Omicron/Omicron.hpp>
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

//#include <iostream>
#include "States/State.hpp"
#include <Omicron/2D/GUIController.hpp>
#include <FMOD/SoundSystem.hpp>
#include <Omicron/2D/Imagen2D.hpp>

class OptionState : public State{
public:
    OptionState();
    OptionState(const OptionState &orig) = delete;
    ~OptionState();
    //void update();
    //void RUN();
    virtual void CLIN();
    virtual void Init();
    virtual void Update();
    virtual void Resume();
    virtual void Pause() { }

    /*

    virtual void HandleInput() = 0;
    virtual void Draw(float dt) = 0;

    virtual void Pause() { }
    virtual void Resume() { }

    */

private:
    Omicron* Engine;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    GUIController* cont;

    SoundSystem* SS;
    unsigned int BACKGROUND_TEXTURE_ID;
    Imagen2D BACKGROUND;
};


#endif
