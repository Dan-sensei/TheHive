#ifndef _OBJECTMANAGER_H
#define _OBJECTMANAGER_H

#include "IComponent.hpp"
#include "Enum.hpp"
#include "Message.hpp"
#include <Arena.hpp>

#include <stack>
#include <map>
#include <vector>
#include <cstdint>

template <typename T>
class Singleton;

class ObjectManager{
    friend class Singleton<ObjectManager>;
    public:
        ~ObjectManager();

        //  ---
        //  Returns next available ID of the system
        //========================================================================
        uint16_t createEntity();

        //  ---
        //  Removes all the componentes from the given EntityID, and adds that
        //  ID to the nextAvailableEntityID stack
        //========================================================================
        void removeEntity(uint16_t targetID);

        //  ---
        //  Adds a component type to a given Entity (ID). It optionally can
        //  initialize the component data
        //========================================================================
        void addComponentToEntity(IComponent* Component, gg::EComponentType type, uint16_t EntityID);

        //  ---
        //  Delete component from given EntityID
        //========================================================================
        void removeComponentFromEntity(gg::EComponentType type, uint16_t EntityID);

        //  ---
        //  Defines wich kind of messages will receive each type of component
        //========================================================================
        void subscribeComponentTypeToMessageType(const gg::EComponentType &cType, const gg::MessageType &mType);

        //  ---
        //  Searchs and returns a pointer to the component of the given EntityID,
        //  if nothing is found, returns nullptr
        //========================================================================
        IComponent* getComponent(const gg::EComponentType &cType, const uint16_t &EntityID);

        //  ---
        //  Sends a message to every component of every entity in the system
        //  that expects to receive that message type
        //========================================================================
        void sendMessageToAllEntities(const Message &m);

        //  ---
        //  Sends a message to every component of the same entity that expects
        //  to receive that message type
        //========================================================================
        void sendMessageToEntity(uint16_t EntityID, const Message &m);

        //  ---
        //  Cleans the maps
        //========================================================================
        void clin();



        //german gay
        bool checkEvent(uint16_t EntityID, const Message &m);


    private:
        ObjectManager();
        ObjectManager(const ObjectManager &orig) = delete;
        void operator=(const ObjectManager &orig) = delete;


        //  ---
        //  Every position of this array, is a map wich contains all the
        //  entities IDs that contain that component type
        //
        // Mental scheme of TypeToComponentMap
        //
        //
        //                            [NUM_COMPONENTS]
        //
        //       TRANSFORM        COLLIDER       RENDERABLE        HEALTH
        //          [0]             [1]             [2]             [3]
        //           |               |               |               |
        //  MAPS:
        //       ID1, COMP_T     ID1, COMP_C     ID3, COMP_R     ID1, ICOM_H
        //       ID2, COMP_T     ID2, COMP_C     ID4, COMP_R     ID3, ICOM_H
        //       ID3, COMP_T     ID3, COMP_C     ID8, COMP_R     ID4, ICOM_H
        //       ID4, COMP_T     ID4, COMP_C                     ID9, ICOM_H
        //
        //========================================================================
        std::map<uint16_t, IComponent*> TypeToComponentMap[gg::NUM_COMPONENTS];

        //  ---
        //  Every position of this array, is a vector wich contains all the
        //  components types that expects to receive that kind of messge
        //
        // Mental scheme of MessageToListeingComponents
        //
        //
        //                            [MESSAGE_TYPE_COUNT]
        //
        //       M_UPDATE   [0]   => [COLLIDER, RENDERABLE, HEALTH]
        //       M_DAMAGE   [1]   => [HEALTH]
        //       M_RESPECT  [2]   => []
        //
        //========================================================================
        std::vector<gg::EComponentType> MessageToListeningComponents[gg::MESSAGE_TYPE_COUNT];

        std::stack<uint16_t> nextAvailableEntityID;

        //  ---
        //  Memory manager class
        //========================================================================
        Arena memory;
};

#endif
