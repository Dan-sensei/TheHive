//
//  SoundSystem.h
//  vdrift
//
//  Created by Pierre on 20171022.
//

#ifndef _SOUNDSYSTEM_H
#define _SOUNDSYSTEM_H

#include <map>
#include <string>

using namespace std;

#include <glm/glm.hpp>
#include "inc/fmod_studio.hpp"
#include "inc/fmod.hpp"
#include "Util.hpp"

#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

class SoundEvent;
template <typename T>
class Singleton;

class SoundSystem {
friend class Singleton<SoundSystem>;
public:
    /**
     *  Constructor
     *  \param soundBanksPath ruta del directorio donde se encuentran los bancos generados con FMOD Studio
     */
	SoundSystem();

	~SoundSystem();

    /**
     *  Método factoría que Construye un SoundEvent a partir del nombre de un evento de FMOD Studio,
     *  p. ej. "event:/Ambience/Country"
     *
     *  \param eventPath nombre del evento según la nomenclatura de FMOD Studio
     */
    SoundEvent* getEvent(string eventPath);

	SoundEvent* createSoundEvent(FMOD::Studio::EventInstance* ins);

    /**
     *  Modifica el volumen general del motor de sonido
     */
    void setVolume(float vol);

    /**
     *  Modifica la posición del punto de escucha (en esta aplicación sólo hay uno)
     */
    void setListernerPosition(gg::Vector3f pos);

    /**
     *  Actualiza el motor de audio
     *  \param paused indica si hay que pausar el motor de audio o no
     */
    //void update(bool paused);
	void update();

	void release();

	//Funcion ERRCHECK

	void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line){
	    if(result!= FMOD_OK){
	        std::cerr << file << "(" << line << "): FMOD error"
	        << result << " - " << std::endl;
	        exit(-1);
	    }
	}
private:
    string banksPath;
	FMOD::Studio::System*	system = NULL;
	FMOD::System*			lowLevelSystem = NULL;
	FMOD::Studio::Bank* masterBank = NULL;
	FMOD::Studio::Bank* stringsBank = NULL;
	FMOD::Studio::Bank* sfx = NULL;
    map<string, FMOD::Studio::Bank*> banks;
    map<string, FMOD::Studio::EventDescription*> eventDescriptions;
	FMOD::Studio::EventDescription* event = NULL;
	SoundEvent* soundEvent = NULL;
    map<string, SoundEvent*> soundEvents;

};

class SoundEvent {
	friend class SoundSystem;
public:
    SoundEvent();
    virtual ~SoundEvent() = 0; /**>  SoundEvent es una clase abstracta */

    /**
     *  Comienza a reproducir el evento
     */
    void start();

    /**
     *  Detiene la reproducción del evento inmediatamente
     */
    void stopInmediate();

	/**
	 *  Detiene la reproducción del evento inmediatamente
	 */
	void stopFadeOut();

    /**
     *  Pausa la reproducción del evento.
     *  Para continuar la reproducción, usar start()
     *  \sa start()
     */
    void pause();

    /**
     *  Modifica el volumen del evento
     *  \param vol volumen del evento: 0=silencio, 1=máximo volumen
     */
    void setVolume(float vol);

    /**
     *  Modifca el volumen del evento multiplicando por un factor de ganancia
     *  \param gain factor de ganancia. 0=silencio, 1=mantener el volumen
     */
    void setGain(float gain);

	void setParameterValue(string nom, float value);

    /**
     *  Modifica la posición 3D del evento de sonido
     *  \param pos nuevo vector de posición
     */
    void setPosition(gg::Vector3f pos);

    /**
     *  Consulta si el evento está sonando
     *  \return devuelve cierto si el evento está sonando
     */
	 bool isPlaying();


	void release();

	FMOD::Studio::EventInstance* getInstance();


protected:
    FMOD::Studio::EventInstance* soundInstance = NULL;
    /**
     * Este método crea un SoundEvent (EngineSound, WindSound, etc.) correspondiente
     * al evento que recibe como argumento
     */
    virtual SoundEvent* newSoundEvent(FMOD::Studio::EventInstance*) = 0;


};


#endif /* SoundSystem_h */
