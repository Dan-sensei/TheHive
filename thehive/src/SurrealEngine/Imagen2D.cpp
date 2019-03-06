#include "Imagen2D.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>



// glm::mat4 TEntidad::modelMatrix;
// glm::mat4 TEntidad::viewMatrix;
// glm::mat4 TEntidad::projMatrix;
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

Imagen2D::Imagen2D(float x,float y,float w,float h,const std::string &Name)
:VAO(0),VBO(0),EBO(0),color(1,1,1,1),textureID(0)
{
    auto sh=Singleton<AssetManager>::Instance()->getShader("2D");
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
            textureID=Manager->getTexture(Name,   GN::RGBA,0);

            //activamos transparencias
            //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glEnable( GL_BLEND );




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
    //glBindVertexArray(VAO);
    //glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);





std::cout << "entra" << '\n';

}
void Imagen2D::setColor(glm::vec4 _color){
    color=_color;
}
void Imagen2D::setImage(const std::string &Name){
    auto Manager = Singleton<AssetManager>::Instance();
    textureID=Manager->getTexture(Name,   GN::RGBA,0);

}

void Imagen2D::Draw(){
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    Singleton<AssetManager>::Instance()->getShader("Default")->Bind();

}

Imagen2D::~Imagen2D(){
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}
