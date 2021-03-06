#ifndef DEBUG_H
#define DEBUG_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <time.h>
#include <stdarg.h>
#define GL_LOG_FILE "gl.log"

#include <Util.hpp>
#include <Omicron/Shader.hpp>

template <typename T>
class Singleton;

class Debug{
    friend class Singleton<Debug>;

    private:
        //Debug(const Game& orig) = delete;
        //void operator=(Game const& orig) = delete;

        Shader* LineShader;
        unsigned int LineVAO;
        unsigned int LineVBO;
        unsigned int ColorID;
        unsigned int MVP_ID;
        std::vector<float> Line;


    public:
        Debug();

        void DroLine(const glm::vec3 &Init, const glm::vec3 &End, const gg::Color &c, const glm::mat4 &MVP);
        // void log_gl_params();
        // void _print_shader_info_log(GLuint shader_index);
        // void _print_programme_info_log(GLuint programme);
        // void print_all(GLuint programme);
        // const char* GL_type_to_string(GLenum type);
        // bool is_valid(GLuint programme);
        //
        //
        // bool restart_gl_log();
        // bool gl_log(const char* message, ...);
        // bool gl_log_err(const char* message, ...);
        ~Debug();
};

#endif
