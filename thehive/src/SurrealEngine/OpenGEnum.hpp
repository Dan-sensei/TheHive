#ifndef OPENGENUM_H
#define OPENGENUM_H


namespace GN{

    //BODY
    enum{
        STATIC = 0,
        DYNAMIC = 1,
    };

    //TEXTURES  -   SOIL
    enum{
        INVERT_Y = 16,
        REPEAT_TEXTURE = 4,
        GEN_MIPMAPS = 4096,
        COMPRESS_TO_DDS = 32,

        RGB = 3,
        RGBA = 4,

        DIFFUSE = 0,
        NORMAL = 1,
        SPECULAR = 2,
    };

}


#endif