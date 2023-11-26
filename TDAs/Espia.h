#ifndef ESPIA_H_
#define ESPIA_H_

#include "Jugador.h"

class Espia{

    private:

        Jugador* ptrPropietario;

    public:
    
        /*
        * Pre: Recibe puntero a un jugador y 3 numeros mayores a cero.
        * Post: Inicializa Espia indicando el jugador propietario del mismo y las coordenadas del Espia.
        */
        Espia(Jugador* ptrJugador){
            this->ptrPropietario = ptrJugador;
        };

        /*
        * Pre: -
        * Post: Devuelve puntero al jugador propietario del Espia
        */
        Jugador* getPropietario(){
            return this->ptrPropietario;
        }
};

#endif /* ESPIA_H_ */
