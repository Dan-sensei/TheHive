#include "SoundSystem.hpp"

SoundSystem::SoundSystem(){
	system 	= nullptr;
	// FMOD::Studio::System::create		(&system);
	FMOD_Studio_System_Create(&system, FMOD_VERSION);

	lowLevelSystem = nullptr;
	// system->getLowLevelSystem			(&lowLevelSystem);
	FMOD_Studio_System_GetLowLevelSystem(system,&lowLevelSystem);

	// lowLevelSystem->setSoftwareFormat	(0,FMOD_SPEAKERMODE_5POINT1,0);
	FMOD_System_SetSoftwareFormat(lowLevelSystem, 0,FMOD_SPEAKERMODE_5POINT1, 0);
	// lowLevelSystem->setOutput			(FMOD_OUTPUTTYPE_AUTODETECT);
	FMOD_System_SetOutput(lowLevelSystem,FMOD_OUTPUTTYPE_AUTODETECT);

	// system->initialize	(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
	// FMOD_Studio_System_Initialize(system, 512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
		FMOD_Studio_System_Initialize(system, 512, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_NORMAL, 0);

	masterBank 	= nullptr;
	// system->loadBankFile("assets/FMOD/Master_Bank.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&masterBank);
	FMOD_Studio_System_LoadBankFile(system,"assets/FMOD/Master_Bank.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&masterBank);

	stringsBank = nullptr;
	// system->loadBankFile("assets/FMOD/Master_Bank.strings.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&stringsBank);
	FMOD_Studio_System_LoadBankFile(system,"assets/FMOD/Master_Bank.strings.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&stringsBank);

	ambienteBank = nullptr;
	//  system->loadBankFile("assets/FMOD/Ambiente.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&ambienteBank);
	FMOD_Studio_System_LoadBankFile(system,"assets/FMOD/Ambiente.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&ambienteBank);

	sfxBank = nullptr;
	//  system->loadBankFile("assets/FMOD/SFX.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&sfxBank);
	FMOD_Studio_System_LoadBankFile(system,"assets/FMOD/SFX.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&sfxBank);

	musicaBank	= nullptr;
	//  system->loadBankFile("assets/FMOD/Musica.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&musicaBank);
	FMOD_Studio_System_LoadBankFile(system,"assets/FMOD/Musica.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&musicaBank);

	vocesBank	= nullptr;
	//  system->loadBankFile("assets/FMOD/Voces.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&vocesBank);
	FMOD_Studio_System_LoadBankFile(system,"assets/FMOD/Voces.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&vocesBank);


	FMOD_3D_ATTRIBUTES *attr;
	//  system->setListenerAttributes(0, attr);
	FMOD_Studio_System_SetListenerAttributes(system,0,attr);
}

SoundSystem::~SoundSystem(){
	CLIN();
}

SoundEvent* SoundSystem::createSound(const std::string &_str, SoundEvent* ret){

	// FMOD::Studio::EventInstance 	*instance = nullptr;
	FMOD_STUDIO_EVENTINSTANCE 	*instance = nullptr;
	if(soundEvents.find(_str) == soundEvents.end()){

		// FMOD::Studio::EventDescription 	*event 	= nullptr;
		FMOD_STUDIO_EVENTDESCRIPTION 		*event 	= nullptr;
		// ERRCHECK(system->getEvent(_str.c_str(), &event));
		ERRCHECK(FMOD_Studio_System_GetEvent(system,_str.c_str(), &event));


		// ERRCHECK(event->createInstance(&instance));
		ERRCHECK(FMOD_Studio_EventDescription_CreateInstance(event,&instance));

		ret->newSoundEvent(instance);

		eventDescriptions.insert(std::make_pair(_str,event));
		soundEvents.insert(std::make_pair(_str,ret));

		return ret;
	}

	else {
		// eventDescriptions.find(_str)->second->createInstance(&instance);
		FMOD_Studio_EventDescription_CreateInstance(eventDescriptions.find(_str)->second,&instance);
		ret->newSoundEvent(instance);
		return ret;
	}
}


void SoundSystem::setVolume(float vol, const std::string& busPath){

	// FMOD::Studio::Bus *bus;
	FMOD_STUDIO_BUS *bus;

	// system->getBus(busPath.c_str(), &bus);
	FMOD_Studio_System_GetBus(system,busPath.c_str(), &bus);

	// bus->setVolume(vol);
	FMOD_Studio_Bus_SetVolume(bus,vol);
}

void SoundSystem::setListenerPosition(glm::vec3 _pos){
	FMOD_3D_ATTRIBUTES *att;
	// system->getListenerAttributes(0, att);
	FMOD_Studio_System_GetListenerAttributes(system,0,att);

	FMOD_VECTOR vec;
	vec.x = _pos.x;
	vec.y = _pos.y;
	vec.z = _pos.z;

	att->position = vec;
	// system->setListenerAttributes(0, att);
	FMOD_Studio_System_SetListenerAttributes(system,0,att);
}

void SoundSystem::update(){
	if(system){
		// system->update();
		FMOD_Studio_System_Update(system);
	}
}

float SoundSystem::getVolume(const std::string& busPath){
	// FMOD::Studio::Bus *bus;
	FMOD_STUDIO_BUS *bus;
	float v;

	// system->getBus(busPath.c_str(), &bus);
	// bus->getVolume(&v,0);

	FMOD_Studio_System_GetBus(system,busPath.c_str(), &bus);
	FMOD_Studio_Bus_GetVolume(bus,&v,0);

	return v;

}


void SoundSystem::setMute(const std::string& busPath){
	// FMOD::Studio::Bus *bus;
	FMOD_STUDIO_BUS *bus;
	FMOD_BOOL mute = false;
	FMOD_Studio_System_GetBus(system,busPath.c_str(), &bus);
	FMOD_Studio_Bus_GetMute(bus,&mute);

	if(mute){
		mute = false;
	}
	else{
		mute = true;
	}

	FMOD_Studio_Bus_SetMute(bus, mute);


}

void SoundSystem::CLIN(){

	// A clinear!

	// auto it2 = eventDescriptions.begin();
	// while(it2!=eventDescriptions.end()){
	// 	(it2->second)->releaseAllInstances();
	// 	delete it2->second;
	// 	it2++;
	// }

	// auto it = soundEvents.begin();
	// while(it!=soundEvents.end()){
	// 	delete (it->second);
	// 	it++;
	// }


	eventDescriptions.clear();

	soundEvents.clear();

	FMOD_Studio_Bank_Unload(masterBank);
	FMOD_Studio_Bank_Unload(stringsBank);
	FMOD_Studio_Bank_Unload(sfxBank);
	FMOD_Studio_Bank_Unload(ambienteBank);
	FMOD_Studio_Bank_Unload(musicaBank);
	FMOD_Studio_Bank_Unload(vocesBank);

	FMOD_Studio_System_Release(system);
	FMOD_System_Release(lowLevelSystem);

	// masterBank->unload();
	// stringsBank->unload();
	// sfxBank->unload();
	// ambienteBank->unload();
	// musicaBank->unload();
	// vocesBank->unload();
	// system->release();
	// lowLevelSystem->release();

}
