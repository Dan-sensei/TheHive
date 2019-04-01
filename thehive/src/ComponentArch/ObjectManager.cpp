#include "ObjectManager.hpp"
//#include "Enum.hpp"
#include <GameAI/Pathfinding.hpp>
#include <Singleton.hpp>
//#include <iostream>
#include "Bullet/ggDynWorld.hpp"
#include <ComponentArch/Components/CRigidBody.hpp>
                     //  2^16
#define MAX_ENTITIES 65536

ObjectManager::ObjectManager() {
    nextAvailableEntityID.push(1);//

    //  Defines wich kind of messages will receive each type of component
    //  We just insert in the array of vectors, the component type in the messageTYpe array position
    //  Dani deja el ingle
    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::VIDA);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::VIDA);


    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::M_EVENT_ACTION].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::M_INTERPOLATE_PRESAVE].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::M_INTERPOLATE_POSTSAVE].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::M_INTERPOLATE].push_back(gg::RIGID_BODY);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::RIGID_BODY);


    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::RENDERABLE_3D);
    MessageToListeningComponents[gg::UPDATE].push_back(gg::RENDERABLE_3D);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::DYNAMICMODEL);
    MessageToListeningComponents[gg::UPDATE].push_back(gg::DYNAMICMODEL);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::PLAYERCONTROLLER);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::PLAYERCONTROLLER);
    MessageToListeningComponents[gg::UPDATE].push_back(gg::PLAYERCONTROLLER);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::NAVMESHAGENT);
    MessageToListeningComponents[gg::UPDATE].push_back(gg::NAVMESHAGENT);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::NAVMESHAGENT);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::HAB);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::HAB);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::GUN);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::GUN);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::GRANADE);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::GRANADE);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::CLOCK);
    MessageToListeningComponents[gg::UPDATE].push_back(gg::CLOCK);


    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::FLOCK);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::FLOCK);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::AIENEM);
    MessageToListeningComponents[gg::FIXED_UPDATE].push_back(gg::AIENEM);
    MessageToListeningComponents[gg::UPDATE].push_back(gg::AIENEM);

    MessageToListeningComponents[gg::M_SETPTRS].push_back(gg::AGENT);

}


//  ---
//  Iterates over every component desallocating memory
//========================================================================
ObjectManager::~ObjectManager() {

}

void ObjectManager::clin(){
    uint8_t i = gg::NUM_COMPONENTS;
    while (i--){
        std::map<uint16_t, IComponent*>::iterator it=TypeToComponentMap[i].begin();

        while(it!=TypeToComponentMap[i].end()){
            //it->second->~IComponent();
            //memory.deallocate(it->second);
            delete it->second;
            ++it;
        };
        TypeToComponentMap[i].clear();
    }

    Singleton<Pathfinding>::Instance()->clear();    //  Provisional
}

int ObjectManager::returnIDFromRigid(btRigidBody* esto){
    //compr esto
    //const gg::EComponentType &cType
    ////std::cout << "hecho" << '\n';
    std::map<uint16_t, IComponent*>::iterator found = TypeToComponentMap[gg::RIGID_BODY].begin();
    while(found!=TypeToComponentMap[gg::RIGID_BODY].end()){
        ////std::cout << "entra" << '\n';
        CRigidBody* cRigidBody = static_cast<CRigidBody*>(found->second);
        if(esto!=nullptr&&cRigidBody->getBody()!=nullptr&&cRigidBody->getBody()==esto){
            ////std::cout << "si joder" << '\n';
            ////std::cout << found->first << '\n';
            return found->first;
        }
        found++;
        ////std::cout << "sale" << '\n';
        //found->second;
    }
    ////std::cout << "sale fin" << '\n';
return 0;
    //  If exists
    //if(found != TypeToComponentMap[cType].end())
    //    return found->second;   // <- We return the pointer to it


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

    delete foundComponent->second;
    TypeToComponentMap[type].erase(foundComponent);
    ////std::cout << "FLOCKING SIZE " << TypeToComponentMap[gg::FLOCK].size() << '\n';
    if(Erase) return;

    Message recalculatePointersToAnotherComponents(gg::M_SETPTRS);
    sendMessageToEntity(EntityID, recalculatePointersToAnotherComponents);
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
    int i=0;
    while(componentsIterator != MessageToListeningComponents[m.mType].end()){
        i++;

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
    CallFunctionOfComponentes(gg::UPDATE, &IComponent::Update);
}

void ObjectManager::FixedUpdateAll(){
    CallFunctionOfComponentes(gg::FIXED_UPDATE, &IComponent::FixedUpdate);
}

void ObjectManager::CallFunctionOfComponentes(gg::MessageType mType, void (IComponent::*TypeOfUpdate)()){
    std::vector<gg::EComponentType>::iterator componentsIterator = MessageToListeningComponents[mType].begin();
    std::map<uint16_t, IComponent*>::iterator entitiesIterator;

    while(componentsIterator != MessageToListeningComponents[mType].end()){
        entitiesIterator = TypeToComponentMap[*componentsIterator].begin();
        while(entitiesIterator != TypeToComponentMap[*componentsIterator].end()) {
            auto current = entitiesIterator;
            ++entitiesIterator;
            (current->second->*TypeOfUpdate)();
        }

        ++componentsIterator;
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

IComponent* ObjectManager::getComponent(const gg::EComponentType &cType, const uint16_t &EntityID){
    //  Searchs on the map of that componentType if that EntityID exists
    std::map<uint16_t, IComponent*>::iterator found = TypeToComponentMap[cType].find(EntityID);

    //  If exists
    if(found != TypeToComponentMap[cType].end())
        return found->second;   // <- We return the pointer to it

    //  If not
    return nullptr; //  <- We return nullptr
}

uint16_t ObjectManager::getHeroID(){
    return HERO_ID;
}

void ObjectManager::setHeroID(uint16_t _id){
    HERO_ID = _id;
}
