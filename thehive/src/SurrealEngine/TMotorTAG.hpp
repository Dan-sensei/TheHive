#ifndef TMOTORTAG_H
#define TMOTORTAG_H

#include <map>
#include <cstdint>
#include <string>
#include <Util.hpp>

#include "TNodo.hpp"
#include "TEntidad.hpp"
#include "TLuz.hpp"
#include "TTransform.hpp"
#include "TCamara.hpp"
#include "Shader.hpp"
#include "ZStaticMesh.hpp"
#include "ZMaterial.hpp"
#include "AssetManager.hpp"

class TMotorTAG {
    public:
        TMotorTAG();
        ~TMotorTAG();

        TNodo* crearCamara(const float&, const float&, const float&, const gg::Vector3f&, const gg::Vector3f&, const float&);
        TNodo* crearLuz(gg::Color&, const gg::Vector3f&, const gg::Vector3f&, const uint8_t&);
        TNodo* crearMalla(const char*, const gg::Vector3f&, const gg::Vector3f&);

        int8_t addShaderToMap(const char*,bool);
        bool bindMaterialToMesh(TNodo*,const char*,const char*,const char*,const char*,const uint8_t&);

        void move(TNodo*,const gg::Vector3f&);
        void rotate(TNodo*,const float&,const gg::Vector3f&);

        void draw();

    private:
        TNodo* ESCENA;
        AssetManager* gestorRecursos;

        TNodo* bindTransform(const gg::Vector3f& pos, const gg::Vector3f& rot);
        std::map<uint8_t,Shader*> shaderMap;
};

#endif
