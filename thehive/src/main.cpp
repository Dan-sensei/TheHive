/*
#include "Game.hpp"
#include <iostream>
#include <string>
#include <Singleton.hpp>
#include "GameAI/Pathfinding.hpp"
#include "GameAI/NavmeshStructs.hpp"
*/

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "GameEngine/Camera.hpp"
#include "Singleton.hpp"
#include "GameAI/Pathfinding.hpp"
#include "GameAI/NavmeshStructs.hpp"

#include "GameEngine/Motor2D.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>

#include "States/StateMachine.hpp"
#include "Game.hpp"
#include "MenuState.hpp"

#include <SurrealEngine/SurrealEngine.hpp>
#include <vector>
#include "BinaryParser.hpp"

int main(int argc, char const *argv[]) {
    // alias upd="rm -f EVENTOS.data && cp ~/Documentos/THE_HIVE_LevelEditor\ \(1\)/BinaryFiles/EVENTOS.data ."


    SurrealEngine *Engine = Singleton<SurrealEngine>::Instance();
    CTriggerSystem *EventSystem = Singleton<CTriggerSystem>::Instance();

    //Engine->Starto();
    //Engine->HideCursor(false);

    ObjectManager *Manager = Singleton<ObjectManager>::Instance();

    ggDynWorld *world = Singleton<ggDynWorld>::Instance();
    world->inito();


    //singleton StateMachine
    //new GameState();
    StateMachine *mainstates = Singleton<StateMachine>::Instance();
    //mainstates->AddState(new GameState());
    //mainstates->AddState(new GameState());
    //mainstates->AddState(new Game());
    mainstates->AddState(new MenuState());

    while(Engine->isWindowOpen()) {
        mainstates->ProcessStateChanges();
        mainstates->prueba();
        mainstates->GetActiveState()->Update();
    }

    Blackboard::ClearGlobalBlackboard();
    Manager->clin();
    Engine->clean();
    world->clean();
    EventSystem->clin();
    mainstates->clin();







    // PRUEBA DE LA FUNCION DIOS Y DE TRANSFORMACIONES VARIAS
    //
    //
    // #include <glm/glm.hpp>
    // #define GLM_ENABLE_EXPERIMENTAL
    // #include <glm/ext/matrix_clip_space.hpp>
    // #include <glm/ext/matrix_transform.hpp>
    // #include <glm/gtx/string_cast.hpp>
    // #include <glm/gtx/matrix_decompose.hpp>
    //
    //
    // glm::mat4 transformation(1.0f);
    // glm::vec3 scale;
    // glm::quat rotation;
    // glm::vec3 translation;
    // glm::vec3 skew;
    // glm::vec4 perspective;
    //
    // transformation = glm::translate(transformation,glm::vec3(5,5,5));
    // transformation = glm::translate(transformation,glm::vec3(1,1,1));
    // transformation = glm::rotate(transformation,90.f,glm::vec3(0,1,0));
    //
    //
    // glm::decompose(transformation, scale, rotation, translation, skew, perspective);
    //
    // std::cout << "TRANFORMATION - " << glm::to_string(transformation) << std::endl;
    // std::cout << "SCALE         - " << glm::to_string(scale) << std::endl;
    // std::cout << "ROTATION      - " << glm::to_string(rotation) << std::endl;
    // std::cout << "TRANSLATION   - " << glm::to_string(translation) << std::endl;
    // std::cout << "SKEW          - " << glm::to_string(skew) << std::endl;
    // std::cout << "PERSPECTIVE   - " << glm::to_string(perspective) << std::endl;
    //

    return 0;
}


// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
//
// #include <Util.hpp>
//
// #include <SurrealEngine/TNodo.hpp>
// #include <SurrealEngine/TEntidad.hpp>
// #include <SurrealEngine/TLuz.hpp>
// #include <SurrealEngine/TCamara.hpp>
// #include <SurrealEngine/TTransform.hpp>
// #include <SurrealEngine/ZStaticMesh.hpp>
// #include <SurrealEngine/ZMaterial.hpp>
// #include <SurrealEngine/Shader.hpp>
// #include <SurrealEngine/OpenGEnum.hpp>
// #include <SurrealEngine/AssetManager.hpp>
// #include <SurrealEngine/SurrealEngine.hpp>
//
// #include "BinaryParser.hpp"
//
//
// int main(int argc, char const *argv[]) {
//
// 	SurrealEngine* ROOT = Singleton<SurrealEngine>::Instance();
//
//
// 	auto window = ROOT->window;
// 	Shader* Def = AssetManager::getShader("Default");
// 	ZMaterial* 		MAT = AssetManager::getMaterial("Morado");
// 	MAT->attachShader(Def);
// 	MAT->addTexture("DiffuseMap",      "assets/Textures/prueba1.png",       		GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
// 	MAT->addTexture("NormalMap",       "assets/Textures/COMOUNPUTOPRO3.png",        GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
// 	MAT->addTexture("SpecularMap",     "assets/Textures/DefaultSpecular.jpeg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
//
//
// 	gg::Color color_luz;
// 	TNodo* OBJ1 = ROOT->crearMalla("assets/BinaryFiles/BinaryModels/Basura_Cajas.modelgg",glm::vec3(),glm::vec3());
// 	ROOT->bindMaterialToMesh(OBJ1, MAT);
//
// 	TNodo* LUZ = ROOT->crearLuz(color_luz,glm::vec3(5, 6, 0),glm::vec3(), Def);
// 	TNodo* OKAMERA = ROOT->crearCamara(90,0.1f,100.f,glm::vec3(5,3,6),glm::vec3(),16.f/9.f);
//
//     do{
//         ROOT->BeginDraw();
//
// 	    glfwPollEvents();
//
// 		// Prueba para las operaciones de transformacion
// 		ROOT->rotate(OBJ1,0.5,glm::vec3(0,1,0));
//
// 		ROOT->draw();
// 		//draw();
//
//         ROOT->EndDraw();
//     }while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
//
//
//     return 0;
// }
//
//
//
// void create(){
// 	auto Manager = Singleton<AssetManager>::Instance();
//
//
// 	auto HUDtext=Manager->getTexture("assets/HUD/ojetecalor.jpg",GL_TEXTURE_2D);
// 	glBindTexture(GL_TEXTURE_2D,HUDtext);
// 	glColor3f(1,1,1);
// 	glBegin(GL_QUADS);
// 	//coordenadas
// 	//glTexCoord2f(0,1);glVertex2f(0.05,0.05);
// 	//glTexCoord2f(1,1);glVertex2f(0.3,0.05);
// 	//glTexCoord2f(1,0);glVertex2f(0.3,0.15);
// 	//glTexCoord2f(0,0);glVertex2f(0.05,0.15);
//
// 		glTexCoord2f(0,1080);		glVertex2f(12,60);
// 		glTexCoord2f(1920,1080);	glVertex2f(80,60);
// 		glTexCoord2f(1920,0);		glVertex2f(80,120);
// 		glTexCoord2f(0,0);			glVertex2f(12,120);
//
// 	//glVertex2i(12,60); glVertex2i(80,60);
// 	//glVertex2i(80,120);glVertex2i(12,120);
//
// 	//glVertex2i(5,5); glVertex2i(-5,5);
// 	//glVertex2i(-5,-5);glVertex2i(5,-5);
//
// 	glEnd();
// }
// void draw(){
// 	glMatrixMode(GL_PROJECTION);
// 	glPushMatrix();
// 	glLoadIdentity();
// 	//gluOrtho2D(0,1,1,0);//screen values left rigth bottom top
// 	gluOrtho2D(0,1920,1080,0);
// 	//gluOrtho2D(-10,10,-10,10);
//
// 	glMatrixMode(GL_MODELVIEW);
// 	glPushMatrix();
// 	glLoadIdentity();
//
// 	create();
//
// 	glMatrixMode(GL_PROJECTION);
// 	glPopMatrix();
// 	glMatrixMode(GL_MODELVIEW);
// 	glPopMatrix();
// }
