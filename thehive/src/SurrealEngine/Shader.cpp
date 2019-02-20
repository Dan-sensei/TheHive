#include "Shader.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

std::unordered_map<std::string, unsigned int> Shader::UniformLocations;


Shader::Shader(){
}

Shader::Shader(const Shader& orig){
    // std::cout << "Copiando Shader" << '\n';
    ShaderID = orig.ShaderID;
}

Shader::~Shader(){
    // std::cout << "Deleting Shader..." << '\n';
    glDeleteProgram(ShaderID);
}


int Shader::getUniformLocation(std::string target){
    auto UniformSearch = UniformLocations.find(target);
    if(UniformSearch != UniformLocations.end()){
        return UniformSearch->second;
    }
    else{
        int location = glGetUniformLocation(ShaderID, target.c_str());
        UniformLocations[target] = location;
        return location;
    }
}

void Shader::Bind() const{
    glUseProgram(ShaderID);
}

bool Shader::loadFiles(const char* VertexShader, const char* GeometryShader, const char* FragmentShader){

    unsigned int VertexShaderID, GeometryShaderID, FragmentShaderID;

    if(VertexShader != nullptr)        VertexShaderID   = loadShader(VertexShader, GL_VERTEX_SHADER);
    else  { std::cout << "  -Error: Null VertexShader" << '\n'; return false;    }

    if(GeometryShader != nullptr)      GeometryShaderID = loadShader(GeometryShader, GL_GEOMETRY_SHADER);

    if(FragmentShader != nullptr)      FragmentShaderID = loadShader(FragmentShader, GL_FRAGMENT_SHADER);
    else  { std::cout << "  -Error: Null FragmentShader" << '\n'; return false;    }

    ShaderID = glCreateProgram();

    if(VertexShaderID   != -1)      glAttachShader(ShaderID, VertexShaderID);
    else                            glDeleteProgram(ShaderID);


    if(GeometryShaderID != -1)      glAttachShader(ShaderID, GeometryShaderID);
    else if(GeometryShader)         glDeleteProgram(ShaderID);


    if(FragmentShaderID != -1)      glAttachShader(ShaderID, FragmentShaderID);
    else                            glDeleteProgram(ShaderID);

    glLinkProgram(ShaderID);

    GLint result = GL_FALSE;
	int info;
    glGetProgramiv(ShaderID, GL_LINK_STATUS, &result);
	glGetProgramiv(ShaderID, GL_INFO_LOG_LENGTH, &info);
	if ( info > 0 ){
		std::vector<char> ProgramErrorMessage(info+1);
		glGetProgramInfoLog(ShaderID, info, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
        glDeleteProgram(ShaderID);
	}

    if(VertexShaderID   != -1){
        glDetachShader(ShaderID, VertexShaderID);
        glDeleteShader(VertexShaderID);
    }

    if(GeometryShaderID != -1)    {
        glDetachShader(ShaderID, GeometryShaderID);
        glDeleteShader(GeometryShaderID);
    }

    if(FragmentShaderID != -1){
        glDetachShader(ShaderID, FragmentShaderID);
        glDeleteShader(FragmentShaderID);
    }

    if(info > 0)    return false;

    return true;
}

unsigned int Shader::loadShader(const char *path, unsigned int type){
    //Leyendo shader
    std::string shaderSource;
    std::ifstream shaderStream(path, std::ios::in);
    if(!shaderStream.is_open()){
        std::cout << "No se pudo abrir el archivo: '" << path << "'" << std::endl;
        return -1;
    }

    std::stringstream starbustStream;
    starbustStream << shaderStream.rdbuf();
    shaderSource = starbustStream.str();
    shaderStream.close();

    unsigned int ID = glCreateShader(type);

    //Compilando Shader
    std::cout << "Comprobando shader: " << path << std::endl;
	char const * src = shaderSource.c_str();
	glShaderSource(ID, 1, &src , NULL);
	glCompileShader(ID);

    GLint info = GL_FALSE;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &info);

    if(info == GL_FALSE){
        std::cout << "Fallo en la compilación del shader" << std::endl;

        GLint infoLink;
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLink);
        std::vector<char> shaderError(infoLink+1);
		glGetShaderInfoLog(ID, infoLink, NULL, &shaderError[0]);
		std::cout << &shaderError[0] << std::endl;

        glDeleteShader(ID);
        ID = -1;
    }

    return ID;
}
