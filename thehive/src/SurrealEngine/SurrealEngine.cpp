#include "SurrealEngine.hpp"
#include <glm/gtx/matrix_decompose.hpp>

bool* SurrealEngine::KEYS = new bool[349];
bool SurrealEngine::LCLICK = false;
int SurrealEngine::wheel;
int SurrealEngine::IdButon;

int SurrealEngine::Half_Window_Width;
int SurrealEngine::Half_Window_Height;

SurrealEngine::SurrealEngine()
:main_camera(nullptr), FPS(0)
{
    ESCENA = new TNodo();
    Initialize();
    gestorRecursos = Singleton<AssetManager>::Instance();

    for(uint16_t i = 0; i < 349; ++i)
        SurrealEngine::KEYS[i] = false;


}

SurrealEngine::~SurrealEngine(){
}

void SurrealEngine::clean(){
    std::cout << "DeleTAG..." << '\n';
    delete SurrealEngine::KEYS;
    delete ESCENA;
    glfwTerminate();
}

void SurrealEngine::DisplayFPS(){
    if(FPS_Clock.ElapsedTime().Seconds() > 1){
        std::string TEXT = "The Hive - ALPHA FPS: " + std::to_string(FPS);
        glfwSetWindowTitle(window, TEXT.c_str());
        FPS = 0;
        FPS_Clock.Restart();
    }
}

void SurrealEngine::Draw3DLine(const glm::vec3 &From, const glm::vec3 &To, const gg::Color &c){
    glm::mat4 MVP = ESCENA->getEntidad()->projMatrix * ESCENA->getEntidad()->viewMatrix * ESCENA->getEntidad()->modelMatrix;
    Singleton<Debug>::Instance()->DroLine(From, To, c, MVP);
}


void SurrealEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {  KEYS[key] = action; }

void SurrealEngine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        LCLICK = true;
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        LCLICK = false;
}

void SurrealEngine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    wheel = yoffset;
}

void SurrealEngine::PollEvents()     {   glfwPollEvents();  }

void SurrealEngine::getCursorPosition(double &posX, double &posY) {  glfwGetCursorPos(window, &posX, &posY); }

TNodo* SurrealEngine::crearCamara(const float& _fov, const float& _near, const float& _far, const glm::vec3& pos, const glm::vec3& rot, const float& _ppv){
    TCamara* C = new TCamara(_fov,_near,_far);
    C->setPerspectiva(_ppv);

    TNodo* Cam = new TNodo(bindTransform(pos,rot),C);

    main_camera = Cam;
    cam_ = C;
    return Cam;
}

void SurrealEngine::print(){

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;

    auto mat = main_camera->getPadre()->getEntidad()->modelMatrix;

    glm::decompose(static_cast<TTransform*>(main_camera->getPadre()->getEntidad())->modelMatrix, scale, rotation, translation, skew, perspective);
}

TNodo* SurrealEngine::crearLuz(gg::Color &_color, const glm::vec3& pos, const glm::vec3& rot, Shader* sh){
    TLuz* L = new TLuz(_color,sh);
    TNodo* Luz = new TNodo(bindTransform(pos,rot),L);

    return Luz;
}

TNodo* SurrealEngine::crearMalla(const char* _path, const glm::vec3& pos, const glm::vec3& rot){
    ZStaticMesh* M = new ZStaticMesh();
    M->load(_path);

    TNodo* Malla = new TNodo(bindTransform(pos,rot),M);

    return Malla;
}

TNodo* SurrealEngine::bindTransform(const glm::vec3& pos, const glm::vec3& rot){
    TTransform* Rotate = new TTransform();
    TTransform* Translate = new TTransform();

    Rotate->setRotation(rot);
    Translate->setPosition(pos);

    TNodo* NodoRot = new TNodo(ESCENA,Rotate);
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

void SurrealEngine::draw(){
    ++FPS;
    ESCENA->drawRoot();
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

    float ancho = 1920;
    float alto = 1080;

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

	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glCullFace (GL_BACK);
    glEnable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window,  GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

    Half_Window_Width = ancho/2;
    Half_Window_Height = alto/2;

	return true;
}
