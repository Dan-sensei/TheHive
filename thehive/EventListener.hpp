#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H

#include <irrlicht/irrlicht.h>

class EventListener : public irr::IEventReceiver {
public:
    EventListener();

    virtual bool OnEvent(const irr::SEvent& event);
    virtual bool IsKeyDown(irr::EKEY_CODE keycode) const;
private:
    bool keyMap[irr::KEY_KEY_CODES_COUNT];
};

#endif
