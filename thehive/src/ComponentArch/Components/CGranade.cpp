#include "CGranade.hpp"


#include "ComponentArch/Message.hpp"

#include <EventSystem/TData.hpp>
#define VEL_FACTOR      200.f
#include "Factory.hpp"


CGranade::CGranade(float _damage,float _radius,float _tipo)
:damage(_damage), radius(_radius), tipo(_tipo)
{
    begin = std::chrono::high_resolution_clock::now();
}

CGranade::~CGranade() {

}
void CGranade::initComponent() {
    //  We wait for the M_UPDATE message
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::GRANADE, gg::M_UPDATE);
}


void CGranade::Init(){

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
            //EventSystem->PulsoTrigger(kTrig_Explosion,0,gg::Vector3f(currentPosition.X,currentPosition.Y,currentPosition.Z),50,mes);
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
                vel*= VEL_FACTOR*decrecimiento;
                Singleton<Factory>::Instance()->createHolyBomb(
                    damage,40,tipo+1,
                    gg::Vector3f(currentPosition.X,currentPosition.Y+alejamiento,currentPosition.Z+alejamiento),
                    vel
                );

                //segunda granada Z-
                vel=gg::Vector3f(0,ymas,-1);
                vel = gg::Normalice(vel);
                vel*= VEL_FACTOR*decrecimiento;
                Singleton<Factory>::Instance()->createHolyBomb(
                    damage,40,tipo+1,
                    gg::Vector3f(currentPosition.X,currentPosition.Y+alejamiento,currentPosition.Z-alejamiento),
                    vel
                );

                //tercera granada X+
                vel=gg::Vector3f(1,ymas,0);
                vel = gg::Normalice(vel);
                vel*= VEL_FACTOR*decrecimiento;
                Singleton<Factory>::Instance()->createHolyBomb(
                    damage,40,tipo+1,
                    gg::Vector3f(currentPosition.X+alejamiento,currentPosition.Y+alejamiento,currentPosition.Z),
                    vel
                );

                //cuarta granada X-
                vel=gg::Vector3f(-1,ymas,0);
                vel = gg::Normalice(vel);
                vel*= VEL_FACTOR*decrecimiento;
                Singleton<Factory>::Instance()->createHolyBomb(
                    damage,40,tipo+1,
                    gg::Vector3f(currentPosition.X-alejamiento,currentPosition.Y+alejamiento,currentPosition.Z),
                    vel
                );
            }


            Manager->removeEntity(getEntityID());
        }
    }

    return gg::ST_TRUE;
}
