#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <map>
#include <unordered_map>
#include <string>

class Shader{
    public:
        Shader();
        Shader(const Shader& orig);
        ~Shader();

        bool loadFiles(const char* VertexShader, const char* GeometryShader, const char* FragmentShader);
        int getUniformLocation(std::string target);
        void Bind() const;
        void Unbind() const;
        void freeBuffer();

        GLuint getID(){return ShaderID;}

    private:
        unsigned int ShaderID;
        unsigned int loadShader(const char *path, unsigned int type);
        static std::unordered_map<std::string, unsigned int> UniformLocations;
};

#endif
