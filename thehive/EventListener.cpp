#include "EventListener.hpp"
#include <cstdint>

EventListener::EventListener(){
    uint16_t i = irr::KEY_KEY_CODES_COUNT;
    while(i--)  keyMap[i] = false;
}

bool EventListener::OnEvent(const irr::SEvent& event) {
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        keyMap[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
}

// This is used to check whether a key is being held down
bool EventListener::IsKeyDown(irr::EKEY_CODE keyCode) const {
    return keyMap[keyCode];
}
