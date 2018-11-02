#ifndef _ICOMPONENT_H
#define _ICOMPONENT_H

#include "Enum.hpp"
#include <cstdint>

class IComponent{
    friend class ObjectManager;
    public:
        IComponent();
        IComponent(const IComponent &orig) = delete;
        virtual ~IComponent();

        uint16_t getEntityID();

        virtual EComponentType getComponentType() = delete;
        virtual EMessageStatus processMessage();

    private:
        uint16_t EntityID;

        void setEntityID(uint16_t _ID);

};

#endif
