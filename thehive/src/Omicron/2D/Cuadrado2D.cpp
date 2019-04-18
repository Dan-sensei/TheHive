#include "Cuadrado2D.hpp"
#include <Omicron/AssetManager.hpp>
#include <Singleton.hpp>
#include <iostream>


#define WIDTH          1080.0f
#define HEIGTH         720.0f

Cuadrado2D::Cuadrado2D(float x,float y,float w,float h)
:VAO(0),VBO(0),EBO(0),color(1,1,1,1),index(-1),inicio(nullptr),fin(nullptr)
{
    auto sh=Singleton<AssetManager>::Instance();
    inicio=sh->getShader("Plano");
    fin=sh->getShader("Default");
    Zindex = inicio->getUniformLocation("Zindex");
    inputColour = inicio->getUniformLocation("inputColour");


    float _x,_y,_w,_h;
    _x=x*2.0-1;
    _w=w*2.0-1;

    _y=(y*-2.0)+1;
    _h=(h*-2.0)+1;

    float vertices[] = {
        _x,  _y,   // Top-left
        _w,  _y,   // Top-right
        _w,  _h,   // Bottom-right
        _x,  _h   // Bottom-left
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //creamo ebo para optimizar
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        //activamos transparencias
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable( GL_BLEND );

        //habilitamos in
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glBindVertexArray(0);

}

void Cuadrado2D::setPos(float x,float y,float w,float h){
    //glDeleteVertexArrays(1, &VBO);
    glBindVertexArray(VAO);

    float _x,_y,_w,_h;
    _x=x*2.0-1;
    _w=w*2.0-1;

    _y=(y*-2.0)+1;
    _h=(h*-2.0)+1;

    float vertices[] = {
        _x,  _y,   // Top-left
        _w,  _y,   // Top-right
        _w,  _h,   // Bottom-right
        _x,  _h   // Bottom-left
    };
    //glBindVertexArray(VAO);
    //glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glBindVertexArray(0);


}
void Cuadrado2D::setColor(glm::vec4 _color){
    color=_color;
}
void Cuadrado2D::setZindex(float res){
    index=res;
}


void Cuadrado2D::Draw(){
    inicio->Bind();
    //metemos el color
    glUniform4fv(inputColour,1,&color[0]);
    glUniform1f(Zindex,index);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);glUniform1f(Zindex,index);

    fin->Bind();

}

Cuadrado2D::~Cuadrado2D(){
    ////std::cout << "DELETE CUADRADO" << '\n';

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);

}
