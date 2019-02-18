#ifndef TMOTORTAG_H
#define TMOTORTAG_H

#include <SurrealEngine/TNodo.hpp>
#include <SurrealEngine/TEntidad.hpp>
#include <SurrealEngine/TLuz.hpp>
#include <SurrealEngine/TTransform.hpp>
#include <SurrealEngine/TCamara.hpp>
#include <SurrealEngine/ZStaticMesh.hpp>
#include <SurrealEngine/AssetManager.hpp>
#include <Util.hpp>

class TMotorTAG {
    public:
        TMotorTAG();
        ~TMotorTAG();

        TNodo* crearCamara(float,float,float,gg::Vector3f,gg::Vector3f);
        TNodo* crearLuz(gg::Color &_color,gg::Vector3f,gg::Vector3f);
        TNodo* crearMalla(const std::string&,gg::Vector3f,gg::Vector3f);

        void draw();

    private:
        TNodo* escena;
        AssetManager* gestorRecursos;

        //Atributos Camara
        float cercano, lejano, fov;
        glm::vec3 target;
        bool inverted;

        //Atributos Luz
        gg::Color intensidad;

        TNodo* Transform(gg::Vector3f pos, gg::Vector3f rot);
        TNodo *crearNodo(TNodo* padre, TEntidad* entidad);

};

#endif
