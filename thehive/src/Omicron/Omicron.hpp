#ifndef _OMICRON_H
#define _OMICRON_H

#include <map>
#include <cstdint>
#include <string>
#include <Util.hpp>

//
#include <Omicron/CORE/StandardNode.hpp>
#include <Omicron/CORE/TEntidad.hpp>
#include "LIGHTS/TLuz.hpp"
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
#include <Omicron/FX/ParticleSystem.hpp>
#include <Omicron/DeferredShading.hpp>
#include <Omicron/CORE/LightRoot.hpp>
#include <Omicron/LIGHTS/ZStaticPointLight.hpp>
#include <Omicron/LIGHTS/ZStaticSpotLight.hpp>

#include <Omicron/2D/HUD.hpp>

template <typename T>
class Singleton;

class Omicron {
    friend class Singleton<Omicron>;
    friend class Debug;
    public:
        ~Omicron();
        void HideCursor(bool t);

        StandardNode* crearCamara(const float&, const float&, const float&, const glm::vec3&, const glm::quat & Rotation, const float&);
        ZStaticPointLight* createStaticPointLight(const glm::vec3 &Color, const glm::vec3& pos, float Intensity, uint8_t ZONE);
        ZStaticSpotLight* createStaticSpotLight(const glm::vec3 &Color, const glm::vec3& pos, const glm::vec3 &Direction, float Intensity, uint8_t ZONE);

        ZNode* createStaticMesh(StandardNode* FATHER, const char*, const glm::vec3 &Position = glm::vec3(), const glm::quat &Rotation = glm::vec3());
        ZNode* createMovableMesh(StandardNode* FATHER, const char*, const glm::vec3 &Position = glm::vec3(), const glm::quat &Rotation = glm::vec3());
        ZNode* CreateDynamicMesh(StandardNode* FATHER, const glm::vec3& Position = glm::vec3(), const glm::quat& Rotation = glm::vec3());
        ParticleSystem* CreateParticleSystem(StandardNode* FATHER, const ParticleSystem_Data &Data);

        // Define cuantas zonas habrán en el juego, para manejar la visibilidad de múltiples objetos a la vez
        void createZones(uint8_t NumberOfZones);

        void deleteLeafNode(ZNode *node);

        bool bindMaterialToMesh(ZNode*,ZMaterial*);
        bool bindMaterialToDynamicMesh(ZNode*,ZMaterial*);

        void DisplayFPS();

        void setPosition(ZNode* _node, const glm::vec3&);
        void setRotation(ZNode* _node,const glm::quat&);

        void BeginDraw();
        void draw();
        void drawHUD();
        void EndDraw();

        //bool isLClicked();
        void close();

        void PollEvents();

        //void PointAt(TNodo *_node, const glm::vec3& _offpos);
        inline bool isLClickPressed(){ return LCLICK; };
        inline bool isRClickPressed(){ return RCLICK; };
        inline int getWheelState(){return wheel;};
        inline bool isWindowOpen(){ return !glfwWindowShouldClose(window);};
        inline StandardNode* getCamera(){return MainCameraNode;};
        inline TCamara* getMainCameraEntity(){return MainCamera;};
        inline glm::vec3* getMainCameraPositionPtr(){return MainCamera->getPositionPtr();};

        inline uint16_t getWindowsWidth(){ return WINDOW_WIDTH; };
        inline uint16_t getWindowsHeight(){ return WINDOW_HEIGHT; };

        inline uint16_t getInternalWindowsWidth(){ return INTERNAL_BUFFER_WIDTH; };
        inline uint16_t getInternalWindowsHeight(){ return INTERNAL_BUFFER_HEIGHT; };

        inline uint8_t getGlobalIlumination(){ return GLOBAL_LIGHT; };

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
        void resizeFrameBuffers(uint16_t FRAMEBUFFER_WIDTH, uint16_t FRAMEBUFFER_HEIGHT);
        void setLights(int nluces_F, int nluces_p);
        void setLightsZone(uint8_t ZONE, bool Active);
        void setGlobalIlumination(uint8_t FACTOR);
        void SetMapZoneVisibility(const int8_t &zone,const bool &flag);

        void resetClickVariable();
        void DrawZero();
        int DRAW_OBJECTS;
        std::vector<StandardNode*> ZONES;
        StandardNode* FORWARD_LAYER;
        HUD* hud;
    private:

        Omicron();

        DeferredShading _DeferredShading;
        gg::Clock FPS_Clock;


        StandardNode* ESCENA;
        StandardNode* OKAMERAS_LAYER;
        LightRoot* LIGHTS_LAYER;
        StandardNode* BUFFERS_LAYER;

        TCamara* MainCamera;
        StandardNode* MainCameraNode;

        GLFWwindow* window;
        AssetManager* gestorRecursos;
        Debug* Debugger;

        uint16_t FPS;



        StandardNode* bindTransform(const glm::vec3& pos, const glm::quat& rot, StandardNode* FATHER);

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        static bool* KEYS;
        static bool LCLICK;
        static bool RCLICK;
        //static bool clicked;
        static int wheel;
        static int IdButon;
        uint16_t WINDOW_WIDTH;
        uint16_t WINDOW_HEIGHT;

        uint16_t INTERNAL_BUFFER_WIDTH;
        uint16_t INTERNAL_BUFFER_HEIGHT;

        uint8_t GLOBAL_LIGHT;

};

#endif
