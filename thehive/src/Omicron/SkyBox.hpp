#ifndef _SKYBOX_H
#define _SKYBOX_H

#include <Omicron/AssetManager.hpp>
#include <Singleton.hpp>
#include <Omicron/Omicron.hpp>
#include <vector>
#include <string>

class Omicron;

class SkyBox{
	public:
		SkyBox();
		~SkyBox();

        //unsigned int loadCubemap(std::vector<std::string>);  //otro forma de cargar el cubemap
		unsigned int loadCubemap(std::vector<const char * >);
        void init();
        void Draw();

    private:
		Shader* inicio;
		Omicron* engine;
        unsigned int cubemapTexture;
        unsigned int skyboxVBO;
        unsigned int skyboxVAO;
		unsigned int view;
		unsigned int text;

		//int skyboxtype;

};

#endif
