<<<<<<< HEAD
//
//  SoundSystem.h
//  vdrift
//
//  Created by Pierre on 20171022.
//

=======
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <map>
#include <string>
<<<<<<< HEAD

#include "inc/fmod_extra.hpp"
#include <Util.hpp>

#include "SoundEvent.hpp"
#include "ForestSound.hpp"
=======
#include <vector>

#include <FMOD/fmod_extra.hpp>
#include <Util.hpp>

#include "SoundEvent.hpp"
#include "TiposSonido.hpp"

>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
#include <Singleton.hpp>

class SoundSystem {
	friend class Singleton<SoundSystem>;
	public:
		SoundSystem();
		~SoundSystem();

<<<<<<< HEAD
		SoundEvent* createSound(const std::string&);
		void update();
=======
		SoundEvent* createSound(const std::string&, SoundEvent*);

		void setVolume(float,const std::string&);
		void setListenerPosition(glm::vec3);
		void update();
		float getVolume(const std::string&);
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
		void CLIN();
	private:
		FMOD::Studio::System	*system;
		FMOD::System			*lowLevelSystem;

		FMOD::Studio::Bank		*masterBank;
		FMOD::Studio::Bank		*stringsBank;
<<<<<<< HEAD
		FMOD::Studio::Bank		*SFXBank;
		FMOD::Studio::Bank		*ambienceBank;

	    // std::map<std::string, FMOD::Studio::Bank*> banks;
	    // std::map<std::string, FMOD::Studio::EventDescription*> eventDescriptions;
	    std::map<std::string, SoundEvent*> soundEvents;
=======
		FMOD::Studio::Bank		*ambienteBank;
		FMOD::Studio::Bank		*sfxBank;
		FMOD::Studio::Bank		*musicaBank;
		FMOD::Studio::Bank		*vocesBank;

	    std::map<std::string, FMOD::Studio::EventDescription*> eventDescriptions;
		std::map<std::string, SoundEvent*> soundEvents;

		// using pFunc = SoundEvent*(SoundSystem::*)(const std::string &);
        // pFunc VectorTipos[NUM_TIPOS];
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
};


#endif /* SoundSystem_h */
