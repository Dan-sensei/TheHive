#include "TEntidad.hpp"

std::stack<glm::mat4> TEntidad::matrixStack;
glm::mat4 TEntidad::projMatrix = glm::mat4();
glm::mat4 TEntidad::viewMatrix = glm::mat4();
glm::mat4 TEntidad::modelMatrix = glm::mat4();

TEntidad::~TEntidad(){}
