#include "TMotorTAG.hpp"
#include <glm/gtx/matrix_decompose.hpp>

bool* TMotorTAG::KEYS = new bool[349];
bool TMotorTAG::LCLICK = false;
int TMotorTAG::wheel;
int TMotorTAG::IdButon;

int TMotorTAG::Half_Window_Width;
int TMotorTAG::Half_Window_Height;

TMotorTAG::TMotorTAG()
:main_camera(nullptr)
{
    ESCENA = new TNodo();
    Initialize();
    gestorRecursos = Singleton<AssetManager>::Instance();

    uint16_t i = 349;
    while(i--) TMotorTAG::KEYS[i] = false;
}

TMotorTAG::~TMotorTAG(){
}

void TMotorTAG::clean(){
    std::cout << "DeleTAG..." << '\n';
    delete ESCENA;
    glfwTerminate();
    delete TMotorTAG::KEYS;
}

void TMotorTAG::Draw3DLine(const gg::Vector3f &From, const gg::Vector3f &To, const gg::Color &c){

}

void TMotorTAG::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {  KEYS[key] = action; }

void TMotorTAG::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        LCLICK = true;
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        LCLICK = false;
}

void TMotorTAG::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    wheel = yoffset;
}

void TMotorTAG::PollEvents()     {   glfwPollEvents();  }

void TMotorTAG::getCursorPosition(double &posX, double &posY) {  glfwGetCursorPos(window, &posX, &posY); }

TNodo* TMotorTAG::crearCamara(const float& _fov, const float& _near, const float& _far, const gg::Vector3f& pos, const gg::Vector3f& rot, const float& _ppv){
    TCamara* C = new TCamara(_fov,_near,_far);
    C->setPerspectiva(_ppv);

    TNodo* Cam = new TNodo(bindTransform(pos,rot),C);

    main_camera = Cam;
    cam_ = C;
    return Cam;
}

void TMotorTAG::print(){

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;

    auto mat = main_camera->getPadre()->getEntidad()->modelMatrix;

    glm::decompose(static_cast<TTransform*>(main_camera->getPadre()->getEntidad())->modelMatrix, scale, rotation, translation, skew, perspective);
}

TNodo* TMotorTAG::crearLuz(gg::Color &_color, const gg::Vector3f& pos, const gg::Vector3f& rot, Shader* sh){
    TLuz* L = new TLuz(_color,sh);
    TNodo* Luz = new TNodo(bindTransform(pos,rot),L);

    return Luz;
}

TNodo* TMotorTAG::crearMalla(const char* _path, const gg::Vector3f& pos, const gg::Vector3f& rot){
    ZStaticMesh* M = new ZStaticMesh();
    M->load(_path);

    TNodo* Malla = new TNodo(bindTransform(pos,rot),M);

    return Malla;
}

TNodo* TMotorTAG::bindTransform(const gg::Vector3f& pos, const gg::Vector3f& rot){
    TTransform* Rotate = new TTransform();
    TTransform* Translate = new TTransform();

    Rotate->setRotation(rot);
    Translate->setPosition(pos);

    TNodo* NodoRot = new TNodo(ESCENA,Rotate);
    TNodo* NodoTrans = new TNodo(NodoRot,Translate);

    return NodoTrans;
}


bool TMotorTAG::bindMaterialToMesh(TNodo *_mesh, ZMaterial* Material){
    ZStaticMesh*    O   = static_cast<ZStaticMesh*>(_mesh->getEntidad());
	O->assignMaterial(Material);

    return true;
}

void TMotorTAG::BeginDraw(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void TMotorTAG::draw(){
    ESCENA->drawRoot();
}

void TMotorTAG::EndDraw(){
    glfwSwapBuffers(window);
}

void TMotorTAG::move(TNodo *_node, const gg::Vector3f& _offpos){
    static_cast<TTransform*>(_node->getPadre()->getEntidad())->translate(_offpos);
}

void TMotorTAG::rotate(TNodo *_node,const float& _angle,const gg::Vector3f& _offrot){
    static_cast<TTransform*>(_node->getPadre()->getPadre()->getEntidad())->rotate(_angle,_offrot);
}


void TMotorTAG::setPosition(TNodo* _node, const gg::Vector3f& _offpos){
    static_cast<TTransform*>(_node->getPadre()->getEntidad())->setPosition(_offpos);
}

void TMotorTAG::setRotation(TNodo* _node,const gg::Vector3f& _offrot){
    static_cast<TTransform*>(_node->getPadre()->getPadre()->getEntidad())->setRotation(_offrot);
}
void TMotorTAG::PointAt(TNodo *_node, const gg::Vector3f& _offpos){
    auto trans =static_cast<TTransform*>(_node->getPadre()->getEntidad());
    auto dir=glm::normalize(glm::vec3(_offpos.X,_offpos.Y,_offpos.Z)-trans->getDatos());

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
    setRotation(_node, gg::Vector3f(x,y,z));

}


bool TMotorTAG::Initialize(){
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
    glfwSetInputMode(window, GLFW_CURSOR_DISABLED, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

    Half_Window_Width = ancho/2;
    Half_Window_Height = alto/2;

	return true;
}
