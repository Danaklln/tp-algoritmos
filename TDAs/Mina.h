#ifndef MINA_H_
#define MINA_H_

#include "Jugador.h"

class Mina{
    private:
        unsigned int poder;
        Jugador* ptrPropietario;

    public:
        /*
        * Pre: Recibe un numero mayor que cero.
        * Post: Inicializa Mina indicando el poder de la misma.
        */
        Mina(unsigned int poderMina, Jugador* ptrJugador){
            this->poder = poderMina;
            this->ptrPropietario = ptrJugador;
        }

        /*
        * Pre: -
        * Post: Devuelve el poder de la Mina.
        */
        unsigned int getPoder(){
            return this->poder;
        }

        /*
        * Pre: -
        * Post: Devuelve puntero al jugador propietario de la mina.
        */
        Jugador* getPropietario(){
            return this->ptrPropietario;
        }
};


#endif /* MINA_H_ */