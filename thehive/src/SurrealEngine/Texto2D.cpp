#include "Texto2D.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>
#include "Singleton.hpp"
#include "Letra2DManager.hpp"

#define SCREENW 1080.0f
#define SCREENH 720.0f

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

void Texto2D::setText(std::string pal){
    palabra=pal;
}
float Texto2D::ChangeChar(float x,float y,char cha){

    //std::cout << "cha:" <<cha<< '\n';

    float _x,_y,_w,_h;
    float T_x,T_y,T_w,T_h;
    _x=x*2.0-1;
    _y=y*-2.0+1;
    auto letra=Manager->getChar(cha);
    letra.resize(tamanyo);
    _w=(x+letra.getW())*2.0-1;
    _h=(y+letra.getH())*-2.0+1;

        T_x=letra.getTX();
        T_w=letra.getTW();

        T_y=letra.getTY();
        T_h=letra.getTH();
        //std::cout << "X:" <<_x<< '\n';
        //std::cout << "Y:" <<_y<< '\n';

        //std::cout << "LW:" <<letra.getW()<< '\n';
        //std::cout << "LH:" <<letra.getH()<< '\n';

        //std::cout << "W:" <<_w<< '\n';
        //std::cout << "H:" <<_h<< '\n';

        //std::cout << "TX:" <<T_x<< '\n';
        //std::cout << "TY:" <<T_y<< '\n';
        //std::cout << "TW:" <<T_w<< '\n';
        //std::cout << "TH:" <<T_h<< '\n';

        //std::cout << "aux1:" <<aux1<< '\n';
        //std::cout << "aux2:" <<aux2<< '\n';


        float vertices[] = {
        //  Position      Color             Texcoords
            _x,  _y,  T_x, T_y, // Top-left
            _w,  _y,  T_w, T_y, // Top-right
            _w,  _h,  T_w, T_h, // Bottom-right
            _x,  _h,  T_x, T_h  // Bottom-left
        };
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return letra.getW();
}
Texto2D::Texto2D(float x,float y,float w,float h,const std::string &Palabra,glm::vec4 _color,float tam):Texto2D(x,y,Palabra,_color,tam){



    float _w=0,_h=0,rx=0,ry=0;
    _w=getSizeX();
    _h=getSizeY();//0-1


    rx=(w-x-_w)/2.0;
    rx=rx+x;

    ry=(h-y-_h)/2.0;
    ry=ry+y;


    setPos(rx,ry);



}

Texto2D::Texto2D(float x,float y,const std::string &Palabra,glm::vec4 _color,float tam)
:VAO(0),VBO(0),EBO(0),color(_color),textureID(0),separacion(0.05),tamanyo(tam),palabra(Palabra),index(-1)
{
    auto sh=Singleton<AssetManager>::Instance()->getShader("2D");

    float _x,_y,_w,_h;
    _x=x;
    _w=0;

    _y=y;
    _h=0;
    //_y=(y*-2.0)+1;
    //_x=x*2.0-1;

    X=x;
    W=_w-_x;

    Y=y;
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
letra.resize(tamanyo);


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
        2, 1, 0,
    	0, 3, 2
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

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


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

    GLuint Zindex = sh->getUniformLocation("Zindex");
    glUniform1f(Zindex,index);



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
//std::cout << "dibujando" << '\n';
//std::cout << "X:" <<X<< '\n';
//std::cout << "Y:" <<Y<< '\n';
//std::cout << "Palabra:" <<palabra<< '\n';
//color=glm::vec4(1,1,1,1);
//std::cout << "Color:" <<"("<<color[0]<<","<<color[1]<<","<<color[2]<<","<<color[3]<<")"<< '\n';
//std::cout << "tamanyo:" <<tamanyo<< '\n';

//palabra
//glDisable(GL_BLEND);

    float incx=X;//opengl
    separacion=0;//si queremos espaci entre las palabras
    int max=palabra.size();
    for (int i = 0; i < max; i++) {

        if(palabra[i]==' ')
        {
            float tam=ChangeChar(incx,Y,'G');
            incx=incx+tam+separacion;
            //SCREENW
        }
        else{
            float tam=ChangeChar(incx,Y,palabra[i]);
            incx=incx+tam+separacion;
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }

    }

    glBindVertexArray(0);
    Singleton<AssetManager>::Instance()->getShader("Default")->Bind();

}

Texto2D::~Texto2D(){
    std::cout << "DELETE TEXTO" << '\n';

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);

}
