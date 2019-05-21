#ifndef _POPSTATE_H
#define _POPSTATE_H

#include <Omicron/Omicron.hpp>
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

//#include <iostream>
#include "States/State.hpp"
#include <FMOD/SoundSystem.hpp>
#include <FMOD/SonidoNormal.hpp>

class PopState : public State {
public:
    PopState();
    PopState(const PopState &orig) = delete;
    ~PopState();
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

    void Addim(unsigned int im);
private:
    Omicron* Engine;
    CTriggerSystem* EventSystem;
    Shader* SH;

    SoundSystem* SS;
    SoundEvent* nextImage;

    unsigned int QUAD;
    unsigned int QUAD_POS_UV;
    std::vector<unsigned int> imagenes;


};


#endif
