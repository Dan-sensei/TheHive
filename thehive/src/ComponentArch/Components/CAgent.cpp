#include "CAgent.hpp"
#include "ComponentArch/Components/CAgent.hpp"

#include <ComponentArch/InitStructs.hpp>
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <Singleton.hpp>
#include <list>


std::list <CAgent*>  CAgent::hola;


void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}

unsigned long  CAgent::GetTriggerFlags(){
    return dwTriggerFlags;
}

gg::Vector3f CAgent::GetPosition(){
    return cTransform->getPosition();
}

bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){
    // std::cout << "Id agente:"<<nCAgentID << " ha entrado"<<std::endl;
    ObjectManager* oManager = Singleton<ObjectManager>::Instance();

    if(_pRec->eTriggerType & kTrig_Explosion){
        Message mes(gg::M_XPLOTATO,_pRec);
        oManager->sendMessageToEntity(nCAgentID,mes);





    }







    return true;
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
