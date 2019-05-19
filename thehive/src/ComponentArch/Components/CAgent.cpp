#include "CAgent.hpp"
#include "ComponentArch/Components/CAgent.hpp"

#include "PopState.hpp"
#include <States/StateMachine.hpp>
#include <list>
#include "ComponentArch/Message.hpp"
#include "CGun.hpp"
#include "CRigidBody.hpp"
#include "CTransform.hpp"
#include "CAIEnem.hpp"
#include "Omicron/ZMaterial.hpp"

#include <ComponentArch/Components/CRigidBody.hpp>
#include <ComponentArch/Components/CVida.hpp>
#include <ComponentArch/Components/CPlayerController.hpp>

std::list <CAgent*>  CAgent::AgentList;
//
CAgent::CAgent(const unsigned long &_flags)
:cTransform(nullptr), Engine(nullptr)
{
    dwTriggerFlags = _flags;
    nDeltaTime=0;
    oManager = Singleton<ObjectManager>::Instance();
    _AssetManager = Singleton<AssetManager>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    hud = Singleton<HUD>::Instance();


}

CAgent::~CAgent() {

    delete s_puerta;
    delete s_fusible;
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
    Engine = Singleton<Omicron>::Instance();

    s_puerta = new SonidoNormal();
    SS->createSound("event:/SFX/Entorno/PuertaEstacion", s_puerta);

    s_fusible = new SonidoNormal();
    SS->createSound("event:/Voces/Companyera/FrasePuerta", s_fusible);

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
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_LoadZone,     &CAgent::ENTER_func_kTrig_LoadZone));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_UnLoadZone,   &CAgent::ENTER_func_kTrig_UnLoadZone));
    mapFuncOnTriggerEnter.insert(std::make_pair(kTrig_InteractMess,   &CAgent::ENTER_func_kTrig_InteractMess));
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
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_ExpansiveForce,&CAgent::STAY_func_kTrig_ExpansiveForce));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_LoadZone,      &CAgent::STAY_func_kTrig_LoadZone));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_UnLoadZone,    &CAgent::STAY_func_kTrig_UnLoadZone));
    mapFuncOnTriggerStay.insert(std::make_pair(kTrig_InteractMess,    &CAgent::STAY_func_kTrig_InteractMess));
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
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_ExpansiveForce,&CAgent::EXIT_func_kTrig_ExpansiveForce));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_LoadZone,      &CAgent::EXIT_func_kTrig_LoadZone));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_UnLoadZone,    &CAgent::EXIT_func_kTrig_UnLoadZone));
    mapFuncOnTriggerExit.insert(std::make_pair(kTrig_InteractMess,    &CAgent::EXIT_func_kTrig_InteractMess));
    // mapFuncOnTriggerExit.insert(std::make_pair(kTrig_Plantilla,    &CAgent::EXIT_func_kTrig_Plantilla));


    // void (*)(std::__cxx11::basic_string<char>&, signed char)
    // void (*)(std::__cxx11::basic_string<char>, signed char)

    zonesArray[0] = std::make_pair("INICIO", BinaryParser::LoadBVHLevelData);
    zonesArray[1] = std::make_pair("PASILLOS", BinaryParser::LoadLevelData);
    zonesArray[2] = std::make_pair("TUNELES", BinaryParser::LoadLevelData);
    zonesArray[3] = std::make_pair("INICIO_CIUDAD", BinaryParser::LoadBVHLevelData);
    zonesArray[4] = std::make_pair("CALLE_PRINCIPAL", BinaryParser::LoadLevelData);
    zonesArray[5] = std::make_pair("CENTRO", BinaryParser::LoadBVHLevelData);
    zonesArray[6] = std::make_pair("FINAL", BinaryParser::LoadLevelData);


    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

//std::list  <TriggerRecordStruct*>  AgentList;

void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}

unsigned long  CAgent::GetTriggerFlags(){
    return dwTriggerFlags;
}

glm::vec3 CAgent::GetPosition(){
    return cTransform->getPosition();
}

void CAgent::updatetrig(){
    TriggerRecordStruct *pTrig;
    float fDistance;
    glm::vec3 TF_POS = cTransform->getPosition();

    std::vector<std::list<TriggerRecordStruct*>::iterator> vec;
    //std::vector<std::list<TriggerRecordStruct*>::iterator>::iterator it2 = vec.begin();

    std::list<TriggerRecordStruct*>::iterator it = TriggerList.begin();
    while(it != TriggerList.end()){
        pTrig = *it;
        fDistance = glm::distance(pTrig->vPos,TF_POS );

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

void CAgent::ENTER_func_kTrig_InteractMess          (TriggerRecordStruct *_pRec){

    //inicializaciones necesarias
    EnumDataType tipos[3]={kDat_img1,kDat_img2,kDat_img3};
    std::string  imagenes[3]={"assets/HUD/interaccionar_esp.png","assets/HUD/salto_esp.png","assets/HUD/ultrasonido_esp.png"};

    auto mes=_pRec->data;

    //std::cout << "entra" << '\n';
    if((int)mes.find(kDat_img1)==2){
        Singleton<AIDirector>::Instance()->setActive(true);
        //std::cout << "activando" << '\n';
    }

    auto estado = new PopState();

    int total=mes.find(kDat_total_img);
    for (size_t i = 0; i < total; i++) {
        estado->Addim(Singleton<AssetManager>::Instance()->getTextureWithoutSavingToMap( imagenes[(int)mes.find(tipos[i])].c_str() ));
    }

    //estado->Addim("assets/HUD/asdw_esp.png");
    //estado->Addim("assets/HUD/camara_esp.png");
    //estado->Addim("assets/HUD/dash_esp.png");
    Singleton<StateMachine>::Instance()->AddState(estado);
}
void CAgent::ENTER_func_kTrig_none          (TriggerRecordStruct *_pRec){}
void CAgent::ENTER_func_kTrig_Touchable     (TriggerRecordStruct *_pRec){}
void CAgent::ENTER_func_kTrig_Pickable      (TriggerRecordStruct *_pRec){}
void CAgent::ENTER_func_kTrig_Gunfire       (TriggerRecordStruct *_pRec){}

void CAgent::ENTER_func_kTrig_LoadZone       (TriggerRecordStruct *_pRec){
    int8_t id = _pRec->data.find(kDat_LoadThatZone);
    std::string name = zonesArray[id].first;
    zonesArray[id].second("assets/BinaryFiles/"+name+"_MODELS.data", id);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/"+name+"_EVENTS.data", id);
    BinaryParser::LoadLevelLights("assets/BinaryFiles/"+name+"_LIGHTS.data", id);
}

void CAgent::ENTER_func_kTrig_UnLoadZone       (TriggerRecordStruct *_pRec){
    int8_t id = _pRec->data.find(kDat_LoadThatZone);
    Engine->SetMapZoneVisibility(id,false);
    Engine->resetLightsZone(id);
}

void CAgent::ENTER_func_kTrig_ExpansiveWave (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_ExpansiveWave){

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
void CAgent::STAY_func_kTrig_InteractMess           (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_none           (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_EnemyNear      (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_Shoot          (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_Senyuelo       (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_Aturd          (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_DeadAlien      (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_ExpansiveWave  (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_ExpansiveForce  (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_LoadZone   (TriggerRecordStruct *_pRec){}
void CAgent::STAY_func_kTrig_UnLoadZone   (TriggerRecordStruct *_pRec){}

void CAgent::STAY_func_kTrig_Gunfire     (TriggerRecordStruct *_pRec){
    if(_pRec->eTriggerType & kTrig_Gunfire){
        float   dmg, cdc, relDT, rng;
        std::string sonido_disparo, sonido_recarga, sonido_desenfundado, sonido_vacia,imgP,imgS;
        int     cb,tb;
        CGun *gun = static_cast<CGun*>(oManager->getComponent(gg::GUN,nCAgentID));
        CPlayerController *cpc = static_cast<CPlayerController*>(oManager->getComponent(gg::PLAYERCONTROLLER,nCAgentID));

        if(!cpc->canPickWeapon()){
            return;
        }
        //recogemos arma
        //Singleton<Motor2D>::Instance()->changeWeapon();
        //Singleton<Motor2D>::Instance()->setbullet(0,gun->getBullets(),gun->getTotalBullets());

        if(gun){
            if(!cpc->heroHasSecondWeapon()){
                // Puedo recoger el arma del suelo
                int _wtype_floor = static_cast<int>(_pRec->data.find(kDat_WeaponType));
                //gg::cout("PICKING: TYPE " + std::to_string(_wtype_floor) + " WEAPON");

                gg::getWeaponInformation(dmg,cdc,relDT,rng,cb,tb,_wtype_floor, sonido_disparo,sonido_recarga,sonido_desenfundado,sonido_vacia,imgP,imgS);

                // Le anyado la nueva
                CGun* Gun = new CGun(dmg,cdc,cb,tb,relDT,rng,_wtype_floor,sonido_disparo,sonido_recarga,sonido_desenfundado,sonido_vacia);
                cpc->setSecondWeapon(Gun);
                Gun->cogida();
                // Singleton<Motor2D>::Instance()->setbullet(1,Gun->getBullets(),Gun->getTotalBullets());
                // Singleton<Motor2D>::Instance()->setWeaponImg(1,img);

                hud->setSecondaryImg(_AssetManager->getTexture(imgP),_AssetManager->getTexture(imgS));
            }
            else{
                //cambiamos la principal
                // Puedo recoger el arma del suelo
                int _wtype_actual = gun->getType();
                int _wtype_floor = static_cast<int>(_pRec->data.find(kDat_WeaponType));
                //gg::cout("PICKING: TYPE " + std::to_string(_wtype_floor) + " WEAPON");

                gg::getWeaponInformation(dmg,cdc,relDT,rng,cb,tb,_wtype_floor, sonido_disparo,sonido_recarga,sonido_desenfundado,sonido_vacia,imgP,imgS);

                // Elimino el arma que tiene la entidad
                oManager->removeComponentFromEntity(gg::GUN,nCAgentID);

                // Le anyado la nueva
                CGun* Gun = new CGun(dmg,cdc,cb,tb,relDT,rng,_wtype_floor,sonido_disparo,sonido_recarga,sonido_desenfundado,sonido_vacia);
                oManager->addComponentToEntity(Gun, gg::GUN, nCAgentID);
                Gun->cogida();

                //Singleton<Motor2D>::Instance()->setbullet(0,Gun->getBullets(),Gun->getTotalBullets());
                //Singleton<Motor2D>::Instance()->setWeaponImg(0,img);

                // glm::vec3 pos(
                //     static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().x,
                //     static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().y+5,
                //     static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition().z
                // );

                glm::vec3 pos = static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition();
                pos.y += 5;

                uint16_t weapon = Singleton<Factory>::Instance()->createCollectableWeapon(pos,_wtype_actual);

                glm::vec3 from = static_cast<CTransform*>(oManager->getComponent(gg::TRANSFORM,nCAgentID))->getPosition();
                glm::vec3 to = Singleton<ggDynWorld>::Instance()->getRaycastVector();
                glm::vec3 vec = (to-from)*30.f;
                static_cast<CRigidBody*>(oManager->getComponent(gg::RIGID_BODY,weapon))->applyCentralForce(vec);

                // Singleton<Motor2D>::Instance()->setbullet(0,Gun->getBullets(),Gun->getTotalBullets());
                // Singleton<Motor2D>::Instance()->setWeaponImg(0,img);
                hud->setSecondaryImg(_AssetManager->getTexture(imgP),_AssetManager->getTexture(imgS));
            }

            // Destruyo el arma del suelo y su evento
            int id = _pRec->data.find(kDat_EntId);
            oManager->removeEntity(id);
            _pRec->nExpirationTime = 50;
        }
        else{
            // NO TIENE ARMA
            gg::getWeaponInformation(dmg,cdc,relDT,rng,cb,tb,static_cast<int>(_pRec->data.find(kDat_WeaponType)),sonido_disparo,sonido_recarga,sonido_desenfundado,sonido_vacia,imgP,imgS);

            // Creo y anyado un arma a la entidad
            CGun* Gun = new CGun(dmg,cdc,cb,tb,relDT,rng,static_cast<int>(_pRec->data.find(kDat_WeaponType)),sonido_disparo,sonido_recarga,sonido_desenfundado,sonido_vacia);
            oManager->addComponentToEntity(Gun, gg::GUN, nCAgentID);

            // ------------------
            // Singleton<Motor2D>::Instance()->setbullet(0,Gun->getBullets(),Gun->getTotalBullets());
            // Singleton<Motor2D>::Instance()->setWeaponImg(0,img);
            // HUD hud;
            // hud.setSecondaryImg(_AssetManager->getTexture(imgP),_AssetManager->getTexture(imgS));
            // ------------------


            // Destruyo el arma del suelo y su evento
            int id = _pRec->data.find(kDat_EntId);
            oManager->removeEntity(id);
            _pRec->nExpirationTime = 50;
        }
    }
}

void CAgent::STAY_func_kTrig_Touchable   (TriggerRecordStruct *_pRec){
    if((_pRec->eTriggerType & kTrig_Touchable) && Engine->key(gg::E)){
        uint16_t item = _pRec->data.find(kDat_PickableItemId);
        uint16_t boton = _pRec->data.find(kDat_PickableItemId);

        CPlayerController *cpc = static_cast<CPlayerController*>(oManager->getComponent(gg::PLAYERCONTROLLER,nCAgentID));
        if(item && !cpc->hasItem(item)){

            s_fusible->play();
            // El heroe no ha cogido el item en concreto para realizar la accion
            //gg::cout("You shall not PASS!!!");
            return;
        }
        //CAMBIO COLOR
        if (item){
            ZMaterial* Dark = _AssetManager->getMaterial("Red");
            //static_cast<CRenderable_3D*>(oManager->getComponent(gg::RENDERABLE_3D, item))->changeMaterial(Dark);
        }

        s_puerta->play();
        // // Usa y destruye el item
        cpc->useItem(item);

        bool isDone = _pRec->data.find(kDat_Done);
        if(!isDone){
            uint16_t eIdObj     = _pRec->data.find(kDat_EntId);
            int actionId        = _pRec->data.find(kDat_Action);
            // //std::cout << "ID: " << eIdObj << " || ACTION: " << actionId << '\n';

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
    if((_pRec->eTriggerType & kTrig_Pickable) /*&& Engine->key(gg::E)*/){
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

void CAgent::EXIT_func_kTrig_InteractMess        (TriggerRecordStruct *_pRec){
    Singleton<CTriggerSystem>::Instance()->RemoveTrigger(_pRec);
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
void CAgent::EXIT_func_kTrig_LoadZone (TriggerRecordStruct *_pRec){}
void CAgent::EXIT_func_kTrig_UnLoadZone (TriggerRecordStruct *_pRec){}

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
            //// //std::cout << "core si" << '\n';
            static_cast<CAIEnem*>(oManager->getComponent(gg::AIENEM,nCAgentID))->MHandler_SENYUELO_END();
            //// //std::cout << "core no" << '\n';
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

//CAgent::CAgent(unsigned long _dwTriggerFlags,glm::vec3 _vPos){
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

/*
// MOVIDO A UTIL.HPP
void CAgent::gg::getWeaponInformation(float &dmg, float &cdc, float &relDT, float &rng, int &tb, int _type){
    switch (_type){
        case 0:
            // Rifle
            dmg = 0.7;
            cdc = 7;
            tb  = 30;
            relDT = 1;
            rng = 0.7;

            sonido_disparo = "event:/SFX/Armas/Rifle/RifleDisparo";
            sonido_recarga = "event:/SFX/Armas/Rifle/RifleRecarga";
            sonido_desenfundado ="event:/SFX/Armas/Rifle/RifleDesenfundado";
            sonido_vacia ="event:/SFX/Armas/Rifle/RifleVacio";

            break;
        case 1:
            // Escopeta
            dmg = 0.8;
            cdc = 1;
            tb  = 10;
            relDT = 3;
            rng = 0.4;

            sonido_disparo = "event:/SFX/Armas/Escopeta/EscopetaDisparo";
            sonido_recarga = "event:/SFX/Armas/Escopeta/EscopetaRecarga";
            sonido_desenfundado ="event:/SFX/Armas/Escopeta/EscopetaDesenfundado";
            sonido_vacia ="event:/SFX/Armas/Escopeta/EscopetaVacia";

            break;
        case 2:
            // Ametralladora
            dmg = 0.3;
            cdc = 9;
            tb  = 100;
            relDT = 6;
            rng = 0.7;

            sonido_disparo = "event:/SFX/Armas/Ametralladora/AmetralladoraDisparo";
            sonido_recarga = "event:/SFX/Armas/Ametralladora/AmetralladoraRecarga";
            sonido_desenfundado ="event:/SFX/Armas/Ametralladora/AmetralladoraDesenfundado";
            sonido_vacia ="event:/SFX/Armas/Ametralladora/AmetralladoraVacia";

            break;
        case 3:
            // Pistola
            dmg = 0.4;
            cdc = 5;
            tb  = 15;
            relDT = 0.5;
            rng = 0.5;

            sonido_disparo = "event:/SFX/Armas/Pistola/PistolaDisparo";
            sonido_recarga = "event:/SFX/Armas/Pistola/PistolaRecarga";
            sonido_desenfundado ="event:/SFX/Armas/Pistola/PistolaDesenfundado";
            sonido_vacia ="event:/SFX/Armas/Pistola/PistolaVacia";

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
*/
