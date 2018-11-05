#include "Material.hpp"

irr::video::IVideoDriver* Material::driver = nullptr;

Material::Material() {

}

Material::Material(const std::string& path) {
    setTexture(path);
}

Material::Material(const Material &orig) {
    mMaterial = orig.mMaterial;
}

Material::~Material() {

}

void Material::setTexture(const std::string &path) {
    mMaterial.setTexture(0, driver->getTexture(path.c_str()));
}
