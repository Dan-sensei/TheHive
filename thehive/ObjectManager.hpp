#ifndef _OBJECTMANAGER_H
#define _OBJECTMANAGER_H

#include "IComponent.hpp"
#include "Enum.hpp"
#include "MessageTypes.hpp"
#include "Arena.hpp"

#include "CTransform.hpp"
#include "CKeyboard.hpp"
#include "CRenderable_3D.hpp"

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

        void initObjectManager();

        uint16_t createEntity();
        void addComponentToEntity(gg::EComponentType type, uint16_t EntityID, const void* initData = nullptr);
        void subscribeComponentTypeToMessageType(const gg::EComponentType &cType, const gg::MessageType &mType);
        IComponent* getComponent(const gg::EComponentType &cType, const uint16_t &EntityID);

        void sendMessageToAllEntities(const gg::MessageType &mType);
        void sendMessageToEntity(uint16_t EntityID, const gg::MessageType &mType);

    private:
        ObjectManager();
        ObjectManager(const ObjectManager &orig) = delete;
        void operator=(const ObjectManager &orig) = delete;

        IComponent* createTransformComponent        ();
        IComponent* createKeyboardComponent         ();
        IComponent* createRenderable_3DComponent    ();
        //IComponent* createColliderComponent     ();
        //IComponent* createRenderableComponent   ();
        //IComponent* createHealthComponent       ();
        //IComponent* createRespectComponent      ();


        typedef IComponent* (ObjectManager::*pConstructor)(void);
        pConstructor map[gg::NUM_COMPONENTS];

        std::map<uint16_t, IComponent*> TypeToComponentMap[gg::NUM_COMPONENTS];
        std::vector<gg::EComponentType> MessageToListeingComponents[gg::MESSAGE_TYPE_COUNT];

        std::stack<uint16_t> nextAvailableEntityID;
        Arena memory;
};

#endif

// ESQUEMA MENTAL DE TypeToComponentMap
//
//
//                            [NUM_COMPONENTS]
//
//       TRANSFORM        COLLIDER       RENDERABLE        HEALTH
//          [0]             [1]             [2]             [3]
//           |               |               |               |
//  MAPAS:
//       ID, COMP_T      ID, COMP_C       ID, COMP_R       ID, ICOM_H
//       ID, COMP_T      ID, COMP_C       ID, COMP_R       ID, ICOM_H
//       ID, COMP_T      ID, COMP_C       ID, COMP_R       ID, ICOM_H
//       ID, COMP_T      ID, COMP_C                        ID, ICOM_H
//
