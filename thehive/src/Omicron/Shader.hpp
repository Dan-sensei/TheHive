#ifndef __SHADER_H
#define __SHADER_H

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
        int getUniformBlockLocation(std::string target);

        void Bind() const;
        void Unbind() const;
        void freeBuffer();

        unsigned int getID(){return ShaderID;}

    private:
        unsigned int ShaderID;
        unsigned int loadShader(const char *path, unsigned int type);
        std::map<std::string, unsigned int> UniformLocations;
        std::map<std::string, unsigned int> UniformBlockLocations;
};

#endif
