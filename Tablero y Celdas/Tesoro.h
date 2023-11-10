#ifndef TESORO_H_
#define TESORO_H_

#include "Jugador.h"

class Tesoro
{
private:
    Jugador *propietario;
    unsigned int coordenadaCeldaContenedoraX;
    unsigned int coordenadaCeldaContenedoraY;
    unsigned int coordenadaCeldaContenedoraZ;

public:

    /*
	 * Pre: -
	 * Post: Inicializa Tesoro indicando el jugador propietario del mismo y las coordenadas del Tesoro
	 */
    Tesoro(Jugador* jugador, unsigned int x, unsigned int y, unsigned int z)
    {
        this-> propietario = jugador;
        this-> coordenadaCeldaContenedoraX = x;
        this-> coordenadaCeldaContenedoraY = y;
        this-> coordenadaCeldaContenedoraZ = z;
    };

	/*
	 * Pre: -
	 * Post: Devuelve el jugador propietario del tesoro
	 */
    Jugador* getPropietario()
    {
        return this-> propietario;
    }

	/*
	 * Pre: -
	 * Post: Devuelve la coordenada X de la celda del jugador actual
	 */
    unsigned int getCeldaContenedoraX()
    {
        return this->coordenadaCeldaContenedoraX;
    }

	/*
	 * Pre: -
	 * Post: Devuelve la coordenada Y de la celda del jugador actual
	 */
    unsigned int getCeldaContenedoraY()
    {
        return this->coordenadaCeldaContenedoraY;
    }

    /*
	 * Pre: -
	 * Post: Devuelve la coordenada Z de la celda del jugador actual
	 */
    unsigned int getCeldaContenedoraZ()
    {
        return this->coordenadaCeldaContenedoraZ;
    }
	/*
	 * Pre: -
	 * Post: Elimina el Tesoro
	 */
};


#endif /* TESORO_H_ */

