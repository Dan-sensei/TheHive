#include "Boton2D.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>



// glm::mat4 TEntidad::modelMatrix;
// glm::mat4 TEntidad::viewMatrix;
// glm::mat4 TEntidad::projMatrix;
#define WIDTH          1080
#define HEIGTH         720

Boton2D::Boton2D(float x,float y,float w,float h,EnumButtonType _tipo,const std::string &imgP,const std::string &imgS,const std::string &texto,bool focus,glm::vec4 color,float tam)
:Imagen(x,y,w,h,imgP),selected(focus),imgPrincipal(imgP),imgHover_Selected(imgS),hov(false),tipo(_tipo),text(x,y,w,h,texto,color,tam)//text(0,0,texto,color,tam)
{
//imagenes[0]=imgP;
//imagenes[1]=imgS;
std::cout << "X:" <<x<< '\n';
std::cout << "Y:" <<y<< '\n';
std::cout << "W:" <<w<< '\n';
std::cout << "H:" <<h<< '\n';
std::cout << "texto:" <<texto<< '\n';

    X=x*WIDTH;
    W=w*WIDTH;

    Y=y*HEIGTH;
    H=h*HEIGTH;

    if(texto==""){
        hasText=false;
    }
    else{
        hasText=true;
        text.setColor(color);
    }


}
void Boton2D::hover(bool dato){
    if(dato&&dato!=hov){
        //sec
        hov=dato;
        Imagen.setImage(imgHover_Selected);
    }else if(dato!=hov){
        //princ
        hov=dato;
        Imagen.setImage(imgPrincipal);

    }
}
bool Boton2D::checkOn(float x,float y){
if(x>X  &&  x<W &&  y>Y &&  y<H){
    return true;
}else{
    return false;
}

}
void Boton2D::setPos(float x,float y,float w,float h){
    Imagen.setPos(x, y, w, h);
}
void Boton2D::setColor(glm::vec4 _color){
    Imagen.setColor(_color);
}
void Boton2D::setImage(const std::string &Name){
    Imagen.setImage(Name);

}


void Boton2D::Draw(){
    Imagen.Draw();
    text.Draw();

}

Boton2D::~Boton2D(){

}
