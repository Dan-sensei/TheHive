#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <vector>
#include <cstdint>

#include <Omicron/2D/EnumButtonType.hpp>
#include <Omicron/2D/Imagen2D.hpp>



class ImageButton {
    public:
        //Boton2D();
        ImageButton(float x, float y, float w, float h, EnumButtonType _tipo, unsigned int Texture, unsigned int TextureHover);
        ImageButton(const ImageButton &orig);
        ~ImageButton();

        void Draw();
        //void init();
        void setPos(float x,float y,float w,float h);
        void setImage(unsigned int &TextureID);
        void setHoverImage(unsigned int &TextureID);
        bool checkOn(float x,float y);

        inline int getType() { return tipo; };
        inline bool HasPlayedSound() { return Played; };
        void reset();
        void setHover();

    private:
        Imagen2D Imagen;
        unsigned int imgPrincipal;
        unsigned int imgHover_Selected;
        float X,Y,W,H;
        EnumButtonType tipo;
        bool selected;
        bool Played;
};

#endif
