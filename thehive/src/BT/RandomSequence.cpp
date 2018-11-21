#include "RandomSequence.hpp"
#include <random>

//el Sequence genera un radom cuando se inicializa el Sequence
RandomSequence::RandomSequence(){}
RandomSequence::RandomSequence(const RandomSequence &orig):Composite(orig)
{}
 void RandomSequence::onInitialize() {

        max = m_Children.size()-1;
        int cont = 0;

        m_CurrentChild=m_Children.begin();
        secuencia.clear();

        for(int i=0;i<=max;i++)
            secuencia.push_back(-1);



        while(cont<=max){
            bool incluido=false;
            std::random_device rd;
            std::default_random_engine gen(rd());
            std::uniform_int_distribution<int> distribution(0,max);
            int x = distribution(gen);


            for(int i=0;i<=max;i++){
                if(secuencia[i]==x)
                    incluido=true;
            }



            if(!incluido){
                for(int i=0;i<=max;i++){
                    if(secuencia[i]==-1 && !incluido){
                        cont++;

                        incluido=true;
                        secuencia[i]=x;

                        std::cout<<"El random es"<< x<<'\n';


                    }
                }
            }
        }

         for(int i=0; i<secuencia.front();i++){
             ++m_CurrentChild;
         }
}

 Status RandomSequence::update() {

     int cont=0;

     while (true) {

        Status s=(*m_CurrentChild)->tick();

        if(s != BH_SUCCESS)
          return s;

        else{

            cont++;

            if(cont<=max){
                m_CurrentChild=m_Children.begin();

                for(int i=0; i<secuencia[cont];i++){
                    ++m_CurrentChild;
                }
            }
            else{
                 return BH_SUCCESS;
            }
        }
    }
  return BH_INVALID;
}
