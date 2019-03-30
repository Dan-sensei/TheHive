#ifndef _SKYBOX
#define _SKYBOX

//#include <iostream>
#include "AssetManager.hpp"
#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>
#include <Singleton.hpp>
#include <Omicron/Omicron.hpp>
//#include "GameEngine/Camera.hpp"
#include "Shader.hpp"
#include <vector>
#include <string>
class Omicron;

class SkyBox{
	public:
		SkyBox();
		~SkyBox();

        //unsigned int loadCubemap(std::vector<std::string>);  //otro forma de cargar el cubemap
		unsigned int loadCubemap(std::vector<const GLchar * >);
        void init();
        void Draw();

    private:
		Shader* inicio;
		Shader* fin;
		Omicron* engine;
        unsigned int cubemapTexture[4];
        unsigned int skyboxVBO;
        unsigned int skyboxVAO;
		unsigned int view;
		unsigned int text;

		int skyboxtype;

};

#endif
