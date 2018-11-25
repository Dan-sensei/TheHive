#include "CAgent.hpp"
#include "ComponentArch/Components/CAgent.hpp"


#include <list>
#include "ComponentArch/Message.hpp"
#include "CGun.hpp"
#include "CRigidBody.hpp"
#include "CTransform.hpp"



std::list <CAgent*>  CAgent::hola;

CAgent::CAgent(const unsigned long &_flags)
:cTransform(nullptr), Engine(nullptr)
{
    dwTriggerFlags = _flags;
    nDeltaTime=0;
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

void CAgent::Init(){
    Engine = Singleton<GameEngine>::Instance();

    nCAgentID=getEntityID();
    addAgent(this);

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

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
        //Message mes(gg::M_XPLOTATO,_pRec);
        if(oManager->getComponent(gg::RIGID_BODY,nCAgentID)){
            //std::cout << "core si" << '\n';
            static_cast<CRigidBody*>(oManager->getComponent(gg::RIGID_BODY,nCAgentID))->MHandler_XPLOTATO(_pRec);
            //std::cout << "core no" << '\n';
            return true;

        }
    }
    else if(_pRec->eTriggerType & kTrig_Gunfire){
        float   dmg, cdc, relDT, rng;
        int     tb;
        CGun *gun = static_cast<CGun*>(oManager->getComponent(gg::GUN,nCAgentID));

        if(gun){
            if(Singleton<GameEngine>::Instance()->key(gg::GG_F) && nCAgentID == 1){
                // Puedo recoger el arma del suelo
                int _wtype_actual = gun->getType();
                int _wtype_floor = static_cast<int>(_pRec->data.find(kDat_WeaponType));
                gg::cout("PICKING: TYPE " + std::to_string(_wtype_floor) + " WEAPON");

                getWeaponInformation(dmg,cdc,relDT,rng,tb,_wtype_floor);

                // Elimino el arma que tiene la entidad
                oManager->removeComponentFromEntity(gg::GUN,nCAgentID);

                // Le anyado la nueva
                CGun* Gun = new CGun(dmg,cdc,tb,relDT,rng,_wtype_floor);
                oManager->addComponentToEntity(Gun, gg::GUN, nCAgentID);

                gg::Vector3f pos(
                    static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().X,
                    static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().Y+20,
                    static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().Z
                );
                Singleton<Factory>::Instance()->createCollectableWeapon(pos,_wtype_actual);

                // Destruyo el arma del suelo y su evento
                int id = _pRec->data.find(kDat_EntId);
                oManager->removeEntity(id);
                _pRec->nExpirationTime = 50;

                return true;
            }
            return false;
        }

        // NO TIENE ARMA
        getWeaponInformation(dmg,cdc,relDT,rng,tb,static_cast<int>(_pRec->data.find(kDat_WeaponType)));

        // Creo y anyado un arma a la entidad
        CGun* Gun = new CGun(dmg,cdc,tb,relDT,rng,static_cast<int>(_pRec->data.find(kDat_WeaponType)));
        oManager->addComponentToEntity(Gun, gg::GUN, nCAgentID);

        // Destruyo el arma del suelo y su evento
        int id = _pRec->data.find(kDat_EntId);
        oManager->removeEntity(id);
        _pRec->nExpirationTime = 50;
    }
    else if(_pRec->eTriggerType & kTrig_EnemyNear){
        //CAIEnem->enemyseen();
    }
    return true;
}

void CAgent::getWeaponInformation(float &dmg, float &cdc, float &relDT, float &rng, int &tb, int _type){
    switch (_type){
        case 0:
            // Rifle
            dmg = 70;
            cdc = 3;
            tb  = 30;
            relDT = 1;
            rng = 0.7;
            break;
        case 1:
            // Escopeta
            dmg = 80;
            cdc = 1;
            tb  = 10;
            relDT = 1.5;
            rng = 0.4;
            break;
    }

    gg::cout(" --- GUN PICKED --- ");
    gg::cout(" - - DMG= "       + std::to_string(dmg));
    gg::cout(" - - CADENCE= "   + std::to_string(cdc));
    gg::cout(" - - BULLETS= "   + std::to_string(tb));
    gg::cout(" - - DT= "        + std::to_string(relDT));
    gg::cout(" - - RANGE= "     + std::to_string(rng));
    gg::cout(" ------------------ ");
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
