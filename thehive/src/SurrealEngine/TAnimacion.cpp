#include "TAnimacion.hpp"


TAnimacion::TAnimacion(){}
TAnimacion::~TAnimacion(){}

TAnimacion::TAnimacion(std::array<ZStaticMesh, 5> &poses_){
    poses = poses_;
}

// Se quedan vacios
void TAnimacion::beginDraw(const uint8_t &T_ID){}
void TAnimacion::endDraw(const uint8_t &T_ID){}
