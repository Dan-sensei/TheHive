#ifndef _MENUSTATE_H
#define _MENUSTATE_H

#include <Omicron/Omicron.hpp>
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

//#include <iostream>
#include "States/State.hpp"
#include <Omicron/2D/GUIController.hpp>
#include <FMOD/SoundSystem.hpp>
#include <Omicron/2D/Imagen2D.hpp>

class MenuState : public State{
public:
    MenuState();
    MenuState(const MenuState &orig) = delete;
    virtual ~MenuState();
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
    ObjectManager* Manager;
    ggDynWorld* world;
    GUIController* cont;

    gg::Clock MasterClock;
    SoundSystem* SS;
    TCamara* Camera;
    glm::vec3 OriginalTarget;
    glm::vec3 CurrentTarget;
    glm::vec3 RandomTarget;
    Imagen2D Menu;
};


#endif
