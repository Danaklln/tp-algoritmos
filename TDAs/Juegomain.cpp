#include <iostream>
#include "Lista.h"
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "Celda.h"
#include "Tablero.h"
#include "Juego.h"

int main() {
	unsigned int numeroDeJugadores = 2, dimensionX = 4, dimensionY = 3, dimensionZ = 2, numeroDeTesorosPorJugador = 1;
	Juego* ptrjuego = new Juego(numeroDeJugadores, dimensionX, dimensionY, dimensionZ);
	ptrjuego->iniciarJuego(numeroDeTesorosPorJugador);
	ptrjuego->jugarJuego();
	delete ptrjuego;
	return 0;
}
