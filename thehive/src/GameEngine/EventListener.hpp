#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H

#include <irrlicht/irrlicht.h>
#include "KEYCODES.hpp"

class EventListener : public irr::IEventReceiver {
public:
    EventListener();

    virtual bool OnEvent(const irr::SEvent& event);
    virtual bool IsKeyDown(gg::KEYCODES key) const;
    virtual bool isLClickPressed();
    virtual int getWheelValue();
private:
    bool keyMap[irr::KEY_KEY_CODES_COUNT];
    bool LCLICK;
    int wheel;
};

#endif
