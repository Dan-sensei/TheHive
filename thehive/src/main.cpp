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

#include "GameEngine/ScreenConsole.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>

#include "States/StateMachine.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
/*
int main(int argc, char const *argv[]) {
    GameEngine *Engine = Singleton<GameEngine>::Instance();
    CTriggerSystem *EventSystem = Singleton<CTriggerSystem>::Instance();

    Engine->Starto();
    //Engine->HideCursor(false);

    ObjectManager *Manager = Singleton<ObjectManager>::Instance();

    ggDynWorld *world = Singleton<ggDynWorld>::Instance();
    world->inito();


    //singleton StateMachine
    //new GameState();
    StateMachine *mainstates = Singleton<StateMachine>::Instance();
    //mainstates->AddState(new GameState());
    //mainstates->AddState(new GameState());
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
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Util.hpp>

#include <SurrealEngine/TNodo.hpp>
#include <SurrealEngine/TEntidad.hpp>
#include <SurrealEngine/TLuz.hpp>
#include <SurrealEngine/TCamara.hpp>
#include <SurrealEngine/TTransform.hpp>
#include <SurrealEngine/ZStaticMesh.hpp>
#include <SurrealEngine/ZMaterial.hpp>
#include <SurrealEngine/Shader.hpp>
#include <SurrealEngine/OpenGEnum.hpp>
#include <SurrealEngine/AssetManager.hpp>

#include "BinaryParser.hpp"

GLFWwindow* window;
int initGL(){
	//INICIALIZAMOS GLFW
	if( !glfwInit() ){
	    fprintf( stderr, "Error al inicializar GLFW\n" );
	    return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Queremos OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para hacer feliz a MacOS ; Aunque no debería ser necesaria
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL

	//CREAMOS UNA VENTANA Y SU CONTEXTO EN OPENGL
	//GLFW
	window = glfwCreateWindow( 1920, 1080, "The Hive - ALPHA", NULL, NULL);
	if( window == NULL ){
	    fprintf( stderr, "Falla al abrir una ventana GLFW. Si usted tiene una GPU Intel, está no es compatible con 3.3. Intente con la versión 2.1 de los tutoriales.\n" );
	    glfwTerminate();
	    return -1;
	}

	//INICIALIZAR GLEW
	glfwMakeContextCurrent(window); // Inicializar GLEW
	glewExperimental=true; // Se necesita en el perfil de base.
	if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Falló al inicializar GLEW\n");
	    return -1;
	}

	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	return 0;
}

int main(int argc, char const *argv[]) {

	// BinaryParser::test();
	// return 0;

	initGL();

	Singleton<AssetManager>::Instance();

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.1f, 0.0f);



	// Shader molon
	Shader* DefaultShader = AssetManager::getShader("Default");

    TNodo* Escena = new TNodo();

	// Luz de prueba
	// Esta comentado porque aun no va bien
	// (Mirar bucle principal)
	// TTransform* R_LUZ 	= new TTransform();
	// TTransform* T_LUZ 	= new TTransform();
	// TLuz*		LUZ 	= new TLuz(sh);
	// T_LUZ->translate(gg::Vector3f(0,10,0));
	//
	// TNodo* 		RotaLuz 	= new TNodo(Escena,R_LUZ);
	// TNodo* 		TransLuz 	= new TNodo(RotaLuz,T_LUZ);
	// TNodo* 		NodoLuz 	= new TNodo(TransLuz,LUZ);

	// Creacion de la camara
    TTransform* R_CAM 	= new TTransform();
	TTransform* T_CAM 	= new TTransform();
	TCamara* 	CAM 	= new TCamara(80,0.1f,100.f);
	T_CAM->translate(gg::Vector3f(5,3,6));
	CAM->setPerspectiva(16.f/9.f);

	TNodo* RotaCam 	= new TNodo(Escena,R_CAM);
    TNodo* TransCam = new TNodo(RotaCam,T_CAM);
	TNodo* NodoCam 	= new TNodo(TransCam,CAM);

	// Una puta obra de arte
    TTransform* 	R_O = new TTransform();
	TTransform* 	T_O = new TTransform();
	ZStaticMesh* 	O 	= new ZStaticMesh();
	O->load("assets/BinaryFiles/BinaryModels/Cube.modelgg");


	ZMaterial* 		MAT = AssetManager::getMaterial("Morado");
	MAT->attachShader(DefaultShader);
	MAT->addTexture("DiffuseMap", 	"assets/Textures/prueba1.png",    			GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
	MAT->addTexture("NormalMap", 	"assets/Textures/COMOUNPUTOPRO3.png",       GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
	MAT->addTexture("SpecularMap", 	"assets/Textures/DefaultSpecular.jpeg",   	GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);
	O->assignMaterial(MAT);

	TNodo* RotaObj 	= new TNodo(Escena, R_O);
    TNodo* TransObj = new TNodo(RotaObj, T_O);
	TNodo* MeshObj	= new TNodo(TransObj, O);

	TTransform* 	R_O2 = new TTransform();
	TTransform* 	T_O2 = new TTransform();
	ZStaticMesh* 	O2 	= new ZStaticMesh();
	O2->load("assets/BinaryFiles/BinaryModels/Cube.modelgg");
	O2->assignMaterial(MAT);

	TNodo* RotaObj2 	= new TNodo(Escena, R_O2);
    TNodo* TransObj2 = new TNodo(RotaObj2, T_O2);
	TNodo* MeshObj2	= new TNodo(TransObj2, O2);

	R_O2->translate(gg::Vector3f(10, 0, 0));
	DefaultShader->Bind();

	GLuint LIGHT = DefaultShader->getUniformLocation("LightPosition_worldspace");
	GLuint OKAMERA = DefaultShader->getUniformLocation("CameraPos");
	glUniform3f(LIGHT, 5, 6, 0);
	glUniform3f(OKAMERA, 5,3,6);


    do{
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	    glfwPollEvents();


		// Prueba para las operaciones de transformacion
		R_O->rotate(0.5,gg::Vector3f(0,1,0));
		R_O2->rotate(0.6,gg::Vector3f(0,1,0));

		Escena->drawRoot();

        glfwSwapBuffers(window);
    }while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    delete Escena;

    return 0;
}
