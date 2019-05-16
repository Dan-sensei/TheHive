#include "Imagen2D.hpp"

#include <Omicron/AssetManager.hpp>
#include <iostream>
#include <Singleton.hpp>

float Imagen2D::getX(){
    return X;
}
float Imagen2D::getW(){
    return W;
}
float Imagen2D::getY(){
    return Y;
}
float Imagen2D::getH(){
    return H;
}
void Imagen2D::setSesgado(float res){
    float sesgado=res;

    float sni=sesgado/2.0;
    float _x,_y,_w,_h;
    _x=X*2.0-1;
    _w=W*2.0-1;

    _y=(Y*-2.0)+1;
    _h=(H*-2.0)+1;
    //float vertices[] = {
    ////  Position      Color             Texcoords
    //    _x+sni,  _y,  0.0f, 0.0f, // Top-left
    //    _w+sesgado,  _y,  1.0f, 0.0f, // Top-right
    //    _w-sesgado,  _h,  1.0f, 1.0f, // Bottom-right
    //    _x-sni,  _h,  0.0f, 1.0f  // Bottom-left
    //};
    if(res>0){
        float aux=sni;
        sni=sesgado;
        sesgado=aux;
    }
    float vertices[] = {
    //  Position              Texcoords
        _x-sesgado,  _y,  0.0f, 0.0f, // Top-left
        _w-sni,  _y,  1.0f, 0.0f, // Top-right
        _w+sni,  _h,  1.0f, 1.0f, // Bottom-right
        _x+sesgado,  _h,  0.0f, 1.0f  // Bottom-left
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Imagen2D::Imagen2D(float x,float y,float w,float h,const std::string &Name)
:VAO(0),VBO(0),EBO(0),color(1,1,1,1), colorInicial(0,0,0,1),textureID(0),index(-0.9999),inicio(nullptr),texturaURL(Name)
{
    auto sh=Singleton<AssetManager>::Instance();
    inicio=sh->getShader("HUD");
    inputColour = inicio->getUniformLocation("inputColour");
    Zindex = inicio->getUniformLocation("Zindex");
    textura=inicio->getUniformLocation("DiffuseMap");
    X=x;
    W=w;

    Y=y;
    H=h;

    float _x,_y,_w,_h;
    _x=x*2.0-1;
    _w=w*2.0-1;

    _y=(y*-2.0)+1;
    _h=(h*-2.0)+1;

    float vertices[] = {
    //  Position      Color             Texcoords
        _x,  _y,  0.0f, 0.0f, // Top-left
        _w,  _y,  1.0f, 0.0f, // Top-right
        _w,  _h,  1.0f, 1.0f, // Bottom-right
        _x,  _h,  0.0f, 1.0f  // Bottom-left
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
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        auto Manager = Singleton<AssetManager>::Instance();
        textureID = Manager->getTexture(Name);

        //activamos transparencias
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glEnable( GL_BLEND );

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

void Imagen2D::setShader(std::string sha){
    auto sh=Singleton<AssetManager>::Instance();
    inicio=sh->getShader(sha);
}
void Imagen2D::setPos(float x,float y,float w,float h){
    //glDeleteVertexArrays(1, &VBO);
    float _x,_y,_w,_h;
    _x=x*2.0-1;
    _w=w*2.0-1;

    _y=(y*-2.0)+1;
    _h=(h*-2.0)+1;

    float vertices[] = {
    //  Position      Color             Texcoords
        _x,  _y,  0.0f, 0.0f, // Top-left
        _w,  _y,  1.0f, 0.0f, // Top-right
        _w,  _h,  1.0f, 1.0f, // Bottom-right
        _x,  _h,  0.0f, 1.0f  // Bottom-left
    };
    glBindVertexArray(VAO);
    //glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(0);

}

void Imagen2D::setColor(glm::vec4 _color){
    color=_color;
}

void Imagen2D::setColorInicial(glm::vec4 _color){
    colorInicial=_color;
}

void Imagen2D::assignColor(){
    color = colorInicial;
}

glm::vec4 Imagen2D::getColor(){
    return color;
}

void Imagen2D::setImage(const std::string &Name){
    texturaURL=Name;
    auto Manager = Singleton<AssetManager>::Instance();
    textureID=Manager->getTexture(Name);
}
std::string Imagen2D::getImage(){
    return texturaURL;
}

void Imagen2D::setZindex(float res){
    index=res;
}

void Imagen2D::Draw(){

    inicio->Bind();
    //metemos el color
    glUniform4f(inputColour,color.x, color.y, color.z, color.w);
    glUniform1f(Zindex,index);
    glUniform1i(textura, 0);
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Imagen2D::~Imagen2D(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}
