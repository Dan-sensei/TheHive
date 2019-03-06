#include "Cuadrado2D.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"
#include <iostream>


// glm::mat4 TEntidad::modelMatrix;
// glm::mat4 TEntidad::viewMatrix;
// glm::mat4 TEntidad::projMatrix;
#define WIDTH          1080.0f
#define HEIGTH         720.0f

Cuadrado2D::Cuadrado2D(float x,float y,float w,float h)
:VAO(0),VBO(0),EBO(0),color(1,1,1,1)
{
    auto sh=Singleton<AssetManager>::Instance()->getShader("Plano");





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


            //activamos transparencias
            //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glEnable( GL_BLEND );

    	//habilitamos in

    	GLint posAttrib = sh->getAttribLocation( "position");
    	glEnableVertexAttribArray(posAttrib);
    	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
    		2*sizeof(float), 0);


        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



}
void Cuadrado2D::setPos(float x,float y,float w,float h){
    //glDeleteVertexArrays(1, &VBO);

float _x,_y,_w,_h;
_x=x/WIDTH;
_w=w/WIDTH;

_y=y/HEIGTH;
_h=h/HEIGTH;

//_x=x*2.0-1;
//_w=w*2.0-1;

//_y=(y*-2.0)+1;
//_h=(h*-2.0)+1;

    float vertices[] = {
        _x,  _y,   // Top-left
        _w,  _y,   // Top-right
        _w,  _h,   // Bottom-right
        _x,  _h   // Bottom-left
    };
    //glBindVertexArray(VAO);
    //glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);





std::cout << "entra" << '\n';

}
void Cuadrado2D::setColor(glm::vec4 _color){
    color=_color;
}


void Cuadrado2D::Draw(){
    auto sh=Singleton<AssetManager>::Instance()->getShader("Plano");
    sh->Bind();
    //metemos el color
    GLuint inputColour = sh->getUniformLocation("inputColour");
    glUniform4fv(inputColour,1,&color[0]);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    Singleton<AssetManager>::Instance()->getShader("Default")->Bind();

}

Cuadrado2D::~Cuadrado2D(){
    std::cout << "DELETE CUADRADO" << '\n';

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}
