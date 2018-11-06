

#include "hoja.hpp"


hoja::hoja(){}
hoja::~hoja(){}



    void hoja::onInitialize(){}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
    Status hoja::update() {
      std::cout << "hoja update" <<getStatus() << '\n';
      return BH_SUCCESS;}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
    void hoja::onTerminate(Status state){
      std::cout << "hoja onTerminate" <<state << '\n';

    }

 /* BEHAVIOR_HPP */
