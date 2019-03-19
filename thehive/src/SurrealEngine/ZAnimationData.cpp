#include "ZAnimationData.hpp"
#include "AssetManager.hpp"

ZAnimationData::ZAnimationData(){
    Keyframes.reserve(5);
}
ZAnimationData::ZAnimationData(const ZAnimationData &orig)
:Keyframes(orig.Keyframes){}
ZAnimationData::~ZAnimationData(){}

void ZAnimationData::addKeyframe(const std::string &PathToKeyframeModel){
    Keyframes.emplace_back(Singleton<AssetManager>::Instance()->getMeshData(PathToKeyframeModel));
}
