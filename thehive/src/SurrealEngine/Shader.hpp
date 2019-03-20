#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>
#include <map>
#include <string>

class Shader{
    public:
        Shader();
        Shader(const Shader& orig);
        ~Shader();

        bool loadFiles(const char* VertexShader, const char* GeometryShader, const char* FragmentShader);
        int getUniformLocation(std::string target);
        int getAttribLocation(std::string target);

        void Bind() const;
        void Unbind() const;
        void freeBuffer();

        GLuint getID(){return ShaderID;}

    private:
        unsigned int ShaderID;
        unsigned int loadShader(const char *path, unsigned int type);
        std::map<std::string, unsigned int> UniformLocations;
        std::map<std::string, unsigned int> AtribLocations;
};

#endif
