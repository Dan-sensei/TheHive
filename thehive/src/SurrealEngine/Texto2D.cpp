#include "Texto2D.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>
#include "Singleton.hpp"
#include "Letra2DManager.hpp"


/*

altura 64
1400X800
minusculas
inicio_y minusculas 64

letra   X       W
a       1       32
b       47      33
c       94      30
d       138     34
e       185     30
f       225     28
g       261     34
h       309     32
i       356     19
j       392     26
k       430     37
l       477     17
m       509     47
n       571     32
o       619     31
p       662     34
q       712     32
r       757     25
s       793     29
t       836     21
u       871     33
v       918     36
w       966     51
x       1024    40
y       1075    33
z       1120    33



MAYUSCULAS
inicio_y MAYUSCULAS 198


letra   X       W

A       0       42
B       56      41
C       111     40
D       162     42
E       217     41
F       270     41
G       322     40
H       375     46
I       433     20
J       465     41
K       518     48
L       573     34
M       622     52
N       686     46
O       745     43
P       801     42
Q       856     43
R       913     42
S       967     40
T       1022    40
U       1073    43
V       1132    46
W       1188    62
X       1255    52
Y       1319    46

inicio_y Z 266

Z      0        43




*/

// glm::mat4 TEntidad::modelMatrix;
// glm::mat4 TEntidad::viewMatrix;
// glm::mat4 TEntidad::projMatrix;
float Texto2D::getX(){
    return X;
}
float Texto2D::getW(){
    return W;
}
float Texto2D::getY(){
    return Y;
}
float Texto2D::getH(){
    return H;
}

float Texto2D::ChangeChar(float x,float y,char cha){
    float _x,_y,_w,_h;
    float T_x,T_y,T_w,T_h;
    _x=x*2.0-1;
    _y=(y*-2.0)+1;
    auto letra=Manager->getChar(cha);
    letra.resize(tamanyo);
    _w=(x+letra.getW())*2.0-1;
    _h=((y+letra.getH())*-2.0)+1;

        T_x=letra.getTX();
        T_w=letra.getTW();

        T_y=letra.getTY();
        T_h=letra.getTH();
        float vertices[] = {
        //  Position      Color             Texcoords
            _x,  _y,  T_x, T_y, // Top-left
            _w,  _y,  T_w, T_y, // Top-right
            _w,  _h,  T_w, T_h, // Bottom-right
            _x,  _h,  T_x, T_h  // Bottom-left
        };
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
        return letra.getW();
}
Texto2D::Texto2D(float x,float y,float w,float h,const std::string &Palabra):Texto2D(x,y,w,h,Palabra,0.05){

}
Texto2D::Texto2D(float x,float y,float w,float h,const std::string &Palabra,float tam)
:VAO(0),VBO(0),EBO(0),color(1,1,1,1),textureID(0),separacion(0.05),tamanyo(tam),palabra(Palabra)
{
    auto sh=Singleton<AssetManager>::Instance()->getShader("2D");

    float _x,_y,_w,_h;
    _x=x*2.0-1;
    _w=w*2.0-1;

    _y=(y*-2.0)+1;
    _h=(h*-2.0)+1;

    X=_x;
    W=_w-_x;

    Y=_y;
    H=_h-_y;

//altura 64
//inicio_y MAYUSCULAS 198
//L       573     34
//1400X800//dibujo
//1080, 720//pantalla
float T_x,T_y,T_w,T_h;
//imprimir una letra usando el manager

Manager = Singleton<Letra2DManager>::Instance();

auto letra=Manager->getChar('a');
letra.resize(400);


_w=letra.getW();
_h=letra.getH();

    T_x=letra.getTX();
    T_w=letra.getTW();

    T_y=letra.getTY();
    T_h=letra.getTH();


    float vertices[] = {
    //  Position      Color             Texcoords
        _x,  _y,  T_x, T_y, // Top-left
        _w,  _y,  T_w, T_y, // Top-right
        _w,  _h,  T_w, T_h, // Bottom-right
        _x,  _h,  T_x, T_h  // Bottom-left
    };


    GLuint elements[] = {
        0, 1, 2,
    	2, 3, 0
    };


    	//Creamos vao
    	//GLuint VAO = 0;
    	glGenVertexArrays(1, &VAO);
    	glBindVertexArray(VAO);

    	//creamos vbo
    	glGenBuffers(1, &VBO);
    	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

    	//creamo ebo para optimizar
    	glGenBuffers(1, &EBO);
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    	    sizeof(elements), elements, GL_STATIC_DRAW);

            //textura

            //std::cout <<"textura"<< HUDtext << '\n';
            //newMat->addTexture("DiffuseMap", "assets/Textures/DefaultDiffuse.jpg",      GN::RGBA, GN::REPEAT_TEXTURE | GN::GEN_MIPMAPS);


            //glGenTextures(1, &textureID);
            //glBindTexture(GL_TEXTURE_2D,textureID);
            //int width, height;
            //unsigned char* image = SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);//buffer?
            //SOIL_free_image_data(image);

            auto Manager = Singleton<AssetManager>::Instance();
            textureID=Manager->getTexture("assets/Fonts/letras.png",   GN::RGBA,0);

            //activamos transparencias
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable( GL_BLEND );
            //glDisable(GL_BLEND);


    	//habilitamos in

    	GLint posAttrib = sh->getAttribLocation( "position");
    	glEnableVertexAttribArray(posAttrib);
    	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
    		4*sizeof(float), 0);

    	GLint texAttrib = sh->getAttribLocation("texcoord");
    	glEnableVertexAttribArray(texAttrib);
    	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
    		4*sizeof(float), (void*)(2*sizeof(float)));

}
void Texto2D::setPos(float x,float y){
    //glDeleteVertexArrays(1, &VBO);
    X=x;
    Y=y;
}
void Texto2D::setColor(glm::vec4 _color){
    color=_color;
}
void Texto2D::setImage(const std::string &Name){
    auto Manager = Singleton<AssetManager>::Instance();
    textureID=Manager->getTexture(Name,   GN::RGBA,0);

}
float  Texto2D::getWid(char car){
    auto letra=Manager->getChar(car);
    letra.resize(tamanyo);
    return letra.getW();
}
float Texto2D::getSizeY(){
    auto letra=Manager->getChar('R');
    letra.resize(tamanyo);
    return letra.getH();

}
float Texto2D::getSizeX(){
    float _w;

    separacion=0;//si queremos espaci entre las palabras
    int max=palabra.size();
    float espacio=getWid('G');
    float tam=0;
    _w=0;
    for (int i = 0; i < max; i++) {
        if(palabra[i]==' ')
        {
            tam=espacio;
        }
        else{
            tam=getWid(palabra[i]);
        }
        _w=_w+tam+separacion;

    }
    return _w;
}

void Texto2D::Draw(){
    auto sh=Singleton<AssetManager>::Instance()->getShader("2D");
    sh->Bind();
    //metemos el color
    GLuint inputColour = sh->getUniformLocation("inputColour");
    glUniform4fv(inputColour,1,&color[0]);




    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    auto loc=sh->getUniformLocation("DiffuseMap");
    glUniform1i(loc, 0);


    //cargado textura
/*
    auto Manager = Singleton<AssetManager>::Instance();
    auto HUDtext=Manager->getTexture("assets/HUD/ojetecalor.jpg",GL_TEXTURE_2D);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    int width, height;
    unsigned char* image =
    SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);//buffer?

    //auto loc=sh->getUniformLocation("DiffuseMap");
    //glActiveTexture(GL_TEXTURE0 );
    //glActiveTexture(HUDtext );
    //glBindTexture(GL_TEXTURE_2D, HUDtext);
    //glUniform1i(loc, HUDtext);

*/

    glBindVertexArray(VAO);
//
//palabra
//glDisable(GL_BLEND);

float incx=X;
separacion=0;//si queremos espaci entre las palabras
int max=palabra.size();
for (int i = 0; i < max; i++) {

    if(palabra[i]==' ')
    {
        float tam=ChangeChar(incx,Y,'G');
        incx=incx+tam+separacion;
    }
    else{
        float tam=ChangeChar(incx,Y,palabra[i]);
        incx=incx+tam+separacion;
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }

}
    Singleton<AssetManager>::Instance()->getShader("Default")->Bind();

}

Texto2D::~Texto2D(){
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}
