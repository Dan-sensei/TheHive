#include "BillboardBueno.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>
#include <Singleton.hpp>
#include <SurrealEngine/SurrealEngine.hpp>





BillboardBueno::BillboardBueno(float x,float y,float z,const std::string &Name)
:VAO(0),VBO(0),EBO(0),color(1,1,1,1),textureID(0),index(0),centro(x,y,z)
{
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
        textureID = Manager->getTexture(Name,   GN::RGBA,0);

        //activamos transparencias
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable( GL_BLEND );

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

void BillboardBueno::setColor(glm::vec4 _color){
    color=_color;
}

void BillboardBueno::setImage(const std::string &Name){
    auto Manager = Singleton<AssetManager>::Instance();
    textureID=Manager->getTexture(Name,   GN::RGBA,0);
}

void BillboardBueno::Draw(){




    auto engine=Singleton<SurrealEngine>::Instance();
    auto up=    engine->vectorUp();
    auto MVP2=    engine->getMVP();
    auto rigth= engine->vectorRigth();
    rigth*=2;
    up*=2;
    //auto centro =glm::vec3(0,20,10);
    //auto centro =glm::vec3(0,2,10);//pos del mundo
    //glm::vec3 x1,x2,x3,x4;
    //x1=centro;
    //x2=centro+rigth;
    //x3=centro+rigth-up;
    //x4=centro-up;
    //x1=centro-rigth+up;//izquierda arriba
    //x2=centro+rigth+up;//derecha arriba
    //x3=centro+rigth-up;//derecha bajo
    //x4=centro-rigth-up;//izquierda bajo

    //engine->Draw3DLine( x1,x2,gg::Color(255,0,255,255));
    //engine->Draw3DLine( x3,x2,gg::Color(255,0,255,255));
    //engine->Draw3DLine( x3,x4,gg::Color(255,0,255,255));
    //engine->Draw3DLine( x1,x4,gg::Color(255,0,255,255));



    auto sh=Singleton<AssetManager>::Instance()->getShader("Bill");
    sh->Bind();
    //std::cout << "centro:"  <<"("<<centro.x<<","<<centro.y<<","<<centro.z<<")"<< '\n';
    //std::cout << "up:"      <<"("<<up    .x<<","<<up    .y<<","<<up    .z<<")"<< '\n';
    //std::cout << "rigth:"   <<"("<<rigth .x<<","<<rigth .y<<","<<rigth .z<<")"<< '\n';
    //auto MVP2=engine

    GLuint MVP = sh->getUniformLocation("MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, &(MVP2)[0][0]);

    GLuint particleCenter_wordspace = sh->getUniformLocation("particleCenter_wordspace");
    glUniform3fv(particleCenter_wordspace,1,&centro[0]);

    GLuint CameraRight_worldspace = sh->getUniformLocation("CameraRight_worldspace");
    glUniform3fv(CameraRight_worldspace,1,&rigth[0]);

    GLuint CameraUp_worldspace = sh->getUniformLocation("CameraUp_worldspace");
    glUniform3fv(CameraUp_worldspace,1,&up[0]);
    //metemos el color
    GLuint inputColour = sh->getUniformLocation("inputColour");
    glUniform4fv(inputColour,1,&color[0]);


    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    auto loc=sh->getUniformLocation("DiffuseMap");
    glUniform1i(loc, 0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    Singleton<AssetManager>::Instance()->getShader("Default")->Bind();

}

BillboardBueno::~BillboardBueno(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);

}
