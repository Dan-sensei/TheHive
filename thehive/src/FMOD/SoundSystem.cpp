#include "SoundSystem.hpp"

SoundSystem::SoundSystem(){
<<<<<<< HEAD
	system 				= nullptr;
	lowLevelSystem 		= nullptr;

	masterBank 			= nullptr;
	stringsBank 		= nullptr;
	SFXBank				= nullptr;
	ambienceBank 		= nullptr;

	// Create the Studio System object
	ERRCHECK(FMOD::Studio::System::create		(&system));
	ERRCHECK(system->getLowLevelSystem			(&lowLevelSystem));
	ERRCHECK(lowLevelSystem->setSoftwareFormat	(0,FMOD_SPEAKERMODE_5POINT1,0));
	ERRCHECK(lowLevelSystem->setOutput			(FMOD_OUTPUTTYPE_AUTODETECT));
	ERRCHECK(system->initialize					(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

	system->loadBankFile("assets/FMOD/Master_Bank.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&masterBank);
	system->loadBankFile("assets/FMOD/Master_Bank.strings.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&stringsBank);
	system->loadBankFile("assets/FMOD/SFX.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&SFXBank);
	system->loadBankFile("assets/FMOD/Ambience.bank",FMOD_STUDIO_LOAD_BANK_NORMAL,&ambienceBank);
}

SoundSystem::~SoundSystem(){}

SoundEvent* SoundSystem::createSound(const std::string &_str){
	FMOD::Studio::EventDescription 	*event 		= nullptr;
	FMOD::Studio::EventInstance 	*instance 	= nullptr;
	ForestSound *ret;

	if(soundEvents.find(_str) == soundEvents.end()){
		ERRCHECK(system->getEvent(_str.c_str(),&event));
		ERRCHECK(event->createInstance(&instance));

		ret = new ForestSound(instance);
		soundEvents.insert(std::make_pair(_str,ret));
	}
	else{
		ret = static_cast<ForestSound*>(soundEvents[_str]);
	}

	return ret;
=======
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

	  FMOD_3D_ATTRIBUTES *attr;
	  system->setListenerAttributes(0, attr);

		createSnaps();
}

SoundSystem::~SoundSystem(){
	CLIN();
}

SoundEvent* SoundSystem::createSound(const std::string &_str, SoundEvent* ret){

	FMOD::Studio::EventInstance 	*instance = nullptr;
	if(soundEvents.find(_str) == soundEvents.end()){

		FMOD::Studio::EventDescription 	*event 	= nullptr;
		ERRCHECK(system->getEvent(_str.c_str(), &event));


		ERRCHECK(event->createInstance(&instance));

		ret->newSoundEvent(instance);


		eventDescriptions.insert(std::make_pair(_str,event));
		soundEvents.insert(std::make_pair(_str,ret));

		return ret;
	}

	else {
		eventDescriptions.find(_str)->second->createInstance(&instance);
		ret->newSoundEvent(instance);
		return ret;
	}
}

void SoundSystem::createSnaps(){

	FMOD::Studio::EventDescription 	*event 	= nullptr;
	FMOD::Studio::EventInstance 	*instance = nullptr;
	ERRCHECK(system->getEvent("snapshot:/Latido", &event));
	ERRCHECK(event->createInstance(&instance));

	snap_latido = new SonidoNormal();
	snap_latido->newSoundEvent(instance);

	eventDescriptions.insert(std::make_pair("snapshot:/Latido",event));
	soundEvents.insert(std::make_pair("snapshot:/Latido",snap_latido));


	FMOD::Studio::EventDescription 	*event2 	= nullptr;
	FMOD::Studio::EventInstance 	*instance2 = nullptr;
	ERRCHECK(system->getEvent("snapshot:/Game", &event2));
	ERRCHECK(event2->createInstance(&instance2));

	snap_game = new SonidoNormal();
	snap_game->newSoundEvent(instance2);

	eventDescriptions.insert(std::make_pair("snapshot:/Game",event2));
	soundEvents.insert(std::make_pair("snapshot:/Game",snap_game));

	FMOD::Studio::EventDescription 	*event3 	= nullptr;
	FMOD::Studio::EventInstance 	*instance3 = nullptr;
	ERRCHECK(system->getEvent("snapshot:/Dialogos", &event3));
	ERRCHECK(event3->createInstance(&instance3));

	snap_dialogos = new SonidoNormal();
	snap_dialogos->newSoundEvent(instance3);

	eventDescriptions.insert(std::make_pair("snapshot:/Dialogos",event3));
	soundEvents.insert(std::make_pair("snapshot:/Dialogos",snap_dialogos));

	FMOD::Studio::EventDescription 	*event4 	= nullptr;
	FMOD::Studio::EventInstance 	*instance4 = nullptr;
	ERRCHECK(system->getEvent("snapshot:/Pause", &event4));
	ERRCHECK(event4->createInstance(&instance4));

	snap_pause = new SonidoNormal();
	snap_pause->newSoundEvent(instance4);

	eventDescriptions.insert(std::make_pair("snapshot:/Pause",event4));
	soundEvents.insert(std::make_pair("snapshot:/Pause",snap_pause));
}


void SoundSystem::setVolume(float vol, const std::string& busPath){

	FMOD::Studio::Bus *bus;
	system->getBus(busPath.c_str(), &bus);

	bus->setVolume(vol);
}

void SoundSystem::setListenerPosition(glm::vec3 _pos){
	FMOD_3D_ATTRIBUTES *att;
	system->getListenerAttributes(0, att);

	FMOD_VECTOR vec;
	vec.x = _pos.x;
	vec.y = _pos.y;
	vec.z = _pos.z;

	att->position = vec;
	system->setListenerAttributes(0, att);
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
}

void SoundSystem::update(){
	if(system){
		system->update();
	}
}

<<<<<<< HEAD
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
	SFXBank->unload();
	system->release();
=======
float SoundSystem::getVolume(const std::string& busPath){
	FMOD::Studio::Bus *bus;
	float v;

	system->getBus(busPath.c_str(), &bus);
	bus->getVolume(&v,0);

	return v;

}

void SoundSystem::snapPlay(const std::string &_str){
	soundEvents.find(_str)->second->play();
}

void SoundSystem::CLIN(){

	// A clinear!

	// auto it2 = eventDescriptions.begin();
	// while(it2!=eventDescriptions.end()){
	// 	(it2->second)->releaseAllInstances();
	// 	delete it2->second;
	// 	it2++;
	// }
	eventDescriptions.clear();

	// auto it = soundEvents.begin();
	// while(it!=soundEvents.end()){
	// 	delete (it->second);
	// 	it++;
	// }
	soundEvents.clear();

	masterBank->unload();

	stringsBank->unload();

	sfxBank->unload();

	ambienteBank->unload();

	musicaBank->unload();

	vocesBank->unload();

	system->release();

	lowLevelSystem->release();


>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
}
