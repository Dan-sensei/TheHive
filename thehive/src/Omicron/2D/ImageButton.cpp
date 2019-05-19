#include "ImageButton.hpp"
#include <GLFW/glfw3.h>


ImageButton::ImageButton(float x, float y, float w, float h, EnumButtonType _tipo, unsigned int Texture, unsigned int TextureHover)
:Imagen(x,y,w,h,Texture), imgPrincipal(Texture), imgHover_Selected(TextureHover), tipo(_tipo), selected(false), Played(false)
{
    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    float ancho = mode->width;
    float alto = mode->height;

    X=x*ancho;
    W=w*ancho;

    Y=y*alto;
    H=h*alto;
}

ImageButton::ImageButton(const ImageButton &orig)
:Imagen(orig.Imagen), imgPrincipal(orig.imgPrincipal), imgHover_Selected(orig.imgHover_Selected),
 X(orig.X), Y(orig.Y), W(orig.W), H(orig.H), tipo(orig.tipo), selected(orig.selected), Played(orig.Played)
{}

ImageButton::~ImageButton(){

}


void ImageButton::Draw(){
    Imagen.Draw();
}

bool ImageButton::checkOn(float x, float y){
    if(X<x  &&  x<W &&  Y<y &&  y<H){
        return true;
    }

    return false;
}

void ImageButton::setHover(){
    if(!selected)
        Imagen.setImage(imgHover_Selected);
    selected = true;
    Played = true;
}

void ImageButton::reset(){
    if(selected)
        Imagen.setImage(imgPrincipal);
    selected = false;
    Played = false;
}
