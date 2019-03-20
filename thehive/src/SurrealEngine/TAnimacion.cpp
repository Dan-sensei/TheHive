#include "TAnimacion.hpp"


TAnimacion::TAnimacion(){}
TAnimacion::~TAnimacion(){}

TAnimacion::TAnimacion(std::array<ZStaticMesh, 5> &poses_){
    poses = poses_;
}

// Se quedan vacios
void TAnimacion::beginDraw(){}
void TAnimacion::endDraw(){}
