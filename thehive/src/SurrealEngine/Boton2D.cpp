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

Boton2D::Boton2D(float x,float y,float w,float h,EnumButtonType _tipo,const std::string &imgP,const std::string &imgS,const std::string &texto,bool focus)
:Imagen(x,y,w,h,imgP),selected(focus),imgPrincipal(imgP),imgHover_Selected(imgS),tipo(_tipo),text(0,0,0,0,texto,0.05)
{
    X=x*WIDTH;
    W=w*WIDTH;

    Y=y*HEIGTH;
    H=h*HEIGTH;

    float _w=0,_h=0,rx=0,ry=0;
    _w=text.getSizeX();
    _h=text.getSizeY();
    std::cout << "_w" <<_w<< '\n';
    std::cout << "_h" <<_h<< '\n';

    std::cout << "x" <<x<< '\n';
    std::cout << "x" <<x<< '\n';
    std::cout << "w" <<w<< '\n';
    std::cout << "h" <<h<< '\n';

    std::cout << "ancho=" <<w-x<< '\n';
    std::cout << "alto=" <<h-y<< '\n';



    //if(ancho>_w){
        rx=(w-x-_w)/2.0;
        rx=rx+x;

        ry=(h-y-_h)/2.0;
        ry=ry+y;
    //}
    std::cout << "rx" <<rx<< '\n';
    std::cout << "ry" <<ry<< '\n';
    text.setPos(rx,ry);
    text.setColor(glm::vec4(0.666,0,0,1));
    //text.setColor(glm::vec4(0.666,0,0,1));

    //text();


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
    text.Draw();
    Imagen.Draw();

}

Boton2D::~Boton2D(){

}
