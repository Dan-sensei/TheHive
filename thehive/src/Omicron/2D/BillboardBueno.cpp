#include "BillboardBueno.hpp"

#include <Omicron/AssetManager.hpp>
//#include <iostream>
#include <Singleton.hpp>
#include <Omicron/Omicron.hpp>




BillboardBueno::BillboardBueno(float x,float y,float z,const std::string &Name)
:VAO(0),VBO(0),EBO(0),textureID(0),centro(x,y,z),inicio(nullptr)
{
    auto sh=Singleton<AssetManager>::Instance();
    inicio=sh->getShader("Bill");

    engine=Singleton<Omicron>::Instance();
    float _x,_y,_w,_h;
    _x=-0.5;
    _w=0.5;

    _y=0.5;
    _h=-0.5;

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

void BillboardBueno::setPos(float x,float y,float z){
    centro=glm::vec3(x,y,z);
}

void BillboardBueno::setImage(const std::string &Name){
    auto Manager = Singleton<AssetManager>::Instance();
    textureID=Manager->getTexture(Name);
}



void BillboardBueno::beginDraw(){

    inicio->Bind();

    glm::mat4 VP = projMatrix*viewMatrix;

    glUniformMatrix4fv(6, 1, GL_FALSE, &VP[0][0]);
    glUniform3f(3, centro.x, centro.y, centro.z);
    glUniform3f(4, viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
    glUniform3f(5, viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void BillboardBueno::endDraw(){}

BillboardBueno::~BillboardBueno(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}



