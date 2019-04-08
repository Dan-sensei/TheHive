#ifndef OPENGENUM_H
#define OPENGENUM_H

#include <ShaderUniformMapping.hpp>

namespace GN{

    //BODY
    enum{
        STATIC = 0,
        DYNAMIC = 1,
    };

    //TEXTURES  -   SOIL
    enum{
        REPEAT_TEXTURE = 4,
        INVERT_Y = 16,
        GEN_MIPMAPS = 4096,
        COMPRESS_TO_DDS = 32,

        RGB = 3,
        RGBA = 4,

        DIFFUSE = 0,
        NORMAL = 1,
        SPECULAR = 2,
    };

    // SHADERS
    enum ShadersIDs{
        DIFFUSE_MAP = _U_DIFFUSE_MAP,
        NORMAL_MAP = _U_NORMAL_MAP,
        SPECULAR_MAP = _U_SPECULAR_MAP,
        BLEND1 = 19,
        BLEND2 = 20,
    };

}


#endif
