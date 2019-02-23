#include "TEntidad.hpp"

std::stack<glm::mat4> TEntidad::matrixStack;
glm::mat4 TEntidad::projMatrix;
glm::mat4 TEntidad::viewMatrix;
glm::mat4 TEntidad::modelMatrix;

glm::vec3 lightPointsList;

TEntidad::~TEntidad(){}
void TEntidad::beginDraw(const uint8_t &T_ID){}
void TEntidad::endDraw(const uint8_t &T_ID){}
