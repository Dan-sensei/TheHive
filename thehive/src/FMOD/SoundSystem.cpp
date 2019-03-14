#include "SoundSystem.hpp"

SoundSystem::SoundSystem(){
	system 	= nullptr;
	ERRCHECK(FMOD::Studio::System::create		(&system));
	lowLevelSystem = nullptr;
	ERRCHECK(system->getLowLevelSystem			(&lowLevelSystem));

	ERRCHECK(lowLevelSystem->setSoftwareFormat	(0,FMOD_SPEAKERMODE_5POINT1,0));
	ERRCHECK(lowLevelSystem->setOutput			(FMOD_OUTPUTTYPE_AUTODETECT));

	ERRCHECK(system->initialize	(512, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_NORMAL, 0));

	masterBank 	= nullptr;
	ERRCHECK(system->loadBankFile("assets/FMOD/Master_Bank.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&masterBank));
	stringsBank = nullptr;
	ERRCHECK(system->loadBankFile("assets/FMOD/Master_Bank.strings.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&stringsBank));

	 ambienteBank = nullptr;
	 system->loadBankFile("assets/FMOD/Ambiente.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&ambienteBank);
	 sfxBank = nullptr;
	 system->loadBankFile("assets/FMOD/SFX.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&sfxBank);
	 musicaBank	= nullptr;
	 system->loadBankFile("assets/FMOD/Musica.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&musicaBank);
	 vocesBank	= nullptr;
	 system->loadBankFile("assets/FMOD/Voces.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&vocesBank);

	 FMOD_3D_ATTRIBUTES *attr;
	 system->setListenerAttributes(0, attr);

	 // VectorTipos[ESCOPETA] = &SoundSystem::devuelve_escopeta;
	 // VectorTipos[IMPACTO] = &SoundSystem::devuelve_impacto;
	 // VectorTipos[NORMAL] = &SoundSystem::devuelve_normal;
	 // VectorTipos[SALUD] = &SoundSystem::devuelve_salud;
	 // VectorTipos[SUPERFICIE] = &SoundSystem::devuelve_superficie;
}

SoundSystem::~SoundSystem(){}

SoundEvent* SoundSystem::createSound(const std::string &_str, SoundEvent* ret, TiposSonido tipo){

	if(soundEvents.find(_str) == soundEvents.end()){

		FMOD::Studio::EventDescription 	*event 	= nullptr;
		ERRCHECK(system->getEvent(_str.c_str(), &event));

		FMOD::Studio::EventInstance 	*instance = nullptr;
		ERRCHECK(event->createInstance(&instance));

		ret->newSoundEvent(instance);

		soundEvents.insert(std::make_pair(_str,ret));

		return ret;
	}

	else {

		return soundEvents[_str]->getEvent();
	}
}


// SoundEvent* SoundSystem::devuelve_escopeta(const std::string &_str){
//
// 	return static_cast<SonidoEscopeta*>(soundEvents[_str]);
// }
//
// SoundEvent* SoundSystem::devuelve_impacto(const std::string &_str){
// 	return static_cast<SonidoImpacto*>(soundEvents[_str]);
// }
//
// SoundEvent* SoundSystem::devuelve_normal(const std::string &_str){
// 	return static_cast<SonidoNormal*>(soundEvents[_str]);
// }
//
// SoundEvent* SoundSystem::devuelve_salud(const std::string &_str){
// 	return static_cast<SonidoSalud*>(soundEvents[_str]);
// }
//
// SoundEvent* SoundSystem::devuelve_superficie(const std::string &_str){
// 	return static_cast<SonidoSuperficie*>(soundEvents[_str]);
// }


//
// void SoundSystem::setVolume(float vol, const std::string& busPath){
// 	FMOD::Studio::Bus bus;
// 	system->getBus(busPath.c_str(), &bus);
//
// 	bus->setVolume(vol);
// }

void SoundSystem::setListenerPosition(glm::vec3 _pos){
	FMOD_3D_ATTRIBUTES *att;
	system->getListenerAttributes(0, att);

	FMOD_VECTOR vec;
	vec.x = _pos.x;
	vec.y = _pos.y;
	vec.z = _pos.z;

	att->position = vec;
	system->setListenerAttributes(0, att);
}

void SoundSystem::update(){
	if(system){
		system->update();
	}
}

void SoundSystem::CLIN(){
	// A clinear!
	std::map<std::string,SoundEvent*>::iterator it = soundEvents.begin();
	while(it!=soundEvents.end()){
		delete it->second;
		it++;
	}
	soundEvents.clear();

	masterBank->unload();
	stringsBank->unload();
	sfxBank->unload();
	ambienteBank->unload();
	musicaBank->unload();
	vocesBank->unload();
	system->release();
}
