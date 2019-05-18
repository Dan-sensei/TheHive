#ifndef _POPSTATE_H
#define _POPSTATE_H

#include <Omicron/Omicron.hpp>
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

//#include <iostream>
#include "States/State.hpp"
#include <Omicron/SkyBox.hpp>
#include <Omicron/2D/GUIController.hpp>
#include <FMOD/SoundSystem.hpp>

class PopState : public State {
public:
    PopState();
    PopState(const PopState &orig) = delete;
    virtual ~PopState();
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
    void siguiente();

    void Addim(std::string im);
private:
    Omicron* Engine;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    GUIController* _GUIController;

    SoundSystem* SS;
    int cont;
    std::vector<std::string> imagenes;


};


#endif
