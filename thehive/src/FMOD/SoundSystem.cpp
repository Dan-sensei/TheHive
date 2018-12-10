#include "SoundSystem.hpp"

SoundSystem::SoundSystem(){
    FMOD::Studio::System::create(&system);
    system->getLowLevelSystem(&lowLevelSystem);
    lowLevelSystem->setSoftwareFormat (0 , FMOD_SPEAKERMODE_STEREO , 0);
    lowLevelSystem -> setOutput ( FMOD_OUTPUTTYPE_AUTODETECT );
    system -> initialize (512 ,FMOD_STUDIO_INIT_NORMAL ,FMOD_INIT_NORMAL ,0));
    system -> loadBankFile (" .../Master_Bank.bank ", FMOD_STUDIO_LOAD_BANK_NORMAL ,& masterBank ) );
    system -> loadBankFile (" .../Master_Bank.strings.bank ", FMOD_STUDIO_LOAD_BANK_NORMAL ,& stringsBank ) );
    //system -> getEvent (" event :/ Ambience / Country ", & event );
}

SoundSystem::~SoundSystem(){}
