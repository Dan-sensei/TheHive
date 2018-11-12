#include "ObjectManager.hpp"
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

    ComponentConstructorVector[0]= &ObjectManager::createTransformComponent;
    ComponentConstructorVector[1]= &ObjectManager::createKeyboardComponent;
    ComponentConstructorVector[2]= &ObjectManager::createRenderable_3DComponent;
    ComponentConstructorVector[3]= &ObjectManager::createCameraComponent;
    ComponentConstructorVector[4]= &ObjectManager::createAgentComponent;

    //ComponentConstructorVector[3]= &ObjectManager::createHealthComponent;
    //ComponentConstructorVector[4]= &ObjectManager::createRespectComponent;
}


//  ---
//  Iterates over every component desallocating memory
//========================================================================
ObjectManager::~ObjectManager() {

}

void ObjectManager::clin(){
    std::cout << "Destruyendo todos los componentes..." << '\n';
    uint8_t i = gg::NUM_COMPONENTS;
    while (i--){
        std::map<uint16_t, IComponent*>::iterator it=TypeToComponentMap[i].begin();

        while(it!=TypeToComponentMap[i].end()){
            std::cout << "  -Eliminando componente " << (int)i << " de entidad " << it->first << '\n';
            //it->second->~IComponent();
            //memory.deallocate(it->second);
            delete it->second;
            ++it;
        };
    }
}

//  ---
//  Calls statics functions of every component to initialize them
//========================================================================
void ObjectManager::initObjectManager() {
    CTransform::initComponent();
    CKeyboard::initComponent();
    CRenderable_3D::initComponent();
    CCamera::initComponent();
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
    while (i--) removeComponentFromEntity(static_cast<gg::EComponentType>(i), targetID);
}


void ObjectManager::addComponentToEntity(gg::EComponentType type, uint16_t EntityID, const void* initData) {
    IComponent* newComponent;

    //  Depending on the component type we wanna create, we call a different function
    //  in the constructor vector of functions
    pConstructor constructor = ComponentConstructorVector[type];

    if(constructor != nullptr)
        newComponent = (this->*constructor)();

    //std::cout << "  -Adding componente " << type << " to entity " << EntityID << '\n';

    //  We set the entityID to that component
    newComponent->setEntityID(EntityID);

    //  And insert in the map, the ID with is assigned component
    TypeToComponentMap[type].insert(std::make_pair(EntityID, newComponent));

    //  We pass the initData for the component, we call the method
    //  of the component wich uses this data
    newComponent->initializeComponentData(initData);
}

void ObjectManager::removeComponentFromEntity(gg::EComponentType type, uint16_t EntityID){
    auto foundComponent = TypeToComponentMap[type].find(EntityID);

    if(foundComponent == TypeToComponentMap[type].end())
        return;

    delete foundComponent->second;
    TypeToComponentMap[type].erase(foundComponent);

    Message recalculatePointersToAnotherComponents(gg::M_SETPTRS);
    sendMessageToEntity(EntityID, recalculatePointersToAnotherComponents);
}

void ObjectManager::subscribeComponentTypeToMessageType(const gg::EComponentType &cType, const gg::MessageType &mType) {
    //  We just insert in the array of vectors, the component type in the messageTYpe array position
    MessageToListeningComponents[mType].push_back(cType);
}


void ObjectManager::sendMessageToAllEntities(const Message &m){
    // We iterate over every component in the map that expects to receive that kind of message

    std::vector<gg::EComponentType>::iterator componentsIterator = MessageToListeningComponents[m.mType].begin();
    std::map<uint16_t, IComponent*>::iterator entitiesIterator;

    // First we search for a component type that expects that message type
    while(componentsIterator != MessageToListeningComponents[m.mType].end()){

        //  Found one!
        std::map<uint16_t, IComponent*>::iterator entitiesEnd = TypeToComponentMap[*componentsIterator].end();
        entitiesIterator = TypeToComponentMap[*componentsIterator].begin();

        //  Now we iterate over every entity that contains that component type
        while(entitiesIterator != entitiesEnd) {
            //  We process the message
            entitiesIterator->second->processMessage(m);
            ++entitiesIterator;
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

//  ---
//  CONSTRUCTORS
//===========================================================================================================

IComponent* ObjectManager::createTransformComponent         ()   {
    return new CTransform;
}
IComponent* ObjectManager::createKeyboardComponent          ()   {
    return new CKeyboard;
}
IComponent* ObjectManager::createRenderable_3DComponent     ()   {
    return new CRenderable_3D;
}
IComponent* ObjectManager::createCameraComponent            ()   {
    return new CCamera;
}
IComponent* ObjectManager::createAgentComponent            ()   {
    return new CAgent;
}

//IComponent* ObjectManager::createColliderComponent     ();
//IComponent* ObjectManager::createHealthComponent       ();
//IComponent* ObjectManager::createRespectComponent      ();
