#include "ObjectManager.hpp"
//#include "Enum.hpp"
#include <GameAI/Pathfinding.hpp>
#include <Singleton.hpp>
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

    //  Defines wich kind of messages will receive each type of component
    //  We just insert in the array of vectors, the component type in the messageTYpe array position
    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::VIDA);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::M_EVENT_ACTION].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::M_INTERPOLATE_PRESAVE].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::M_INTERPOLATE_POSTSAVE].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::M_INTERPOLATE].push_back(gg::RIGID_BODY);


    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::RENDERABLE_3D);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::PLAYERCONTROLLER);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::NAVMESHAGENT);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::HAB);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::GUN);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::GRANADE);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::CLOCK);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::AIENEM);



    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::CAMERA);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::AGENT);

}


//  ---
//  Iterates over every component desallocating memory
//========================================================================
ObjectManager::~ObjectManager() {

}

void ObjectManager::clin(){
    // std::cout << "Destruyendo todos los componentes..." << '\n';
    uint8_t i = gg::NUM_COMPONENTS;
    while (i--){
        std::map<uint16_t, IComponent*>::iterator it=TypeToComponentMap[i].begin();

        while(it!=TypeToComponentMap[i].end()){
            // std::cout << "  -Eliminando componente " << (int)i << " de entidad " << it->first << '\n';
            //it->second->~IComponent();
            //memory.deallocate(it->second);
            delete it->second;
            ++it;
        };
    }
    Singleton<Pathfinding>::Instance()->clear();    //  Provisional
}



uint16_t ObjectManager::createEntity() {
    //  The stack will usually contain only one element wich will
    //  be the next ID (Ex: If current is 2, next will be 3)
    uint16_t ID = nextAvailableEntityID.top();
    nextAvailableEntityID.pop();

    uint16_t Next = ID;

    //  But, if the stacks is not empty, that means there are free
    //  ID positions before, so we don't update the ID
    if(nextAvailableEntityID.empty()){

        // If the stacks is empty, we just increment the ID
        ++Next;
        if(Next > MAX_ENTITIES){    // ID 0 will be used for not initialized entities,
                                    // therefore, the condition will be ">" instead of ">="
            Next = 0;
            // LOG: MAX ENTITIES LIMIT REACHED!
        }
        // And put that ID in the stack for next generation
        nextAvailableEntityID.push(Next);
    }
    return ID;
}


void ObjectManager::removeEntity(uint16_t targetID){
    nextAvailableEntityID.push(targetID);

    uint8_t i = gg::NUM_COMPONENTS;
    while (i--) removeComponentFromEntity(static_cast<gg::EComponentType>(i), targetID, true);
}


void ObjectManager::addComponentToEntity(IComponent* Component, gg::EComponentType type, uint16_t EntityID) {

    //  We set the entityID to that component
    Component->setEntityID(EntityID);

    //  And insert in the map, the ID with is assigned component
    TypeToComponentMap[type].insert(std::make_pair(EntityID, Component));

    //  We call the init method of the Component :)
    Component->Init();
}

void ObjectManager::removeComponentFromEntity(gg::EComponentType type, uint16_t EntityID, bool Erase){
    auto foundComponent = TypeToComponentMap[type].find(EntityID);

    if(foundComponent == TypeToComponentMap[type].end())
        return;

    // std::cout << "B Component " << type << '\n';
    delete foundComponent->second;
    TypeToComponentMap[type].erase(foundComponent);

    if(Erase) return;

    Message recalculatePointersToAnotherComponents(gg::M_SETPTRS);
    sendMessageToEntity(EntityID, recalculatePointersToAnotherComponents);
    // std::cout << "Deleting" << '\n';
}

void ObjectManager::removeComponentFromEntityMAP(gg::EComponentType type, uint16_t EntityID){
    auto foundComponent = TypeToComponentMap[type].find(EntityID);

    if(foundComponent == TypeToComponentMap[type].end())
        return;

    TypeToComponentMap[type].erase(foundComponent);
}

void ObjectManager::sendMessageToAllEntities(const Message &m){
    // We iterate over every component in the map that expects to receive that kind of message

    std::vector<gg::EComponentType>::iterator componentsIterator = MessageToListeningComponents[m.mType].begin();
    std::map<uint16_t, IComponent*>::iterator entitiesIterator;
    // First we search for a component type that expects that message type
    while(componentsIterator != MessageToListeningComponents[m.mType].end()){

        //  Found one!
        entitiesIterator = TypeToComponentMap[*componentsIterator].begin();
        //  Now we iterate over every entity that contains that component type
        while(entitiesIterator != TypeToComponentMap[*componentsIterator].end()) {
            auto current = entitiesIterator;
            ++entitiesIterator;
            //  We process the message
            current->second->processMessage(m);
        }

        ++componentsIterator;
    }
}

void ObjectManager::UpdateAll(){
    uint8_t i = 0;
    while (i < gg::NUM_COMPONENTS){
        std::map<uint16_t, IComponent*>::iterator it=TypeToComponentMap[i].begin();
        while(it!=TypeToComponentMap[i].end()){
            auto current = it;
            ++it;
            current->second->Update();
        };
        ++i;
    }
}

void ObjectManager::FixedUpdateAll(){
    uint8_t i = 0;
    while (i < gg::NUM_COMPONENTS){
        std::map<uint16_t, IComponent*>::iterator it=TypeToComponentMap[i].begin();
        while(it!=TypeToComponentMap[i].end()){
            auto current = it;
            ++it;
            current->second->FixedUpdate();
        };
        ++i;
    }
}



void ObjectManager::sendMessageToEntity(uint16_t EntityID, const Message &m){

    // Same as sendMessageToAllEntities, but just for one EntityID
    std::vector<gg::EComponentType>::iterator componentsIterator = MessageToListeningComponents[m.mType].begin();
    std::map<uint16_t, IComponent*> entitiesMap;
    while(componentsIterator != MessageToListeningComponents[m.mType].end()){

        entitiesMap = TypeToComponentMap[*componentsIterator];

        std::map<uint16_t, IComponent*>::iterator EntityFound;
        EntityFound = entitiesMap.find(EntityID);

        if(EntityFound != entitiesMap.end()){
            EntityFound->second->processMessage(m);
        }

        ++componentsIterator;
    }
}

bool ObjectManager::checkEvent(uint16_t EntityID, const Message &m){

    // Same as sendMessageToAllEntities, but just for one EntityID
    std::vector<gg::EComponentType>::iterator componentsIterator = MessageToListeningComponents[m.mType].begin();
    std::map<uint16_t, IComponent*> entitiesMap;
    while(componentsIterator != MessageToListeningComponents[m.mType].end()){

        entitiesMap = TypeToComponentMap[*componentsIterator];

        std::map<uint16_t, IComponent*>::iterator EntityFound;
        EntityFound = entitiesMap.find(EntityID);

        if(EntityFound != entitiesMap.end()){
            if(EntityFound->second->processMessage(m)==gg::ST_FALSE) return false;
        }

        ++componentsIterator;
    }
    return true;
}

IComponent* ObjectManager::getComponent(const gg::EComponentType &cType, const uint16_t &EntityID){
    //  Searchs on the map of that componentType if that EntityID exists
    std::map<uint16_t, IComponent*>::iterator found = TypeToComponentMap[cType].find(EntityID);

    //  If exists
    if(found != TypeToComponentMap[cType].end())
        return found->second;   // <- We return the pointer to it


    //  If not
    return nullptr; //  <- We return nullptr
}
