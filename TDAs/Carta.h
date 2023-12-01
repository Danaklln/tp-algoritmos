#ifndef CARTA_H_
#define CARTA_H_
#include <iostream>
#include<stdlib.h>
#include<time.h>

enum TipoDeCarta{
    BLINDAJE,
    RADAR,
    PARTIR_TESORO,
    ROMPER_BLINDAJE,
    TESORO_EN_PELIGRO,
    TRIPLE_MINA
};

class Carta{

private:
    TipoDeCarta carta;

public:
     
    /**
    * pre:
    * post:
    */
    Carta(){
        int limiteInferior = 0;  
        int limiteSuperior = 5;                                       
        srand(time(NULL));
        this->carta = TipoDeCarta(limiteInferior + rand()%(limiteSuperior +1 - limiteInferior));
    }
    

    virtual ~Carta(){}

    TipoDeCarta getTipoDeCarta(){
        return this->carta;
    }
 
};

#endif
