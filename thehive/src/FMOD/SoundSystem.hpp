#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <map>
#include <string>
#include <vector>

#include "inc/fmod_extra.hpp"
#include <Util.hpp>

#include "SoundEvent.hpp"
#include "TiposSonido.hpp"

#include <Singleton.hpp>

class SoundSystem {
	friend class Singleton<SoundSystem>;
	public:
		SoundSystem();
		~SoundSystem();

		SoundEvent* createSound(const std::string&, SoundEvent*, TiposSonido tipo);

		// SoundEvent* devuelve_escopeta(const std::string&);
		// SoundEvent* devuelve_impacto(const std::string&);
		// SoundEvent* devuelve_normal(const std::string&);
		// SoundEvent* devuelve_salud(const std::string&);
		// SoundEvent* devuelve_superficie(const std::string&);

		void setVolume(float,const std::string&);
		void setListenerPosition(glm::vec3);
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

	    std::map<std::string, FMOD::Studio::EventDescription*> eventDescriptions;
		std::map<std::string, SoundEvent*> soundEvents;

		// using pFunc = SoundEvent*(SoundSystem::*)(const std::string &);
        // pFunc VectorTipos[NUM_TIPOS];
};


#endif /* SoundSystem_h */
