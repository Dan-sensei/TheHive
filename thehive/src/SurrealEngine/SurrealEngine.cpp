#include "SurrealEngine.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

bool* SurrealEngine::KEYS = new bool[349];
bool SurrealEngine::LCLICK = false;
bool SurrealEngine::clicked = false;
int SurrealEngine::wheel;
int SurrealEngine::IdButon;

int SurrealEngine::Half_Window_Width;
int SurrealEngine::Half_Window_Height;

SurrealEngine::SurrealEngine()
:main_camera(nullptr), FPS(0), TOTALOBJECTS(0)
{
    ESCENA = new TNodo();
    Initialize();
    gestorRecursos = Singleton<AssetManager>::Instance();

    for(uint16_t i = 0; i < 349; ++i)
        SurrealEngine::KEYS[i] = false;

    CurrentDraw = &SurrealEngine::draw;
}

SurrealEngine::~SurrealEngine(){
}

void SurrealEngine::createZones(uint8_t NumberOfZones){
    NumberOfZones += 1;
    ZONES.reserve(NumberOfZones);
    ZONES.resize(NumberOfZones);
    for(uint8_t i = 0; i < NumberOfZones; ++i)
        ZONES[i] = new TNodo(ESCENA,nullptr);

}

void SurrealEngine::clean(){
    //std::cout << "DeleTAG..." << '\n';
    ZONES.clear();
    delete SurrealEngine::KEYS;
    delete ESCENA;
    glfwTerminate();
}

void SurrealEngine::DisplayFPS(){
    if(FPS_Clock.ElapsedTime().Seconds() > 1){
        std::string RasterCulling = CurrentDraw == &SurrealEngine::RasterCullingDraw ? "On" : "Off";
        std::string TEXT = "RasterCulling: " + RasterCulling + " | FPS: " + std::to_string(FPS) + "  - ObjectsDrawn: " + std::to_string(TEntidad::DRAWN) + " / " + std::to_string(TOTALOBJECTS) ;
        glfwSetWindowTitle(window, TEXT.c_str());
        FPS = 0;
        FPS_Clock.Restart();
    }
}

void SurrealEngine::Draw3DLine(const glm::vec3 &From, const glm::vec3 &To, const gg::Color &c){
    glm::mat4 MVP = ESCENA->getEntidad()->projMatrix * ESCENA->getEntidad()->viewMatrix;
    Singleton<Debug>::Instance()->DroLine(From, To, c, MVP);
}


void SurrealEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {  KEYS[key] = action; }

void SurrealEngine::resetClicked(){
    clicked=false;
}
bool SurrealEngine::isLClicked(){
    return clicked;
}
void SurrealEngine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        clicked=true;
        LCLICK = true;
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        LCLICK = false;
    }
}

void SurrealEngine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    wheel = yoffset;
}

void SurrealEngine::PollEvents()     {   glfwPollEvents();  }

void SurrealEngine::getCursorPosition(double &posX, double &posY) {  glfwGetCursorPos(window, &posX, &posY); }

TNodo* SurrealEngine::crearCamara(const float& _fov, const float& _near, const float& _far, const glm::vec3& pos, const glm::vec3& rot, const float& _ppv){
    TCamara* C = new TCamara(_fov,_near,_far);
    ZStaticMesh::setMainCamera(C);
    C->setPerspectiva(_ppv);

    TNodo* Cam = new TNodo(bindTransform(pos,rot),C);

    main_camera = Cam;
    cam_ = C;
    return Cam;
}

TNodo* SurrealEngine::crearLuz(gg::Color &_color, const glm::vec3& pos, const glm::vec3& rot, Shader* sh){
    TLuz* L = new TLuz(_color,sh);
    TNodo* Luz = new TNodo(bindTransform(pos,rot),L);

    return Luz;
}

TNodo* SurrealEngine::crearMalla(const char* _path, const glm::vec3& pos, const glm::vec3& rot, int8_t map_zone){
    ZStaticMesh* M = new ZStaticMesh();
    M->load(_path);

    TNodo* Malla = new TNodo(bindTransform(pos,rot,map_zone),M);
    ++TOTALOBJECTS;
    return Malla;
}

TNodo* SurrealEngine::bindTransform(const glm::vec3& pos, const glm::vec3& rot, int8_t map_zone){
    TTransform* Rotate = new TTransform();
    TTransform* Translate = new TTransform();

    Rotate->setRotation(rot);
    Translate->setPosition(pos);

    TNodo* PADRE = ZONES[map_zone];

    TNodo* NodoRot = new TNodo(PADRE,Rotate);
    TNodo* NodoTrans = new TNodo(NodoRot,Translate);

    return NodoTrans;
}


bool SurrealEngine::bindMaterialToMesh(TNodo *_mesh, ZMaterial* Material){
    ZStaticMesh*    O   = static_cast<ZStaticMesh*>(_mesh->getEntidad());
	O->assignMaterial(Material);

    return true;
}

void SurrealEngine::BeginDraw(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void SurrealEngine::SwitchRasterCulling(){
    ESCENA->drawRoot(&TNodo::SwitchRasterCulling);

    if(CurrentDraw == &SurrealEngine::RasterCullingDraw){
        CurrentDraw = &SurrealEngine::draw;
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
    }
    else{
        CurrentDraw = &SurrealEngine::RasterCullingDraw;
    }
}

void SurrealEngine::drawScene(){
    (this->*CurrentDraw)();
}


void SurrealEngine::draw(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    ++FPS;
    TEntidad::DRAWN = 0;

    glDepthFunc(GL_LESS);
    ESCENA->drawRoot(&TNodo::draw);
}

void SurrealEngine::RasterCullingDraw(){
    ++FPS;

    TEntidad::DRAWN = 0;

    glDepthMask(GL_TRUE);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glColorMask(0,0,0,0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    AssetManager::getShader("Z-Prepass")->Bind();
    ESCENA->drawRoot(&TNodo::draw);

    AssetManager::getShader("Default")->Bind();
    TEntidad::DRAWN = 0;
    glDepthMask(GL_FALSE);
    glColorMask(1,1,1,1);
    glDepthFunc(GL_EQUAL);

    ESCENA->drawRoot(&TNodo::JustRender);

}



void SurrealEngine::EndDraw(){
    glfwSwapBuffers(window);
}

void SurrealEngine::move(TNodo *_node, const glm::vec3& _offpos){
    static_cast<TTransform*>(_node->getPadre()->getEntidad())->translate(_offpos);
}

void SurrealEngine::rotate(TNodo *_node,const float& _angle,const glm::vec3& _offrot){
    static_cast<TTransform*>(_node->getPadre()->getPadre()->getEntidad())->rotate(_angle,_offrot);
}


void SurrealEngine::setPosition(TNodo* _node, const glm::vec3& _offpos){
    static_cast<TTransform*>(_node->getPadre()->getEntidad())->setPosition(_offpos);
}

void SurrealEngine::setRotation(TNodo* _node,const glm::vec3& _offrot){
    static_cast<TTransform*>(_node->getPadre()->getPadre()->getEntidad())->setRotation(_offrot);
}
glm::vec3 SurrealEngine::vectorUp(){
    auto v=ESCENA->getEntidad()->viewMatrix;
    return glm::vec3(v[0][1], v[1][1], v[2][1]);
}

glm::vec3 SurrealEngine::vectorRigth(){
    auto v=ESCENA->getEntidad()->viewMatrix;
    return glm::vec3(v[0][0], v[1][0], v[2][0]);
}
glm::mat4  SurrealEngine::getMVP(){
    return  ESCENA->getEntidad()->projMatrix * ESCENA->getEntidad()->viewMatrix * ESCENA->getEntidad()->modelMatrix;
}
glm::mat4  SurrealEngine::getVP(){
    return  ESCENA->getEntidad()->projMatrix * ESCENA->getEntidad()->viewMatrix;
}
glm::mat4  SurrealEngine::getV(){
    return  ESCENA->getEntidad()->viewMatrix;
}
glm::mat4  SurrealEngine::getM(){
    return ESCENA->getEntidad()->modelMatrix;
}
TCamara* SurrealEngine::getCam(){
    return cam_;
}
void SurrealEngine::PointAt(TNodo *_node, const glm::vec3& _offpos){
    auto trans =static_cast<TTransform*>(_node->getPadre()->getEntidad());
    auto dir=glm::normalize(glm::vec3(_offpos.x,_offpos.y,_offpos.z)-trans->getDatos());

    auto x=glm::degrees(glm::acos(dir.x));
    auto y=glm::degrees(glm::acos(dir.y));
    auto z=glm::degrees(glm::acos(dir.z));
    //la condicion puede invertirse
    if(dir.x<0){
        x=360-x;
    }
    if(dir.y<0){
        y=360-y;
    }
    if(dir.z<0){
        z=360-z;
    }
    setRotation(_node, glm::vec3(x,y,z));

}

void SurrealEngine::HideCursor(bool t){
    if(t){
        glfwSetInputMode(window,  GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }else{
        glfwSetInputMode(window,  GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
void SurrealEngine::close(){
    glfwSetWindowShouldClose(window, GL_TRUE);
}
bool SurrealEngine::Initialize(){
	//INICIALIZAMOS GLFW
	if( !glfwInit() ){
	    //fprintf( stderr, "Error al inicializar GLFW\n" );
	    return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Queremos OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para hacer feliz a MacOS ; Aunque no debería ser necesaria
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    float ancho = mode->width;
    float alto = mode->height;

	window = glfwCreateWindow( ancho, alto, "The Hive - ALPHA", NULL, NULL);
	if( window == NULL ){
	    //fprintf( stderr, "Falla al abrir una ventana GLFW. Si usted tiene una GPU Intel, está no es compatible con 3.3. Intente con la versión 2.1 de los tutoriales.\n" );
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

    glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // glFrontFace(GL_CCW);
    // glEnable(GL_CULL_FACE);
    // glCullFace (GL_BACK);


    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window,  GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    Half_Window_Width = ancho/2;
    Half_Window_Height = alto/2;

	return true;
}

void SurrealEngine::deleteLeafNode(TNodo *node){
    TNodo *tmp = node->getPadre()->getPadre();
    TNodo *FATHER = tmp->getPadre();
    FATHER->remHijo(tmp);
}

void SurrealEngine::SetMapZoneVisibility(const int8_t &zone,const bool &flag){
    ZONES[zone]->setVisibility(flag);
}
