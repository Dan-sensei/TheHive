#ifndef _ICOMPONENT_H
#define _ICOMPONENT_H

#include "Enum.hpp"
#include "MessageTypes.hpp"
#include <cstdint>

class IComponent{
    //  We make this class friend of ObjectManger, so it can access the setEntityID method
    friend class ObjectManager;
    public:
        IComponent(const IComponent &orig) = delete;
        virtual ~IComponent();

        //  ---
        //  Returns the EntityID
        //========================================================================
        uint16_t getEntityID();

        //virtual gg::EComponentType getComponentType() = delete;

        //  ---
        //  Process the message and returns a message status
        //========================================================================
        virtual gg::EMessageStatus processMessage();

        //  ---
        //  Initializes the component data
        //========================================================================
        virtual void initializeComponentData(const void* data);

    protected:
        IComponent();

    private:

        uint16_t EntityID;

        //  ---
        //  We just set the EntityID
        //========================================================================
        void setEntityID(uint16_t _ID);

};

#endif
