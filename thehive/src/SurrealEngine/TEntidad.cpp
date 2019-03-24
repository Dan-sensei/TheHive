#include "TEntidad.hpp"

std::stack<glm::mat4> TEntidad::matrixStack;
glm::mat4 TEntidad::projMatrix;
glm::mat4 TEntidad::viewMatrix;
glm::mat4 TEntidad::modelMatrix;
uint16_t TEntidad::DRAWN = 0;

TEntidad::~TEntidad(){}
void TEntidad::JustRender(){}
void TEntidad::SwitchRasterCulling(){}
