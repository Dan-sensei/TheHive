#include <iostream>
#include "Singleton.hpp"
#include "Agent.hpp"
#include "Vector.hpp"
#include "Time.hpp"
#include <irrlicht/irrlicht.h>
//#include <irrlicht/irrList.h>
#include <irrlicht/IEventReceiver.h>
using namespace irr;

class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};



/**
int main(int argc, char const *argv[]) {
    // start up the engine

    std::cout << "Ey yo wassup my nigga" << std::endl;

    MyEventReceiver receiver;

    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
        core::dimension2d<u32>(640,480),16, false, false, false, &receiver);

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* scenemgr = device->getSceneManager();


    device->setWindowCaption(L"Hello World!");

    // load and show quake2 .md2 model
    scene::ISceneNode* node = scenemgr->addAnimatedMeshSceneNode(
        scenemgr->getMesh("quake2model.md2"));

    // if everything worked, add a texture and disable lighting
    if (node)
    {
        node->setMaterialTexture(0, driver->getTexture("texture.bmp"));
        node->setMaterialFlag(video::EMF_LIGHTING, false);
    }

    // add a first person shooter style user controlled camera
    scenemgr->addCameraSceneNodeFPS();

    // draw everything
    while(device->run() && driver)
    {
      if(receiver.IsKeyDown(irr::KEY_KEY_W)){
        std::cout << "Ey yo wassup my nigga" << std::endl;

        }

        driver->beginScene(true, true, video::SColor(255,0,0,255));
        scenemgr->drawAll();
        driver->endScene();
    }

    // delete device
    device->drop();
    return 0;
 }*/
int main(int argc, char const *argv[]) {

    //IEventReceiver::SKeyInput(KeyInput)
    //if(IEventReceiver::OnEvent (IEventReceiver::KeyInput))return 0;
    CAgent* pAgent=NULL;

    pAgent=new CAgent(kTrig_Gunfire,Vector(4,5,0));
    CAgent::hola.push_back(pAgent);
    std::cout << "Id agente 1:"<<pAgent->nCAgentID << std::endl;
    pAgent=new CAgent(kTrig_EnemyNear,Vector(3,2,0));
    CAgent::hola.push_back(pAgent);
    std::cout << "Id agente 1:"<<pAgent->nCAgentID << std::endl;

    pAgent=new CAgent(kTrig_EnemyNear,Vector(77,77,0));
    CAgent::hola.push_back(pAgent);
    std::cout << "Id agente 1:"<<pAgent->nCAgentID << std::endl;

    pAgent=new CAgent(kTrig_Gunfire,Vector());
    CAgent::hola.push_back(pAgent);
    std::cout << "Id agente 1:"<<pAgent->nCAgentID << std::endl;

    pAgent=new CAgent(kTrig_EnemyNear|kTrig_Gunfire,Vector(77,77,0));
    CAgent::hola.push_back(pAgent);
    std::cout << "Id agente 1:"<<pAgent->nCAgentID << std::endl;

    CAgent::hola.size();
    TriggerRecordStruct(kTrig_Explosion,6, Vector(),4,2,false);
    CTriggerSystem* sistemita = Singleton<CTriggerSystem>::Instance();
    unsigned long id_puesto=sistemita->RegisterTriger(kTrig_Gunfire,3,0,Vector(), 10, 2,false);
    id_puesto=sistemita->RegisterTriger(kTrig_EnemyNear,1,0,Vector(), 150, 2,false);
    sistemita->Update();
    sistemita->RemoveTrigger(id_puesto);

                        //(EnumTriggerType _eTriggerType,unsigned long _idSource,const Vector _vPos,float _fRadius,
                          //                  unsigned long _fDuration,bool _bDynamicSourcePos);
    irr::core::list<CAgent*>::Iterator it =CAgent::hola.begin();

    while(it!=CAgent::hola.end()){
      std::cout << "Entre" << std::endl;

      it++;
    }
    std::cout << "Ey yo wassup my nigga" << std::endl;

    //erase(Iterator& it);
     //insert_before(Iterator& it);
     //hola->second

    return 0;
}
