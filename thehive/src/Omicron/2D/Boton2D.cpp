#include "Boton2D.hpp"
#include <GLFW/glfw3.h>

Boton2D::Boton2D(float x,float y,float w,float h,EnumButtonType _tipo,const std::string &imgP,const std::string &imgS,const std::string &texto,bool focus,glm::vec4 color,float tam)
:Imagen(x,y,w,h,imgP),selected(focus),imgPrincipal(imgP),imgHover_Selected(imgS),hov(false),tipo(_tipo),text(x,y,w,h,texto,color,tam)//text(0,0,texto,color,tam)
{
    //imagenes[0]=imgP;
    //imagenes[1]=imgS;

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    float ancho = mode->width;
    float alto = mode->height;

    X=x*ancho;
    W=w*ancho;

    Y=y*alto-0.0377604*alto;
    H=h*alto-0.0377604*alto;

    if(texto==""){
        hasText=false;
    }
    else{
        hasText=true;
        text.setColor(color);
    }
}
void Boton2D::setSesgo(float res){
    Imagen.setSesgado(res);
}
int Boton2D::getType(){
    return tipo;
}
void Boton2D::hover(bool dato){
    if(dato&&dato!=hov){
        //sec
        hov=dato;
        Imagen.setImage(imgHover_Selected);
        //setColor(glm::vec4(0,111/250.0,0,1));
        setColor(glm::vec4(0.1,0.1,0.1,1));
    }else if(dato!=hov){
        //princ
        setColor(glm::vec4(0,0,0,1));
        //setColor(glm::vec4(0,75/250.0,0,1));
        hov=dato;
        Imagen.setImage(imgPrincipal);

    }
}
bool Boton2D::checkOn(float x,float y){
if(X<x  &&  x<W &&  Y<y &&  y<H){
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
    text.setColor(_color);
}
void Boton2D::setImage(const std::string &Name){
    Imagen.setImage(Name);

}

bool Boton2D::getHov(){
    return hov;
}


void Boton2D::Draw(){
    text.Draw();
    Imagen.Draw();

}

Boton2D::~Boton2D(){

}
