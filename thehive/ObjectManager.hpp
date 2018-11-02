#ifndef _OBJECTMANAGER_H
#define _OBJECTMANAGER_H

#include "IComponent.hpp"
#include "Enum.hpp"
#include "Arena.hpp"
#include <stack>
#include <map>
#include <cstdint>

class ObjectManager{
    public:
        ObjectManager();
        ObjectManager(const ObjectManager &orig) = delete;
        ~ObjectManager();

        uint16_t createEntity();
        void addComponentToEntity(EComponentType type, uint16_t EntityID);

    private:

        IComponent* createTransformComponent    ();
        //IComponent* createColliderComponent     ();
        //IComponent* createRenderableComponent   ();
        //IComponent* createHealthComponent       ();
        //IComponent* createRespectComponent      ();


        typedef IComponent* (ObjectManager::*pConstructor)(void);
        pConstructor map[NUM_COMPONENTS];

        std::map<uint16_t, IComponent*> TypeToComponentMap[NUM_COMPONENTS];
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
