#include "SoundSystem.hpp"

SoundSystem::SoundSystem(){
	system 	= nullptr;
	FMOD::Studio::System::create		(&system);
	lowLevelSystem = nullptr;
	system->getLowLevelSystem			(&lowLevelSystem);

	lowLevelSystem->setSoftwareFormat	(0,FMOD_SPEAKERMODE_5POINT1,0);
	lowLevelSystem->setOutput			(FMOD_OUTPUTTYPE_AUTODETECT);

	system->initialize	(512, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_NORMAL, 0);

	masterBank 	= nullptr;
	system->loadBankFile("assets/FMOD/Master_Bank.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&masterBank);
	stringsBank = nullptr;
	system->loadBankFile("assets/FMOD/Master_Bank.strings.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&stringsBank);

	 ambienteBank = nullptr;
	 system->loadBankFile("assets/FMOD/Ambiente.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&ambienteBank);
	 sfxBank = nullptr;
	 system->loadBankFile("assets/FMOD/SFX.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&sfxBank);
	 musicaBank	= nullptr;
	 system->loadBankFile("assets/FMOD/Musica.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&musicaBank);
	 vocesBank	= nullptr;
	 system->loadBankFile("assets/FMOD/Voces.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&vocesBank);

	 // FMOD_3D_ATTRIBUTES *attr;
	 // system->setListenerAttributes(0, attr);
}

SoundSystem::~SoundSystem(){
	CLIN();
}

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
	// if(system){
	// 	system->update();
	// }
}

void SoundSystem::CLIN(){
	// A clinear!
	std::map<std::string,SoundEvent*>::iterator it = soundEvents.begin();
	while(it!=soundEvents.end()){
		delete it->second;
		it++;
	}
	soundEvents.clear();

	std::map<std::string,FMOD::Studio::EventDescription*>::iterator it2 = eventDescriptions.begin();
	while(it2!=eventDescriptions.end()){
		delete it2->second;
		it2++;
	}
	eventDescriptions.clear();

	masterBank->unload();
	stringsBank->unload();
	sfxBank->unload();
	ambienteBank->unload();
	musicaBank->unload();
	vocesBank->unload();
	lowLevelSystem->release();
	system->release();

}
