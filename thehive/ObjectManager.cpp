#include "ObjectManager.hpp"
#include "CTransform.hpp"
#include <iostream>
                     //  2^16
#define MAX_ENTITIES 65536

void *operator new(std::size_t size, Arena &A){
    return A.allocate(size);
}

void operator delete(void* p, Arena &A){
    return A.deallocate(p);
}

ObjectManager::ObjectManager()
:memory(128)
{
    nextAvailableEntityID.push(1);

    map[0]= &ObjectManager::createTransformComponent;
    //map[1]= &ObjectManager::createColliderComponent;
    //map[2]= &ObjectManager::createRenderableComponent;
    //map[3]= &ObjectManager::createHealthComponent;
    //map[4]= &ObjectManager::createRespectComponent;
}


ObjectManager::~ObjectManager() {
    std::cout << "Destruyendo todos los componentes..." << '\n';
    uint8_t i = gg::NUM_COMPONENTS;
    while (i--){
        std::map<uint16_t, IComponent*>::iterator it=TypeToComponentMap[i].begin();

        while(it!=TypeToComponentMap[i].end()){
            std::cout << "  -Eliminando componente " << (int)i << " de entidad " << it->first << '\n';
            it->second->~IComponent();
            memory.deallocate(it->second);
            ++it;
        };

    }
}

void ObjectManager::initObjectManager(){
    CTransform::initComponent();
}

// ==========================================================
//  Devuelve el próximo ID libre en el que crear una entidad
// ==========================================================
uint16_t ObjectManager::createEntity() {
    uint16_t ID = nextAvailableEntityID.top();
    uint16_t Next = ID;
    nextAvailableEntityID.pop();
    if(nextAvailableEntityID.empty()){
        ++Next;
        if(Next > MAX_ENTITIES){    // Usaré el ID 0 para entidades no incializadas,
                                    // por lo que la condicion es ">" en vez de ">="
            Next = 0;
            // LOG: LIMITE DE ENTIDADES ALCANZADO
        }
        nextAvailableEntityID.push(Next);
    }
    return ID;
}


void ObjectManager::addComponentToEntity(gg::EComponentType type, uint16_t EntityID) {
    IComponent* newComponent;
    pConstructor constructor = map[type];

    if(constructor != nullptr)
        newComponent = (this->*constructor)();

    std::cout << "  -Añadiendo componente " << type << " a entidad " << EntityID << '\n';
    newComponent->setEntityID(EntityID);
    TypeToComponentMap[type].insert(std::make_pair(EntityID, newComponent));
}



void ObjectManager::subscribeComponentTypeToMessageType(const gg::EComponentType &cType, const gg::MessageType &mType) {
    MessageToListeingComponents[mType].push_back(cType);
}


void ObjectManager::sendMessageToAllEntities(const gg::MessageType &mType){

    std::vector<gg::EComponentType>::iterator componentsIterator = MessageToListeingComponents[mType].begin();
    std::map<uint16_t, IComponent*>::iterator entitiesIterator;
    while(componentsIterator != MessageToListeingComponents[mType].end()){

        std::map<uint16_t, IComponent*>::iterator entitiesEnd = TypeToComponentMap[*componentsIterator].end();
        entitiesIterator = TypeToComponentMap[*componentsIterator].begin();

        while(entitiesIterator != entitiesEnd) {
            entitiesIterator->second->processMessage();
            ++entitiesIterator;
        }
        ++componentsIterator;
    }

}

void ObjectManager::sendMessageToEntity(uint16_t EntityID, const gg::MessageType &mType){

    std::vector<gg::EComponentType>::iterator componentsIterator = MessageToListeingComponents[mType].begin();
    std::map<uint16_t, IComponent*> entitiesMap;
    while(componentsIterator != MessageToListeingComponents[mType].end()){

        entitiesMap = TypeToComponentMap[*componentsIterator];

        std::map<uint16_t, IComponent*>::iterator EntityFound;
        EntityFound = entitiesMap.find(EntityID);

        if(EntityFound != entitiesMap.end()){
            EntityFound->second->processMessage();
        }

        ++componentsIterator;
    }
}

IComponent* ObjectManager::createTransformComponent    ()   {
    return new CTransform;
}
//IComponent* ObjectManager::createColliderComponent     ();
//IComponent* ObjectManager::createRenderableComponent   ();
//IComponent* ObjectManager::createHealthComponent       ();
//IComponent* ObjectManager::createRespectComponent      ();
