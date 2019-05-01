#include "Texto2D.hpp"

#include <Omicron/AssetManager.hpp>

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
void Texto2D::setY(float y){
    Y=y;
}
float Texto2D::getH(){
    return H;
}

void Texto2D::setText(std::string pal){
    palabra=pal;
}
void Texto2D::ChangeChar(float &incx,const char &cha){
    //tam =letra->getW();
    ////std::cout << "cha:" <<cha<< '\n';
    //incx=incx+tam;

    float T_x,T_y,T_w,T_h;
    float _x,_y,_w,_h;
    _x=incx*2.0-1;
    _y=Y*-2.0+1;

    //float tam=letra->getW();
    auto letra=Manager->getChar(cha);
    letra->resize(tamanyo);

    incx+=letra->getW();

    _w=incx*2.0-1;
    _h=(Y+letra->getH())*-2.0+1;

        T_x=letra->getTX();
        T_w=letra->getTW();

        T_y=letra->getTY();
        T_h=letra->getTH();

        float vertices[] = {
        //  Position      Color             Texcoords
            _x,  _y,  T_x, T_y, // Top-left
            _w,  _y,  T_w, T_y, // Top-right
            _w,  _h,  T_w, T_h, // Bottom-right
            _x,  _h,  T_x, T_h  // Bottom-left
        };
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        //incx+=tam;
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

}
Texto2D::Texto2D(float x,float y,float w,float h,const std::string &Palabra,glm::vec4 _color,float tam)
:Texto2D(x,y,Palabra,_color,tam)
{



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
:VAO(0),VBO(0),EBO(0),color(_color),textureID(0),separacion(0.05),tamanyo(tam),palabra(Palabra),index(-1),inicio(nullptr),fin(nullptr)
{
    auto sh=Singleton<AssetManager>::Instance();
    inicio=sh->getShader("2D");
    fin=sh->getShader("Default");
    inputColour = inicio->getUniformLocation("inputColour");
    Zindex = inicio->getUniformLocation("Zindex");
    textura=inicio->getUniformLocation("DiffuseMap");



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
    letra->resize(tamanyo);


    _w=letra->getW();
    _h=letra->getH();

    T_x=letra->getTX();
    T_w=letra->getTW();

    T_y=letra->getTY();
    T_h=letra->getTH();


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

            ////std::cout <<"textura"<< HUDtext << '\n';
            //newMat->addTexture("DiffuseMap", "assets/Textures/DefaultDiffuse.jpg");


            //glGenTextures(1, &textureID);
            //glBindTexture(GL_TEXTURE_2D,textureID);
            //int width, height;
            //unsigned char* image = SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);//buffer?
            //SOIL_free_image_data(image);

            auto Manager = Singleton<AssetManager>::Instance();
            textureID=Manager->getTexture("assets/Fonts/letras.png");

            //activamos transparencias
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glEnable( GL_BLEND );
            //glDisable(GL_BLEND);


    	//habilitamos in
        glEnableVertexAttribArray(0);
    	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
    		4*sizeof(float), 0);

    	glEnableVertexAttribArray(1);
    	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
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
    textureID=Manager->getTexture(Name);

}
float  Texto2D::getWid(char car){
    auto letra=Manager->getChar(car);
    letra->resize(tamanyo);
    return letra->getW();
}
float Texto2D::getSizeY(){
    auto letra=Manager->getChar('R');
    letra->resize(tamanyo);
    return letra->getH();

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

    inicio->Bind();
    //metemos el color
    glUniform4fv(inputColour,1,&color[0]);
    glUniform1f(Zindex,index);
    glUniform1i(textura, 0);



    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, textureID);



    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float incx=X;//opengl
    separacion=0;//si queremos espaci entre las palabras
    int max=palabra.size();
    for (int i = 0; i < max; i++) {

        if(palabra[i]==' ')
        {
            ChangeChar(incx,'G');
        }
        else{
            ChangeChar(incx,palabra[i]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }

    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    fin->Bind();

}

Texto2D::~Texto2D(){

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);

}
