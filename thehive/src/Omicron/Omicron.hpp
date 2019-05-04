#ifndef _OMICRON_H
#define _OMICRON_H

#include <map>
#include <cstdint>
#include <string>
#include <Util.hpp>

//
#include <Omicron/CORE/StandardNode.hpp>
#include <Omicron/CORE/TEntidad.hpp>
#include "TLuz.hpp"
#include <Omicron/CORE/TTransform.hpp>
#include <Omicron/CORE/TCamara.hpp>
#include "Shader.hpp"
#include <Omicron/ZMESHES/ZStaticMesh.hpp>
#include <Omicron/ZMESHES/ZMovableMesh.hpp>
#include <Omicron/ZMESHES/ZDynamicMesh.hpp>
#include <Omicron/ZMaterial.hpp>
#include <Omicron/AssetManager.hpp>
#include <Omicron/KEYCODES.hpp>
#include "Debug.hpp"
#include <Omicron/Clock.hpp>
#include <Omicron/FX/Particle_System_DATA.hpp>
#include <Omicron/DeferredShading.hpp>

template <typename T>
class Singleton;

class Omicron {
    friend class Singleton<Omicron>;
    friend class Debug;
    public:
        ~Omicron();
        void HideCursor(bool t);

        StandardNode* crearCamara(const float&, const float&, const float&, const glm::vec3&, const glm::vec3&, const float&);
        StandardNode* crearLuz(gg::Color&, const glm::vec3&, const glm::vec3&, Shader* sh);
        StandardNode* createStaticMesh(const char*, const glm::vec3 &Position = glm::vec3(), const glm::quat &Rotation = glm::vec3(), int8_t map_zone = 0, const std::string& BoundingBoxPath = "");
        StandardNode* createMovableMesh(const char*, const glm::vec3 &Position = glm::vec3(), const glm::quat &Rotation = glm::vec3(), int8_t map_zone = 0, const std::string& BoundingBoxPath = "");
        StandardNode* CreateDynamicMesh(const glm::vec3& Position = glm::vec3(), const glm::quat& Rotation = glm::vec3(), int8_t map_zone = 0, const std::string& BoundingBoxPath = "");
        StandardNode* CreateParticleSystem(const ParticleSystem_Data &Data, int8_t map_zone = 0);

        // Define cuantas zonas habrán en el juego, para manejar la visibilidad de múltiples objetos a la vez
        void createZones(uint8_t NumberOfZones);

        void deleteLeafNode(ZNode *node);
        void deleteZStaticMeshLeafNode(ZNode *node);

        bool bindMaterialToMesh(StandardNode*,ZMaterial*);
        bool bindMaterialToDynamicMesh(StandardNode*,ZMaterial*);

        void DisplayFPS();

        void setPosition(StandardNode* _node, const glm::vec3&);
        void setRotation(StandardNode* _node,const glm::quat&);

        void BeginDraw();
        void draw();
        void EndDraw();

        //bool isLClicked();
        void close();
        //void resetClicked();
        glm::vec3 vectorUp();
        glm::vec3 vectorRigth();
        glm::mat4  getMVP();
        glm::mat4  getVP();
        glm::mat4  getV();
        glm::mat4  getM();

        TCamara* getCam();
        void PollEvents();

        //void PointAt(TNodo *_node, const glm::vec3& _offpos);
        inline bool isLClickPressed(){ return LCLICK; };
        inline int getWheelState(){return wheel;};
        inline bool isWindowOpen(){ return !glfwWindowShouldClose(window);};
        inline StandardNode* getCamera(){return main_camera;};

        void getCursorPosition(double &posX, double &posY);
        void clean();
        void resetSceneGraph();

        void Draw3DLine(const glm::vec3 &From, const glm::vec3 &To, const gg::Color &c);

        inline bool key(gg::KEYCODE keyCode, bool setToFalse = false){
            if(setToFalse){
                bool result = KEYS[keyCode];
                KEYS[keyCode] = false;
                return result;
            }
            else
                return KEYS[keyCode];
        };

        bool Initialize();

        void SetMapZoneVisibility(const int8_t &zone,const bool &flag);

        void resetClickVariable();

    private:

        Omicron();

        gg::Clock FPS_Clock;

        DeferredShading _DeferredShading;

        StandardNode* ESCENA;
        StandardNode* OKAMERAS_LAYER;
        StandardNode* LIGHTS_LAYER;
        StandardNode* BUFFERS_LAYER;

        GLFWwindow* window;
        AssetManager* gestorRecursos;
        Debug* Debugger;

        StandardNode* main_camera;
        TCamara* cam_;

        uint16_t FPS;


        std::vector<StandardNode*> ZONES;

        StandardNode* bindTransform(const glm::vec3& pos, const glm::quat& rot, StandardNode* FATHER);

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        static bool* KEYS;
        static bool LCLICK;
        //static bool clicked;
        static int wheel;
        static int IdButon;

        uint16_t WINDOW_WIDTH;
        uint16_t WINDOW_HEIGHT;

};

#endif
