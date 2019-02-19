//
//  SoundSystem.h
//  vdrift
//
//  Created by Pierre on 20171022.
//

#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <map>
#include <string>

#include "inc/fmod_extra.hpp"
#include <Util.hpp>

#include "SoundEvent.hpp"
#include "ForestSound.hpp"
#include <Singleton.hpp>

class SoundSystem {
	friend class Singleton<SoundSystem>;
	public:
		SoundSystem();
		~SoundSystem();

		SoundEvent* createSound(const std::string&);
		void update();
		void CLIN();
	private:
		FMOD::Studio::System	*system;
		FMOD::System			*lowLevelSystem;

		FMOD::Studio::Bank		*masterBank;
		FMOD::Studio::Bank		*stringsBank;
		FMOD::Studio::Bank		*ambienteBank;
		FMOD::Studio::Bank		*sfxBank;
		FMOD::Studio::Bank		*musicaBank;
		FMOD::Studio::Bank		*vocesBank;

	    // std::map<std::string, FMOD::Studio::Bank*> banks;
	    // std::map<std::string, FMOD::Studio::EventDescription*> eventDescriptions;
	    std::map<std::string, SoundEvent*> soundEvents;
};


#endif /* SoundSystem_h */
