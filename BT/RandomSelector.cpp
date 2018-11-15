#include "RandomSelector.hpp"
#include <random>

//el selector genera un radom cuando se inicializa el selector
 void RandomSelector::onInitialize() {

        int max = m_Children.size()-1;
        cont = 0;
        std::cout<<"el max es"<< max<<'\n';
        m_CurrentChild=m_Children.begin();

        for(int i=0;i<sizeof(secuencia);i++)
            secuencia[i]=-1;



        while(cont<=max){
            std::random_device rd;
            std::default_random_engine gen(rd());
            std::uniform_int_distribution<int> distribution(0,max);
            int x = distribution(gen);

            for(int i=0;i<max;i++){
                if(secuencia[i]!=x){
                    cont++;

                    secuencia[i]=x;

                    std::cout<<"el random es"<< x<<'\n';
                    std::cout<<"Cont es"<< cont<<'\n';
                    std::cout<<"Secuencia "<< i<<"es"<<secuencia[i]<<'\n';
                }
            }
        }

        for(int i=0; i<secuencia[0];i++){
            ++m_CurrentChild;
        }
}

 Status RandomSelector::update() {
     int cont=0;
  while (true) {

    Status s=(*m_CurrentChild)->tick();
    if(s != BH_FAILURE)//{
      //if(s == BH_RUNNING)continue;
      return s;//}
    /*if(s== BH_FAILURE){
          m_CurrentChild.setFailed();
          for(int i=0; i<m_Children.size()-1;;i++){
              if(m_CurrentChild.getFailed()==true)
              cont++;
              ++m_CurrentChild;
          }
          if(cont==m_Children.size()-1){
              return BH_FAILURE;
          }
    }
    */
    if(++m_CurrentChild==m_Children.end()) return BH_FAILURE;
  }
  return BH_INVALID;
}
