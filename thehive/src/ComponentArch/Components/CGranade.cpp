#include "CGranade.hpp"
#include "CTransform.hpp"

#include <Singleton.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>

#include <ComponentArch/InitStructs.hpp>

#include <EventSystem/EnumTriggerType.hpp>
#include "EventSystem/CTriggerSystem.hpp"
#include "ComponentArch/Message.hpp"

#include <EventSystem/TData.hpp>
#define VEL_FACTOR      200.f



CGranade::CGranade() {
    begin = std::chrono::high_resolution_clock::now();
}

CGranade::CGranade(const CGranade &orig){

}

CGranade::~CGranade() {

}
void CGranade::initComponent() {
    //  We wait for the M_UPDATE message
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::GRANADE, gg::M_UPDATE);
}


void CGranade::initializeComponentData(const void* data){
    if(data){
        InitCGrenade* cData = (InitCGrenade*)data;
        damage=cData->damage;
        radius=cData->radius;
        tipo=cData->tipo;
    }

    EventSystem = Singleton<CTriggerSystem>::Instance();
    engine = Singleton<GameEngine>::Instance();
    Manager = Singleton<ObjectManager>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

gg::EMessageStatus CGranade::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}

gg::EMessageStatus CGranade::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CGranade::MHandler_UPDATE(){
    if(cTransform){
        gg::Vector3f currentPosition = cTransform->getPosition();

        auto end = std::chrono::high_resolution_clock::now(); //Start de another chrono tu see the processor time now
        auto elapsedtime = end - begin; //The difference between both crhonos is the elapsed time
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedtime).count(); //Calculate the elapsed time as milisecons

        if(ms>1200){  //we control the time that we want the granade to move
            TData mes;
            mes.add(kDat_damage,damage);
            EventSystem->RegisterTriger(kTrig_Explosion,1,0,gg::Vector3f(currentPosition.X,currentPosition.Y,currentPosition.Z), radius, 50,false,mes);

            if(tipo==1||tipo==2){
                //std::cout << "entramos 2" << '\n';
                //if(tipo==1){

                //}else{

                //}
                //primera granada Z+
                float alejamiento=5;
                float ymas=10;
                float decrecimiento=0.75;
                gg::Vector3f vel(0,ymas,1);

                vel = gg::Normalice(vel);

                uint16_t holyBomb = Manager->createEntity();
                InitCGrenade CHolyBomb(damage,40,tipo+1);
                Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
                InitCRenderable_3D CRenderableHolyBomb("assets/Models/Cube.obj", moradoDeLos80);
                InitCTransform CTransformHolyBomb(           currentPosition.X,currentPosition.Y+alejamiento,currentPosition.Z+alejamiento, 0,0,0);
                InitCRigidBody CRigidBodyHolyBomb(false,"",  currentPosition.X,currentPosition.Y+alejamiento,currentPosition.Z+alejamiento, 3,3,3, 1, 0,0,0);
                Manager->addComponentToEntity(gg::TRANSFORM, holyBomb, &CTransformHolyBomb);
                Manager->addComponentToEntity(gg::RENDERABLE_3D, holyBomb, &CRenderableHolyBomb);
                Manager->addComponentToEntity(gg::RIGID_BODY, holyBomb, &CRigidBodyHolyBomb);
                Manager->addComponentToEntity(gg::GRANADE,holyBomb ,&CHolyBomb);

                CRigidBody* rb = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, holyBomb));
                vel*= VEL_FACTOR*decrecimiento;
                rb->applyCentralForce(vel);

                //segunda granada Z-
                vel=gg::Vector3f(0,ymas,-1);

                vel = gg::Normalice(vel);


                holyBomb = Manager->createEntity();
                CTransformHolyBomb=InitCTransform(           currentPosition.X,currentPosition.Y+alejamiento,currentPosition.Z-alejamiento, 0,0,0);
                CRigidBodyHolyBomb=InitCRigidBody(false,"",  currentPosition.X,currentPosition.Y+alejamiento,currentPosition.Z-alejamiento, 3,3,3, 1, 0,0,0);
                Manager->addComponentToEntity(gg::TRANSFORM, holyBomb, &CTransformHolyBomb);
                Manager->addComponentToEntity(gg::RENDERABLE_3D, holyBomb, &CRenderableHolyBomb);
                Manager->addComponentToEntity(gg::GRANADE,holyBomb ,&CHolyBomb);
                Manager->addComponentToEntity(gg::RIGID_BODY, holyBomb, &CRigidBodyHolyBomb);

                rb = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, holyBomb));
                vel*= VEL_FACTOR*decrecimiento;
                rb->applyCentralForce(vel);
                //tercera granada X+
                vel=gg::Vector3f(1,ymas,0);

                vel = gg::Normalice(vel);


                holyBomb = Manager->createEntity();
                CTransformHolyBomb=InitCTransform(           currentPosition.X+alejamiento,currentPosition.Y+alejamiento,currentPosition.Z, 0,0,0);
                CRigidBodyHolyBomb=InitCRigidBody(false,"",  currentPosition.X+alejamiento,currentPosition.Y+alejamiento,currentPosition.Z, 3,3,3, 1, 0,0,0);
                Manager->addComponentToEntity(gg::TRANSFORM, holyBomb, &CTransformHolyBomb);
                Manager->addComponentToEntity(gg::RENDERABLE_3D, holyBomb, &CRenderableHolyBomb);
                Manager->addComponentToEntity(gg::GRANADE,holyBomb ,&CHolyBomb);
                Manager->addComponentToEntity(gg::RIGID_BODY, holyBomb, &CRigidBodyHolyBomb);

                rb = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, holyBomb));
                vel*= VEL_FACTOR*decrecimiento;
                rb->applyCentralForce(vel);
                //cuarta granada X-
                vel=gg::Vector3f(-1,ymas,0);

                vel = gg::Normalice(vel);


                holyBomb = Manager->createEntity();
                CTransformHolyBomb=InitCTransform(           currentPosition.X-alejamiento,currentPosition.Y+alejamiento,currentPosition.Z, 0,0,0);
                CRigidBodyHolyBomb=InitCRigidBody(false,"",  currentPosition.X-alejamiento,currentPosition.Y+alejamiento,currentPosition.Z, 3,3,3, 1, 0,0,0);
                Manager->addComponentToEntity(gg::TRANSFORM, holyBomb, &CTransformHolyBomb);
                Manager->addComponentToEntity(gg::RENDERABLE_3D, holyBomb, &CRenderableHolyBomb);
                Manager->addComponentToEntity(gg::GRANADE,holyBomb ,&CHolyBomb);
                Manager->addComponentToEntity(gg::RIGID_BODY, holyBomb, &CRigidBodyHolyBomb);

                rb = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, holyBomb));
                vel*= VEL_FACTOR*decrecimiento;
                rb->applyCentralForce(vel);


            }


            Manager->removeEntity(getEntityID());
        }
    }

    return gg::ST_TRUE;
}
