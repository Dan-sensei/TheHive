#include "Omicron.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>
#include <Omicron/FX/ParticleSystem.hpp>
#include <Singleton.hpp>
#include <Omicron/CORE/BVH_ROOT_Node.hpp>
#include <Omicron/CORE/Leaf.hpp>
#include <Omicron/CORE/FrustrumLeaf.hpp>

bool* Omicron::KEYS = new bool[349];
bool Omicron::LCLICK = false;
bool Omicron::RCLICK = false;
int Omicron::wheel;
int Omicron::IdButon;

Omicron::Omicron()
:MainCamera(nullptr), MainCameraNode(nullptr), FPS(0), _DeferredShading(), WINDOW_WIDTH(0), WINDOW_HEIGHT(0)
{
    ESCENA = new StandardNode();
    Initialize();

    OKAMERAS_LAYER  = new StandardNode(ESCENA, nullptr);
      LIGHTS_LAYER  = new StandardNode(ESCENA, nullptr);
     BUFFERS_LAYER  = new StandardNode(ESCENA, nullptr);
     FORWARD_LAYER  = new StandardNode(ESCENA, nullptr);

    for(uint16_t i = 0; i < 349; ++i)
        Omicron::KEYS[i] = false;
}

Omicron::~Omicron(){}

void Omicron::createZones(uint8_t NumberOfZones){
    NumberOfZones += 1;
    ZONES.reserve(NumberOfZones);
    ZONES.resize(NumberOfZones);
    for(uint8_t i = 0; i < NumberOfZones; ++i)
        ZONES[i] = new StandardNode(BUFFERS_LAYER, nullptr);
}

void Omicron::resetSceneGraph() {
    ZONES.clear();
    delete ESCENA;

    ESCENA = new StandardNode();
    OKAMERAS_LAYER  = new StandardNode(ESCENA, nullptr);
      LIGHTS_LAYER  = new StandardNode(ESCENA, nullptr);
     BUFFERS_LAYER  = new StandardNode(ESCENA, nullptr);
     FORWARD_LAYER  = new StandardNode(ESCENA, nullptr);
}


void Omicron::clean(){
    //std::cout << "DeleTAG..." << '\n';
    ZONES.clear();
    delete[] Omicron::KEYS;
    delete ESCENA;
    glfwTerminate();
}

void Omicron::DisplayFPS(){
    if(FPS_Clock.ElapsedTime().Seconds() > 1){
        // std::string TEXT = "The Hive - ALPHA FPS: " + std::to_string(FPS) + "DRAWN OBJECTS: " + std::to_string(DRAW_OBJECTS);
        // glfwSetWindowTitle(window, TEXT.c_str());
        //std::cout << "FPS: " << FPS << '\n';
        FPS = 0;
        FPS_Clock.Restart();
    }
}

void Omicron::Draw3DLine(const glm::vec3 &From, const glm::vec3 &To, const gg::Color &c){
    glm::mat4 MVP = ESCENA->getEntidad()->projMatrix * ESCENA->getEntidad()->viewMatrix;
    Singleton<Debug>::Instance()->DroLine(From, To, c, MVP);
}


void Omicron::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS)
        KEYS[key] = true;
    else if(action == GLFW_RELEASE)
        KEYS[key] = false;
}

// void Omicron::resetClicked(){
//     clicked=false;
// }
// bool Omicron::isLClicked(){
//     return clicked;
// }

void Omicron::resetClickVariable(){
    LCLICK = false;
}

void Omicron::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        LCLICK = true;
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        LCLICK = false;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        RCLICK = true;
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
        RCLICK = false;
    }
}

void Omicron::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    wheel = yoffset;
}

void Omicron::PollEvents()     {   glfwPollEvents();  }

void Omicron::getCursorPosition(double &posX, double &posY) {  glfwGetCursorPos(window, &posX, &posY); }

StandardNode* Omicron::crearCamara(const float& _fov, const float& _near, const float& _far, const glm::vec3& pos, const glm::quat& rot, const float& _ppv){
    TCamara* C = new TCamara(_fov,_near,_far);
    C->setPerspectiva(_ppv);

    StandardNode* Cam = new StandardNode(bindTransform(pos,rot, OKAMERAS_LAYER),C);
    MainCamera = C;
    MainCameraNode = Cam;
    ZMesh::CameraPosition = MainCamera->getPositionPtr();
    BVH_ROOT_Node::CameraPosition = MainCamera->getPositionPtr();
    FrustrumLeaf::CameraPosition = MainCamera->getPositionPtr();
    return Cam;
}

StandardNode* Omicron::crearLuz(gg::Color &_color, const glm::vec3& pos, const glm::vec3& rot, Shader* sh){
    TLuz* L = new TLuz(_color,sh);
    StandardNode* Luz = new StandardNode(bindTransform(pos,rot, LIGHTS_LAYER),L);

    return Luz;
}

ZNode* Omicron::createStaticMesh(StandardNode* FATHER, const char* _path, const glm::vec3& pos, const glm::quat &Rotation){

    TTransform T_Position;
    TTransform T_Rotation;
    T_Position.setPosition(pos);
    T_Rotation.setRotation(Rotation);

    glm::mat4 Model = T_Position.matrix * T_Rotation.matrix;

    ZStaticMesh* M = new ZStaticMesh(Model);
    M->load(_path);

    Leaf* Malla = new Leaf(FATHER, M);

    return Malla;
}

ZNode* Omicron::createMovableMesh(StandardNode* FATHER, const char* _path, const glm::vec3& pos, const glm::quat &Rotation){
    ZMovableMesh* M = new ZMovableMesh();
    M->load(_path);

    Leaf* Malla = new Leaf(bindTransform(pos,Rotation, FATHER), M);

    return Malla;
}

ZNode* Omicron::CreateDynamicMesh(StandardNode* FATHER, const glm::vec3& Position, const glm::quat& Rotation){
    ZDynamicMesh* M = new ZDynamicMesh();

    Leaf* Malla = new Leaf(bindTransform(Position, Rotation, FATHER), M);

    return Malla;
}

ParticleSystem* Omicron::CreateParticleSystem(StandardNode* FATHER, const ParticleSystem_Data &Data){
    ParticleSystem* P = new ParticleSystem();

    P->Init(Data.MaxParticles);
    P->setGenerationTime(Data.SpawnTime);
    P->setTexture(Data.Texture);
    P->setParticleLifeTime(Data.ParticleLifeTime);
    P->setPosition(Data.Position);
    P->setSize(Data.Size);

    Leaf* ParticleNode = new Leaf(FATHER, P);

    return P;
}

StandardNode* Omicron::bindTransform(const glm::vec3& pos, const glm::quat& rot, StandardNode* FATHER){
    TTransform* Rotate = new TTransform();
    TTransform* Translate = new TTransform();

    Rotate->setRotation(rot);
    Translate->setPosition(pos);

    StandardNode* NodoRot = new StandardNode(FATHER, Rotate);
    StandardNode* NodoTrans = new StandardNode(NodoRot, Translate);

    return NodoTrans;
}


bool Omicron::bindMaterialToMesh(ZNode *_mesh, ZMaterial* Material){
    ZStaticMesh*    O   = static_cast<ZStaticMesh*>(_mesh->getEntidad());
	O->assignMaterial(Material);

    return true;
}

bool Omicron::bindMaterialToDynamicMesh(ZNode *_mesh, ZMaterial* Material){
    ZDynamicMesh*    O   = static_cast<ZDynamicMesh*>(_mesh->getEntidad());
	O->assignMaterial(Material);

    return true;
}

void Omicron::BeginDraw(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Omicron::draw(){
    ++FPS;
    DRAW_OBJECTS = 0;
    glDisable( GL_BLEND );
    //
    // Bindeamos el shader que recibe la info de luces y cámara
    _DeferredShading.Bind_D_Shader();
    ESCENA->ROOT_OkameraUpdate();   // Le enviamos la info
    ESCENA->ROOT_LightsUpdate();

    // Ahora bindeamos nuestro G-Búffer y renderizamos a las texturas
    _DeferredShading.Bind_G_Buffer();
    glViewport(0,0, INTERNAL_BUFFER_WIDTH, INTERNAL_BUFFER_HEIGHT);
    ESCENA->ROOT_ObjectsUpdate();
    _DeferredShading.DrawQuad();
    glUniform1f(7, FPS/60.f);
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    _DeferredShading.DrawPostProcessing();

    glEnable (GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    ESCENA->ROOT_ForwardRendering();
    glDepthMask(GL_TRUE);
}

void Omicron::drawHUD(){
    hud->draw();
}

void Omicron::EndDraw(){
    glfwSwapBuffers(window);
}

void Omicron::setPosition(ZNode* _node, const glm::vec3& _offpos){
    static_cast<TTransform*>(_node->getPadre()->getEntidad())->setPosition(_offpos);
}

void Omicron::setRotation(ZNode* _node,const glm::quat& _offrot){
    static_cast<TTransform*>(_node->getPadre()->getPadre()->getEntidad())->setRotation(_offrot);
}
glm::vec3 Omicron::vectorUp(){
    auto v=ESCENA->getEntidad()->viewMatrix;
    return glm::vec3(v[0][1], v[1][1], v[2][1]);
}

glm::vec3 Omicron::vectorRigth(){
    auto v=ESCENA->getEntidad()->viewMatrix;
    return glm::vec3(v[0][0], v[1][0], v[2][0]);
}

glm::mat4  Omicron::getMVP(){
    return  ESCENA->getEntidad()->projMatrix * ESCENA->getEntidad()->viewMatrix * ESCENA->getEntidad()->modelMatrix;
}
glm::mat4  Omicron::getVP(){
    return  ESCENA->getEntidad()->projMatrix * ESCENA->getEntidad()->viewMatrix;
}
glm::mat4  Omicron::getV(){
    return  ESCENA->getEntidad()->viewMatrix;
}
glm::mat4  Omicron::getM(){
    return ESCENA->getEntidad()->modelMatrix;
}

// void Omicron::PointAt(TNodo *_node, const glm::vec3& _offpos){
//     auto trans =static_cast<TTransform*>(_node->getPadre()->getEntidad());
//     auto dir=glm::normalize(glm::vec3(_offpos.x,_offpos.y,_offpos.z)-trans->getDatos());
//
//     auto x=glm::degrees(glm::acos(dir.x));
//     auto y=glm::degrees(glm::acos(dir.y));
//     auto z=glm::degrees(glm::acos(dir.z));
//     //la condicion puede invertirse
//     if(dir.x<0){
//         x=360-x;
//     }
//     if(dir.y<0){
//         y=360-y;
//     }
//     if(dir.z<0){
//         z=360-z;
//     }
//     setRotation(_node, glm::vec3(x,y,z));
// }


void Omicron::HideCursor(bool t){
    if(t){
        glfwSetInputMode(window,  GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }else{
        glfwSetInputMode(window,  GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Omicron::close(){
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Omicron::DrawZero(){
    ZONES[1]->drawRoot();
    ZONES[4]->drawRoot();
    ZONES[6]->drawRoot();
}


bool Omicron::Initialize(){
	//INICIALIZAMOS GLFW
	if( !glfwInit() ){
	    //fprintf( stderr, "Error al inicializar GLFW\n" );
	    return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    WINDOW_WIDTH = mode->width;
    WINDOW_HEIGHT = mode->height;
    INTERNAL_BUFFER_WIDTH = 1280;
    INTERNAL_BUFFER_HEIGHT = 720;

	window = glfwCreateWindow(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT), "The Hive - ALPHA",nullptr, NULL);
	if( window == NULL ){
	    glfwTerminate();
	    return false;
	}


    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

	glfwMakeContextCurrent(window);
	glewExperimental=true;
	if (glewInit() != GLEW_OK) {
	    //fprintf(stderr, "Falló al inicializar GLEW\n");
	    return false;
	}

    _DeferredShading.init(INTERNAL_BUFFER_WIDTH, INTERNAL_BUFFER_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

    gestorRecursos = Singleton<AssetManager>::Instance();
    hud = Singleton<HUD>::Instance();
    hud->initHUD(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        gestorRecursos->getTexture("assets/HUD/NUEVO/plantilla.png",4),
        gestorRecursos->getShader("HUD")
    );

    glDepthRange(0.f,1.f);

	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace (GL_BACK);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window,      GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glClearColor(0, 0, 0, 1.0f);

	return true;
}

void Omicron::resizeFrameBuffers(uint16_t FRAMEBUFFER_WIDTH, uint16_t FRAMEBUFFER_HEIGHT) {
    INTERNAL_BUFFER_WIDTH = FRAMEBUFFER_WIDTH;
    INTERNAL_BUFFER_HEIGHT = FRAMEBUFFER_HEIGHT;
    _DeferredShading.resizeFrameBuffers(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
}

void Omicron::deleteLeafNode(ZNode *node){
    ZNode *tmp = node->getPadre()->getPadre();
    StandardNode *FATHER = static_cast<StandardNode*>(tmp->getPadre());
    FATHER->remHijo(tmp);
}

void Omicron::SetMapZoneVisibility(const int8_t &zone,const bool &flag){
    ZONES[zone]->setVisibility(flag);
}
