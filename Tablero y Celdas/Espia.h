#ifndef ESPIA_H_
#define ESPIA_H_

#include "Jugador.h"

class Espia
{
private:
    Jugador *propietario;
    unsigned int coordenadaCeldaContenedoraX;
    unsigned int coordenadaCeldaContenedoraY;
    unsigned int coordenadaCeldaContenedoraZ;

public:

    /*
	 * Pre: -
	 * Post: Inicializa Espia indicando el jugador propietario del mismo y las coordenadas del Espia
	 */
    Espia(Jugador* jugador, unsigned int x, unsigned int y, unsigned int z)
    {
        this-> propietario = jugador;
        this-> coordenadaCeldaContenedoraX = x;
        this-> coordenadaCeldaContenedoraY = y;
        this-> coordenadaCeldaContenedoraZ = z;
    };

	/*
	 * Pre: -
	 * Post: Devuelve el jugador propietario del Espia
	 */
    Jugador* getPropietario()
    {
        return this-> propietario;
    }

	/*
	 * Pre: -
	 * Post: Devuelve la coordenada X de la celda, contenedora del espia, del jugador actual
	 */
    unsigned int getCeldaContenedoraX()
    {
        return this->coordenadaCeldaContenedoraX;
    }

	/*
	 * Pre: -
	 * Post: Devuelve la coordenada Y de la celda, contenedora del espia, del jugador actual
	 */
    unsigned int getCeldaContenedoraY()
    {
        return this->coordenadaCeldaContenedoraY;
    }

    /*
	 * Pre: -
	 * Post: Devuelve la coordenada Z de la celda, contenedora del espia, del jugador actual
	 */
    unsigned int getCeldaContenedoraZ()
    {
        return this->coordenadaCeldaContenedoraZ;
    }

};


#endif /* ESPIA_H_ */
