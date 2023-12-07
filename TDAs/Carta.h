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
    SALTAR_PROXIMO_TURNO,
    TRIPLE_MINA
};

class Carta{

private:
    TipoDeCarta carta;

public:

    /**
    * Pre: -
    * Post: Crea una instancia de carta cuyo tipo es al azar
    */
    Carta(){
        int limiteInferior = 0;
        int limiteSuperior = 5;
        this->carta = TipoDeCarta(limiteInferior + rand()%(limiteSuperior +1 - limiteInferior));
    }

    /**
    * pre: -
    * post: imprime el tipo de carta
    */
    void printTipoDeCarta(){
        std::string nombresCartas[6]={"Blindaje","Radar","Partir Tesoro","Romper Blindaje","Tesoro en Peligro","Triple Mina"};
        std::cout<<"Esta carta es: " << nombresCartas[this->getTipoDeCarta()] << std::endl;
    }

    /**
    * pre: -
    * post: elimina los elementos
    */
    virtual ~Carta(){}

    /**
    * pre: -
    * post: devuelve la el tipo de la carta
    */
    TipoDeCarta getTipoDeCarta(){
        return this->carta;
    }

};

#endif
