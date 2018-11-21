#include "CAgent.hpp"
#include "ComponentArch/Components/CAgent.hpp"

#include <ComponentArch/InitStructs.hpp>
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <Singleton.hpp>
#include <list>
#include "ComponentArch/Message.hpp"


std::list <CAgent*>  CAgent::hola;

//std::list  <TriggerRecordStruct*>  hola;

void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}

unsigned long  CAgent::GetTriggerFlags(){
    return dwTriggerFlags;
}

gg::Vector3f CAgent::GetPosition(){
    return cTransform->getPosition();
}
void CAgent::updatetrig(){
    //std::cout << "entra updatetrig" <<nCAgentID<< '\n';

    std::list <TriggerRecordStruct*>::iterator it;
    it=holiiis.begin();
    TriggerRecordStruct* pTrig=NULL;
    for(unsigned long e=0; e<holiiis.size();++e)
    {
        pTrig=*it;
        float fDistance=gg::DIST(pTrig->vPos,GetPosition());//funcion calcular la distancia
        //std::cout << "radio" <<pTrig->fRadius<< '\n';
        //std::cout << "fDistance" <<fDistance<< '\n';
        float distancia=pTrig->fRadius;
        if(fDistance > (pTrig->fRadius)){
            //ejecutar ontriggerExit
            //std::cout << "OnTriggerExit ni idea" <<nCAgentID<< '\n';
            //std::cout << "peta" <<nCAgentID<< '\n';
            onTriggerExit(pTrig);

            //ejecutar ontriggerExit
            holiiis.erase(it);
        }else{
            //std::cout << "peta" <<nCAgentID<< '\n';
            onTriggerStay(pTrig);
        }
        it++;

    }

    //std::cout << "sale updatetrig" <<nCAgentID<< '\n';


}

bool CAgent::onTriggerEnter(TriggerRecordStruct* _pRec){
    ObjectManager* oManager = Singleton<ObjectManager>::Instance();
    //oManager->checkEvent(nCAgentID,mes);


    //std::cout << "OnTriggerExit ni idea" <<nCAgentID<< '\n';
    if(_pRec->eTriggerType & kTrig_Explosion){
        //std::cout << "OnTrigger explosion" <<nCAgentID<< '\n';
        //// std::cout << "agente" << nCAgentID << "con triger"<< GetTriggerFlags()<<'\n';
        //// std::cout << "usando handler despues" << nCAgentID<< '\n';
        //Message mes(gg::M_XPLOTATO,_pRec);
        if(oManager->getComponent(gg::RIGID_BODY,nCAgentID)){
            //std::cout << "core si" << '\n';
            static_cast<CRigidBody*>(oManager->getComponent(gg::RIGID_BODY,nCAgentID))->MHandler_XPLOTATO(_pRec);
            //std::cout << "core no" << '\n';
            return true;

        }


        //if(!oManager->checkEvent(nCAgentID,mes)) return false;

        //oManager->sendMessageToEntity(nCAgentID,mes);

    }
    else if(_pRec->eTriggerType & kTrig_Gunfire){
        //std::cout << "OnTriggerEnter arma" << nCAgentID<<'\n';
        if(oManager->getComponent(gg::GUN,nCAgentID))
            if(static_cast<CGun*>(oManager->getComponent(gg::GUN,nCAgentID))->getBullets())
                return false;

        if(oManager->getComponent(gg::GUN,nCAgentID))
            oManager->removeComponentFromEntity(gg::GUN,nCAgentID);

        // NO TIENE BALAS O ARMA
        InitCGun CGunHero(10,1,50);
        oManager->addComponentToEntity(gg::GUN, nCAgentID, &CGunHero);
    }
return true;

}
void CAgent::onTriggerStay(TriggerRecordStruct* _pRec){
    //std::cout << "OnTriggerStay  entra" <<nCAgentID<< '\n';
    //std::cout << "OnTriggerExit ni idea" <<nCAgentID<< '\n';
    ObjectManager* oManager = Singleton<ObjectManager>::Instance();

    if(_pRec->eTriggerType & kTrig_Explosion){
        //// std::cout << "agente" << nCAgentID << "con triger"<< GetTriggerFlags()<<'\n';
        //// std::cout << "usando handler despues" << nCAgentID<< '\n';
        if(oManager->getComponent(gg::RIGID_BODY,nCAgentID)){
            static_cast<CRigidBody*>(oManager->getComponent(gg::RIGID_BODY,nCAgentID))->MHandler_XPLOTATO(_pRec);
            return;
        }
    }
    //std::cout << "OnTriggerStay  sale" <<nCAgentID<< '\n';



}
void CAgent::onTriggerExit(TriggerRecordStruct* _pRec){
    //std::cout << "OnTriggerExit ni idea" <<nCAgentID<< '\n';


}
void CAgent::deletetrig(TriggerRecordStruct* _pRec){

    std::list <CAgent*>::iterator it2 ;
    std::list <TriggerRecordStruct*>::iterator it;

    it2=CAgent::hola.begin();
    CAgent* pAgent=NULL;
    for(unsigned long i=0; i<CAgent::hola.size();++i)
    {
        pAgent=*it2;
        //std::cout << "entra delete" <<pAgent->nCAgentID<< '\n';

        it=pAgent->holiiis.begin();
        TriggerRecordStruct* pTrig=NULL;
        for(unsigned long e=0; e<pAgent->holiiis.size();++e)
        {
            pTrig=*it;
            if(pTrig==_pRec){

                //std::cout << "OnTriggerExit ni idea" << '\n';
                pAgent->onTriggerExit(_pRec);
                pAgent->holiiis.erase(it);
                break;
            }
            it++;

        }


        it2++;
    }

}
bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){
    //std::cout << "numero de trigs "<< holiiis.size() << '\n';

    // // std::cout << "Id agente:"<<nCAgentID << " ha entrado"<<std::endl;
    std::list <TriggerRecordStruct*>::iterator it;
    it=holiiis.begin();
    TriggerRecordStruct* pTrig=NULL;
    //std::cout << "entra handler" <<nCAgentID<< '\n';
    for(unsigned long i=0; i<holiiis.size();++i)
    {
        pTrig=*it;
        if(pTrig==_pRec){
            return false;
        }
        it++;

    }

    //MessageXplotato* exp =(MessageXplotato*) _pRec->data;
    //std::cout << "hanlder" << '\n';
    //std::cout << exp->damage << '\n';

    bool res=onTriggerEnter(_pRec);
    if(res)
    holiiis.push_back(_pRec);
    //posible codigo init

    //...
    //update
    //update(_pRec);
    //holiiis;
    return res;
}

//CAgent::CAgent(unsigned long _dwTriggerFlags,gg::Vector3f _vPos){
//    nCAgentID=id2;
//    id2++;
//    dwTriggerFlags=_dwTriggerFlags;
//    nDeltaTime=0;
//    vPos=_vPos;
//}
void CAgent::addAgent(CAgent* agente){
    hola.push_back(agente);
}
void CAgent::removeAgent(std::list<CAgent*>::iterator ite){
    hola.erase(ite);
}
CAgent::CAgent()
:cTransform(nullptr)
{

}

CAgent::~CAgent() {
    std::list <CAgent*>::iterator it2 ;
    it2=CAgent::hola.begin();
    CAgent* pAgent=NULL;
    for(unsigned long i=0; i<CAgent::hola.size();++i)
    {
        pAgent=*it2;
        if (pAgent->nCAgentID==nCAgentID) {
            removeAgent(it2);
            break;
        }
        it2++;
    }
}

void CAgent::initComponent() {
    //  Si necesitas punteros a otras funciones es importante suscribir esta componente al mensaje M_SETPTRS
    //  Este mensaje se llamará para recalular los punteros cuando se borre una componente de un objeto


}

void CAgent::initializeComponentData(const void* data){
    if(data){
        InitCAgent* cdata=(InitCAgent*)data;
            nCAgentID=getEntityID();
            dwTriggerFlags=cdata->flags;
            nDeltaTime=0;
            addAgent(this);
            //vPos=cTransform->getPosition;
        //CAgent(data->dwTriggerFlags,gg::Vector3f _vPos(cTransform->X,cTransform->Y,cTransform->Z));
        // Si le pasamos cosas, convertimos el void* a la estructura inicializadora para acceder a los elementos
    }
    engine = Singleton<GameEngine>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

//void CAgent::update(){
//    std::list <TriggerRecordStruct*>::iterator it;
//    it=holiiis.begin();
//    TriggerRecordStruct* pTrig=NULL;
//    for(unsigned long i=0; i<holiiis.size();++i)
//    {
//        pTrig=*it;
//        onTriggerStay(pTrig);
//        it++;
//
//    }
//
//
//
//}
gg::EMessageStatus CAgent::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CAgent::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CAgent::MHandler_UPDATE(){
    // UPDATE
    //setposition
    //CAgent(cTransform->getPosition);


    return gg::ST_TRUE;

}
