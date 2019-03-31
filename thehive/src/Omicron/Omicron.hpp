#ifndef Omicron_H
#define Omicron_H

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
#include "ZDynamicMesh.hpp"
#include "ZMaterial.hpp"
#include "AssetManager.hpp"
#include <Omicron/KEYCODES.hpp>
#include "TCamara.hpp"
#include "Debug.hpp"
#include "Clock.hpp"

template <typename T>
class Singleton;

class Omicron {
    friend class Singleton<Omicron>;
    friend class Debug;
    public:
        ~Omicron();
        void HideCursor(bool t);

        TNodo* crearCamara(const float&, const float&, const float&, const glm::vec3&, const glm::vec3&, const float&);
        TNodo* crearLuz(gg::Color&, const glm::vec3&, const glm::vec3&, Shader* sh);
        TNodo* crearMalla(const char*, const glm::vec3& = glm::vec3(), const glm::quat &Rotation = glm::vec3(), int8_t map_zone = 0, const std::string& BoundingBoxPath = "");
        TNodo* CreateDynamicMesh(const glm::vec3& Position = glm::vec3(), const glm::quat& Rotation = glm::vec3(), int8_t map_zone = 0, const std::string& BoundingBoxPath = "");

        // Define cuantas zonas habrán en el juego, para manejar la visibilidad de múltiples objetos a la vez
        void createZones(uint8_t NumberOfZones);

        void deleteLeafNode(TNodo *node);

        bool bindMaterialToMesh(TNodo*,ZMaterial*);
        bool bindMaterialToDynamicMesh(TNodo*,ZMaterial*);

        void DisplayFPS();

        void move(TNodo*,const glm::vec3&);
        void rotate(TNodo*,const float&,const glm::vec3&);
        void setPosition(TNodo* _node, const glm::vec3&);
        void setRotation(TNodo* _node,const glm::quat&);

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

        void PointAt(TNodo *_node, const glm::vec3& _offpos);
        inline bool isLClickPressed(){ return LCLICK; };
        inline int getWheelState(){return wheel;};
        inline bool isWindowOpen(){ return !glfwWindowShouldClose(window);};
        inline int getScreenWidth(){ return Half_Window_Width; };
        inline int getScreenHeight(){ return Half_Window_Height; };
        inline TNodo* getCamera(){return main_camera;};

        void getCursorPosition(double &posX, double &posY);
        void clean();

        void Draw3DLine(const glm::vec3 &From, const glm::vec3 &To, const gg::Color &c);

        inline bool key(gg::KEYCODES keyCode){ return KEYS[keyCode];};
        bool Initialize();

        void SetMapZoneVisibility(const int8_t &zone,const bool &flag);

        void resetClickVariable();

    private:

        Omicron();

        gg::Clock FPS_Clock;

        TNodo* ESCENA;
        TNodo* OKAMERAS_LAYER;
        TNodo* LIGHTS_LAYER;
        TNodo* BUFFERS_LAYER;
        GLFWwindow* window;
        AssetManager* gestorRecursos;
        Debug* Debugger;

        TNodo* main_camera;
        TCamara* cam_;

        uint16_t FPS;


        std::vector<TNodo*> ZONES;

        TNodo* bindTransform(const glm::vec3& pos, const glm::quat& rot, TNodo* FATHER);

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        static bool* KEYS;
        static bool LCLICK;
        //static bool clicked;
        static int wheel;
        static int IdButon;

        static int Half_Window_Width;
        static int Half_Window_Height;

};

#endif
