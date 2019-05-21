#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <map>
#include <string>
#include <vector>

#include <FMOD/fmod_extra.hpp>
#include <FMOD/fmod_studio_common.h>
#include <Util.hpp>

#include "SoundEvent.hpp"
#include "TiposSonido.hpp"

#include <Singleton.hpp>

class SoundSystem {
	friend class Singleton<SoundSystem>;
	public:
		SoundSystem();
		~SoundSystem();

		SoundEvent* createSound(const std::string&, SoundEvent*);

		void setVolume(float,const std::string&);
		void setListenerPosition(glm::vec3,glm::vec3);
		void update();
		float getVolume(const std::string&);
		void setMute(const std::string&);
		void CLIN();
	private:
		FMOD_STUDIO_SYSTEM	*system;
		FMOD_SYSTEM			*lowLevelSystem;

		FMOD_STUDIO_BANK	*masterBank;
		FMOD_STUDIO_BANK	*stringsBank;
		FMOD_STUDIO_BANK	*ambienteBank;
		FMOD_STUDIO_BANK	*sfxBank;
		FMOD_STUDIO_BANK	*musicaBank;
		FMOD_STUDIO_BANK	*vocesBank;

	    std::map<std::string, FMOD_STUDIO_EVENTDESCRIPTION*> eventDescriptions;
		std::map<std::string, SoundEvent*> soundEvents;

		// using pFunc = SoundEvent*(SoundSystem::*)(const std::string &);
        // pFunc VectorTipos[NUM_TIPOS];
};


#endif /* SoundSystem_h */
