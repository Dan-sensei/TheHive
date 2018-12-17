#include "SoundSystem.hpp"
#include "ForestSound.hpp"


SoundSystem::SoundSystem(){

    FMOD::Studio::System::create(&system);
    ERRCHECK(system->getLowLevelSystem(&lowLevelSystem));
    ERRCHECK(lowLevelSystem->setSoftwareFormat (0 , FMOD_SPEAKERMODE_5POINT1 , 0));
    ERRCHECK(lowLevelSystem->setOutput ( FMOD_OUTPUTTYPE_AUTODETECT ));
    ERRCHECK(system->initialize (512 ,FMOD_STUDIO_INIT_NORMAL ,FMOD_INIT_NORMAL ,0));
    //int* cont;
    //system->getBankCount(cont);
    ERRCHECK(system->loadBankFile ("assets/FMOD/Master_Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL ,&masterBank));
    //system->getBankCount(cont);
    ERRCHECK(system->loadBankFile ("assets/FMOD/Master_Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL ,&stringsBank));
    //system->getBankCount(cont);
    ERRCHECK(system->loadBankFile ("assets/FMOD/SFX.bank", FMOD_STUDIO_LOAD_BANK_NORMAL ,&sfx));
    //system->getBankCount(cont);
    //FMOD_STUDIO_LOADING_STATE *state;
    //masterBank->getLoadingState(state);

    //system->getBank("assets/FMOD/SFX.bank",&masterBank);
    //masterBank->getLoadingState(state);

    this->setVolume(1);


}


SoundSystem::~SoundSystem(){}

SoundEvent* SoundSystem::getEvent(string eventPath){
    ERRCHECK(system->getEvent(eventPath.c_str(), &event));
    FMOD::Studio::EventInstance* ins = NULL;
    ERRCHECK(event->createInstance(&ins)); //no estamos seguros de si va aqui

    return createSoundEvent(ins);
}

SoundEvent* SoundSystem::createSoundEvent(FMOD::Studio::EventInstance* instance){
    soundEvent=new ForestSound();
    return soundEvent->newSoundEvent(instance);
}

void SoundSystem::setVolume(float vol){
    string busPath = "bus:/";
    FMOD::Studio::Bus* bus;
    ERRCHECK(system->getBus(busPath.c_str(),&bus));
    ERRCHECK(bus->setVolume(vol));

}

void SoundSystem::setListernerPosition(gg::Vector3f pos){
    FMOD_VECTOR v;
    v.x = pos.X;
    v.y = pos.Y;
    v.z = pos.Z;

   FMOD_3D_ATTRIBUTES a;
   a.position = v;
   system->setListenerAttributes(0,&a);
}
void SoundSystem::update(){
    system->update();
}
void SoundSystem::release(){
    stringsBank->unload();
    masterBank->unload();
    system->release();
}

// void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line){
//     if(result!= FMOD_OK){
//         std::cerr << file << "(" << line << "): FMOD error"
//         << result << " - " << FMOD::ErrorString(result) << std::endl;
//         exit(-1);
//     }
// }
//---------------------------------------------------------

SoundEvent::SoundEvent(){}

SoundEvent::~SoundEvent(){}



void SoundEvent::start(){
    ERRCHECK(soundInstance->start());
}

FMOD::Studio::EventInstance* SoundEvent::getInstance(){
    return soundInstance;
}

void SoundEvent::stopInmediate(){
    soundInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
}

void SoundEvent::stopFadeOut(){
    soundInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
}

void SoundEvent::pause(){
    ERRCHECK(soundInstance->setPaused(true));
}

void SoundEvent::setVolume(float vol){
    ERRCHECK(soundInstance->setVolume(vol));
}

void SoundEvent::setGain(float gain){
    float* vol;
    soundInstance->getVolume(vol,0);
    float volFinal = *vol * gain;
    soundInstance->setVolume(volFinal);
}

void SoundEvent::setPosition(gg::Vector3f pos){

     FMOD_VECTOR v;
     v.x = pos.X;
     v.y = pos.Y;
     v.z = pos.Z;

    FMOD_3D_ATTRIBUTES a;
    a.position = v;
    soundInstance->set3DAttributes(&a);
}

void SoundEvent::setParameterValue(string nom, float value){
    soundInstance->setParameterValue(nom.c_str(),value);
}

bool SoundEvent::isPlaying(){
    bool *pause;
    ERRCHECK(soundInstance->getPaused(pause));
    return *pause;
}

void SoundEvent::release(){
    soundInstance->release();
}
