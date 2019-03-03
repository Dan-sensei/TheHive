#include "CAgent.hpp"
#include "ComponentArch/Components/CAgent.hpp"


#include <list>
#include "ComponentArch/Message.hpp"
#include "CGun.hpp"
#include "CRigidBody.hpp"
#include "CTransform.hpp"
#include "CAIEnem.hpp"


std::list <CAgent*>  CAgent::AgentList;

CAgent::CAgent(const unsigned long &_flags)
:cTransform(nullptr), Engine(nullptr)
{
    dwTriggerFlags = _flags;
    nDeltaTime=0;
    oManager = Singleton<ObjectManager>::Instance();
}

CAgent::~CAgent() {
    std::list <CAgent*>::iterator it2 ;
    it2=CAgent::AgentList.begin();
    CAgent* pAgent=NULL;
    for(unsigned long i=0; i<CAgent::AgentList.size();++i)
    {
        pAgent=*it2;
        if (pAgent->nCAgentID==nCAgentID) {
            removeAgent(it2);
            break;
        }
        it2++;
    }
}


void CAgent::Init(){
    Engine = Singleton<TMotorTAG>::Instance();

    nCAgentID=getEntityID();
    addAgent(this);

    // Mapa a funcion de los trigger ON ENTER
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_none,         &CAgent::ENTER_func_kTrig_none));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_Explosion,    &CAgent::ENTER_func_kTrig_Explosion));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_EnemyNear,    &CAgent::ENTER_func_kTrig_EnemyNear));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_Gunfire,      &CAgent::ENTER_func_kTrig_Gunfire));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_Shoot,        &CAgent::ENTER_func_kTrig_Shoot));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_Touchable,    &CAgent::ENTER_func_kTrig_Touchable));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_Senyuelo,     &CAgent::ENTER_func_kTrig_Senyuelo));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_Aturd,        &CAgent::ENTER_func_kTrig_Aturd));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_Pickable,     &CAgent::ENTER_func_kTrig_Pickable));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_DeadAlien,    &CAgent::ENTER_func_kTrig_DeadAlien));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_ExpansiveWave,&CAgent::ENTER_func_kTrig_ExpansiveWave));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_ExpansiveForce,&CAgent::ENTER_func_kTrig_ExpansiveForce));
    // mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_Plantilla,    &CAgent::ENTER_func_kTrig_Plantilla));

    // Mapa a funcion de los trigger ON STAY
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_none,          &CAgent::STAY_func_kTrig_none));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_Explosion,     &CAgent::STAY_func_kTrig_Explosion));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_EnemyNear,     &CAgent::STAY_func_kTrig_EnemyNear));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_Gunfire,       &CAgent::STAY_func_kTrig_Gunfire));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_Shoot,         &CAgent::STAY_func_kTrig_Shoot));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_Touchable,     &CAgent::STAY_func_kTrig_Touchable));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_Senyuelo,      &CAgent::STAY_func_kTrig_Senyuelo));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_Aturd,         &CAgent::STAY_func_kTrig_Aturd));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_Pickable,      &CAgent::STAY_func_kTrig_Pickable));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_DeadAlien,     &CAgent::STAY_func_kTrig_DeadAlien));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_ExpansiveWave, &CAgent::STAY_func_kTrig_ExpansiveWave));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_ExpansiveForce, &CAgent::STAY_func_kTrig_ExpansiveForce));
    // mapFuncOnTriggerStay.insert(std::make_pair(kTrig_Plantilla,    &CAgent::STAY_func_kTrig_Plantilla));

    // Mapa a funcion de los trigger ON STAY
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_none,          &CAgent::EXIT_func_kTrig_none));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Explosion,     &CAgent::EXIT_func_kTrig_Explosion));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_EnemyNear,     &CAgent::EXIT_func_kTrig_EnemyNear));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Gunfire,       &CAgent::EXIT_func_kTrig_Gunfire));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Shoot,         &CAgent::EXIT_func_kTrig_Shoot));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Touchable,     &CAgent::EXIT_func_kTrig_Touchable));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Senyuelo,      &CAgent::EXIT_func_kTrig_Senyuelo));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Aturd,         &CAgent::EXIT_func_kTrig_Aturd));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Pickable,      &CAgent::EXIT_func_kTrig_Pickable));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_DeadAlien,     &CAgent::EXIT_func_kTrig_DeadAlien));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_ExpansiveWave, &CAgent::EXIT_func_kTrig_ExpansiveWave));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_ExpansiveForce, &CAgent::EXIT_func_kTrig_ExpansiveForce));
    // mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Plantilla,    &CAgent::EXIT_func_kTrig_Plantilla));

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

//std::list  <TriggerRecordStruct*>  AgentList;

void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}

unsigned long  CAgent::GetTriggerFlags(){
    return dwTriggerFlags;
}

gg::Vector3f CAgent::GetPosition(){
    return cTransform->getPosition();
}

void CAgent::updatetrig(){
    TriggerRecordStruct *pTrig;
    float fDistance;
    gg::Vector3f TF_POS = cTransform->getPosition();

    std::vector<std::list<TriggerRecordStruct*>::iterator> vec;
    std::vector<std::list<TriggerRecordStruct*>::iterator>::iterator it2 = vec.begin();

    std::list<TriggerRecordStruct*>::iterator it = TriggerList.begin();
    while(it != TriggerList.end()){
        pTrig = *it;
        fDistance = gg::DIST(pTrig->vPos,TF_POS );

        if(fDistance > pTrig->fRadius){
            onTriggerExit(pTrig);
            // TriggerList.erase(it);
            vec.push_back(it);
        }else{
            onTriggerStay(pTrig);
        }
        it++;
    }

    for(int i=0 ; i<vec.size() ; i++){
        TriggerList.erase(vec[i]);
    }
}

bool CAgent::onTriggerEnter(TriggerRecordStruct* _pRec){
    (this->*mapFuncOnTriggerEnter[_pRec->eTriggerType])(_pRec);
    return true;
}
void CAgent::ENTER_func_kTrig_none          (TriggerRecordStruct *_pRec){}
void CAgent::ENTER_func_kTrig_Touchable     (TriggerRecordStruct *_pRec){}
void CAgent::ENTER_func_kTrig_Pickable      (TriggerRecordStruct *_pRec){}
void CAgent::ENTER_func_kTrig_Gunfire       (TriggerRecordStruct *_pRec){}

void CAgent::ENTER_func_kTrig_ExpansiveWave (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_ExpansiveWave){
        //gg::cout(" --- HACE PUM --- ");
    }
}
void CAgent::ENTER_func_kTrig_ExpansiveForce (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_ExpansiveForce){
        if(oManager->getComponent(gg::RIGID_BODY,nCAgentID)){
            static_cast<CRigidBody*>(oManager->getComponent(gg::RIGID_BODY,nCAgentID))->MHandler_XPLOTATO(_pRec);
        }
    }
}

void CAgent::ENTER_func_kTrig_DeadAlien   (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_DeadAlien){
        CAIEnem *AI = static_cast<CAIEnem*>(oManager->getComponent(gg::AIENEM,getEntityID()));
        if(AI && !AI->getCloserAllyIsDead()){
            AI->setCloserAllyIsDead(true);      // Por ahora este no hace falta
            AI->upgradeRage();
        }
    }
}

void CAgent::ENTER_func_kTrig_Explosion   (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_Explosion){
        if(oManager->getComponent(gg::RIGID_BODY,nCAgentID)){
            static_cast<CRigidBody*>(oManager->getComponent(gg::RIGID_BODY,nCAgentID))->MHandler_XPLOTATO(_pRec);
            CVida *health = static_cast<CVida*>(oManager->getComponent(gg::VIDA,nCAgentID));
            if(health){
                float damage = _pRec->data.find(kDat_Damage)/1000;
                // //gg::cout("BOOOOOOOOOOM! -> ["+std::to_string(damage)+"]", gg::Color(0, 0, 255, 1));
                health->quitarvida(damage);
            }
        }
    }
}

void CAgent::ENTER_func_kTrig_EnemyNear   (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_EnemyNear){
        if(oManager->getComponent(gg::AIENEM,nCAgentID)){
            static_cast<CAIEnem*>(oManager->getComponent(gg::AIENEM,nCAgentID))->MHandler_NEAR(_pRec);
        }
    }
}


void CAgent::ENTER_func_kTrig_Shoot       (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_Shoot){
        CVida *health = static_cast<CVida*>(oManager->getComponent(gg::VIDA,nCAgentID));
        if(health){
            float damage = _pRec->data.find(kDat_Damage);
            //gg::cout("PUM! -> ["+std::to_string(damage)+"]", gg::Color(0, 0, 255, 1));

            health->quitarvida(damage);

            CAIEnem *AI = static_cast<CAIEnem*>(oManager->getComponent(gg::AIENEM,nCAgentID));
            if(AI){
                AI->setPlayerIsAttacking(true);
            }
        }
    }
}

void CAgent::ENTER_func_kTrig_Senyuelo    (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_Senyuelo){
        if(oManager->getComponent(gg::AIENEM,nCAgentID)){
            static_cast<CAIEnem*>(oManager->getComponent(gg::AIENEM,nCAgentID))->MHandler_SENYUELO(_pRec);
        }
    }
}

void CAgent::ENTER_func_kTrig_Aturd       (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_Aturd){
        if(oManager->getComponent(gg::AIENEM,nCAgentID)){
            static_cast<CAIEnem*>(oManager->getComponent(gg::AIENEM,nCAgentID))->MHandler_ATURD();
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAgent::onTriggerStay(TriggerRecordStruct* _pRec){
    (this->*mapFuncOnTriggerStay[_pRec->eTriggerType])(_pRec);
}

void CAgent::STAY_func_kTrig_none           (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_EnemyNear      (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_Shoot          (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_Senyuelo       (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_Aturd          (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_DeadAlien      (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_ExpansiveWave  (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_ExpansiveForce  (TriggerRecordStruct *_pRec){}

void CAgent::STAY_func_kTrig_Gunfire     (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_Gunfire){
        float   dmg, cdc, relDT, rng;
        int     tb;
        CGun *gun = static_cast<CGun*>(oManager->getComponent(gg::GUN,nCAgentID));
        CPlayerController *cpc = static_cast<CPlayerController*>(oManager->getComponent(gg::PLAYERCONTROLLER,nCAgentID));

        if(!cpc->canPickWeapon()){
            return;
        }

        if(gun){
            if(!cpc->heroHasSecondWeapon()){
                // Puedo recoger el arma del suelo
                int _wtype_floor = static_cast<int>(_pRec->data.find(kDat_WeaponType));
                //gg::cout("PICKING: TYPE " + std::to_string(_wtype_floor) + " WEAPON");

                getWeaponInformation(dmg,cdc,relDT,rng,tb,_wtype_floor);

                // Le anyado la nueva
                CGun* Gun = new CGun(dmg,cdc,tb,relDT,rng,_wtype_floor);
                cpc->setSecondWeapon(Gun);
            }
            else{
                // Puedo recoger el arma del suelo
                int _wtype_actual = gun->getType();
                int _wtype_floor = static_cast<int>(_pRec->data.find(kDat_WeaponType));
                //gg::cout("PICKING: TYPE " + std::to_string(_wtype_floor) + " WEAPON");

                getWeaponInformation(dmg,cdc,relDT,rng,tb,_wtype_floor);

                // Elimino el arma que tiene la entidad
                oManager->removeComponentFromEntity(gg::GUN,nCAgentID);

                // Le anyado la nueva
                CGun* Gun = new CGun(dmg,cdc,tb,relDT,rng,_wtype_floor);
                oManager->addComponentToEntity(Gun, gg::GUN, nCAgentID);

                gg::Vector3f pos(
                    static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().X,
                    static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().Y+5,
                    static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().Z
                );
                uint16_t weapon = Singleton<Factory>::Instance()->createCollectableWeapon(pos,_wtype_actual);

                gg::Vector3f from = static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition();
                gg::Vector3f to = Singleton<ggDynWorld>::Instance()->getRaycastVector();
                gg::Vector3f vec = (to-from)*30;
                static_cast<CRigidBody*>(oManager->getComponent(gg::RIGID_BODY,weapon))->applyCentralForce(vec);
            }

            // Destruyo el arma del suelo y su evento
            int id = _pRec->data.find(kDat_EntId);
            oManager->removeEntity(id);
            _pRec->nExpirationTime = 50;
        }
        else{
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
    }
}

void CAgent::STAY_func_kTrig_Touchable   (TriggerRecordStruct *_pRec){
    if((_pRec->eTriggerType & kTrig_Touchable) && Engine->key(gg::GG_E)){
        uint16_t item = _pRec->data.find(kDat_PickableItemId);
        CPlayerController *cpc = static_cast<CPlayerController*>(oManager->getComponent(gg::PLAYERCONTROLLER,nCAgentID));
        if(item && !cpc->hasItem(item)){
            // El heroe no ha cogido el item en concreto para realizar la accion
            //gg::cout("You shall not PASS!!!");
            return;
        }
        // Usa y destruye el item
        cpc->useItem(item);

        bool isDone = _pRec->data.find(kDat_Done);
        if(!isDone){
            uint16_t eIdObj     = _pRec->data.find(kDat_EntId);
            int actionId        = _pRec->data.find(kDat_Action);
            //gg::cout("ID: "+std::to_string(eIdObj)+" || ACTION: "+std::to_string(actionId));

            // Esta done la accion del jugador
            _pRec->data.clearData(kDat_Done);
            _pRec->data.add(kDat_Done,true);

            // Ahora le toca a la entidad hacer la accion en concreto
            Message mes(gg::M_EVENT_ACTION,&actionId);
            oManager->sendMessageToEntity(eIdObj,mes);
        }
    }
}

void CAgent::STAY_func_kTrig_Pickable    (TriggerRecordStruct *_pRec){
    if((_pRec->eTriggerType & kTrig_Pickable) /*&& Engine->key(gg::GG_E)*/){
        int id = _pRec->data.find(kDat_PickableItemId);

        bool result = static_cast<CPlayerController*>(oManager->getComponent(gg::PLAYERCONTROLLER, nCAgentID))->pickItem(id);
        if(result){
            //gg::cout(" -- Picked object: "+std::to_string(id));
            // Ha podido coger el item
            _pRec->nExpirationTime = 20;
            oManager->removeEntity(id);
        }
        else{
            // No ha podido cogerlo
            //gg::cout(" -- Can't pick object: "+std::to_string(id)+" -> FULL POCKETS");
        }
    }
}

void CAgent::STAY_func_kTrig_Explosion   (TriggerRecordStruct *_pRec){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAgent::onTriggerExit(TriggerRecordStruct* _pRec){
    (this->*mapFuncOnTriggerExit[_pRec->eTriggerType])(_pRec);
}

void CAgent::EXIT_func_kTrig_none        (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_Gunfire     (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_EnemyNear   (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_Shoot       (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_Aturd       (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_Touchable   (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_Pickable    (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_Explosion   (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_ExpansiveWave (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_ExpansiveForce (TriggerRecordStruct *_pRec){}

void CAgent::EXIT_func_kTrig_DeadAlien   (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_DeadAlien){
        CAIEnem *AI = static_cast<CAIEnem*>(oManager->getComponent(gg::AIENEM,getEntityID()));
        if(AI){
            AI->setCloserAllyIsDead(false);
            //gg::cout("ROMERO");
        }
    }
}

void CAgent::EXIT_func_kTrig_Senyuelo    (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_Senyuelo){
        if(oManager->getComponent(gg::AIENEM,nCAgentID)){
            //// std::cout << "core si" << '\n';
            static_cast<CAIEnem*>(oManager->getComponent(gg::AIENEM,nCAgentID))->MHandler_SENYUELO_END();
            //// std::cout << "core no" << '\n';
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAgent::deletetrig(TriggerRecordStruct* _pRec){
    std::list <CAgent*>::iterator it2 ;
    std::list <TriggerRecordStruct*>::iterator it;

    it2=CAgent::AgentList.begin();
    CAgent* pAgent=NULL;
    for(unsigned long i=0; i<CAgent::AgentList.size();++i)
    {
        pAgent=*it2;

        it=pAgent->TriggerList.begin();
        TriggerRecordStruct* pTrig=NULL;
        for(unsigned long e=0; e<pAgent->TriggerList.size();++e)
        {
            pTrig=*it;
            if(pTrig==_pRec){

                pAgent->onTriggerExit(_pRec);
                pAgent->TriggerList.erase(it);
                break;
            }
            it++;

        }


        it2++;
    }

}
bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){
    std::list <TriggerRecordStruct*>::iterator it;
    it=TriggerList.begin();
    TriggerRecordStruct* pTrig=NULL;
    for(unsigned long i=0; i<TriggerList.size();++i)
    {
        pTrig=*it;
        if(pTrig==_pRec){
            return false;
        }
        it++;

    }

    //MessageXplotato* exp =(MessageXplotato*) _pRec->data;

    bool res=onTriggerEnter(_pRec);
    if(res)
    TriggerList.push_back(_pRec);
    //posible codigo init

    //...
    //update
    //update(_pRec);
    //TriggerList;
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
    AgentList.push_back(agente);
}
void CAgent::removeAgent(std::list<CAgent*>::iterator ite){
    AgentList.erase(ite);
}



//void CAgent::update(){
//    std::list <TriggerRecordStruct*>::iterator it;
//    it=TriggerList.begin();
//    TriggerRecordStruct* pTrig=NULL;
//    for(unsigned long i=0; i<TriggerList.size();++i)
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

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CAgent::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

// void CAgent::Update(){
//     // UPDATE
//     //setposition
//     //CAgent(cTransform->getPosition);
// }

void CAgent::getWeaponInformation(float &dmg, float &cdc, float &relDT, float &rng, int &tb, int _type){
    switch (_type){
        case 0:
            // Rifle
            dmg = 0.7;
            cdc = 7;
            tb  = 30;
            relDT = 1;
            rng = 0.7;
            break;
        case 1:
            // Escopeta
            dmg = 0.8;
            cdc = 1;
            tb  = 10;
            relDT = 3;
            rng = 0.4;
            break;
        case 2:
            // Ametralladora
            dmg = 0.3;
            cdc = 9;
            tb  = 100;
            relDT = 6;
            rng = 0.7;
            break;
        case 3:
            // Pistola
            dmg = 0.4;
            cdc = 5;
            tb  = 15;
            relDT = 0.5;
            rng = 0.5;
            break;
        case 4:
            // Katana
            dmg = 1;
            cdc = 0.5;
            tb  = -1;
            relDT = -1;
            rng = 0.1;
            break;
    }

    //gg::cout(" --- GUN PICKED --- ");
    //gg::cout(" - - DMG= "       + std::to_string(dmg));
    //gg::cout(" - - CADENCE= "   + std::to_string(cdc));
    //gg::cout(" - - BULLETS= "   + std::to_string(tb));
    //gg::cout(" - - DT= "        + std::to_string(relDT));
    //gg::cout(" - - RANGE= "     + std::to_string(rng));
    //gg::cout(" ------------------ ");
}
