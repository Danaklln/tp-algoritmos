#include <iostream>
#include "Lista.h"
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "Celda.h"
#include "Tablero.h"

using namespace std;

int main() {
	unsigned int dimensionX = 4, dimensionY = 3, dimensionZ = 2;
	Jugador* ptrJugador1 = new Jugador(1); Jugador* ptrJugador2 = new Jugador(2);
	Tablero* ptrtablerodeprueba = new Tablero(dimensionX, dimensionY, dimensionZ, ptrJugador1);
	ptrtablerodeprueba->agregarNuevoTesoro(ptrJugador1,2,2,1);
	ptrtablerodeprueba->agregarNuevoTesoro(ptrJugador1,3,3,1);
	ptrtablerodeprueba->agregarNuevoEspia(ptrJugador1,2,2,1);
	ptrtablerodeprueba->agregarNuevaMina(2,ptrJugador1,2,3,1);
	ptrtablerodeprueba->agregarNuevoTesoro(ptrJugador2,1,1,1);
	ptrtablerodeprueba->agregarNuevoEspia(ptrJugador2,2,1,1);
	ptrtablerodeprueba->mostrarPiso(1);
	ptrtablerodeprueba->pasarTurnoTablero(ptrJugador2);
	ptrtablerodeprueba->agregarNuevoTesoro(ptrJugador2,2,2,1);
	ptrtablerodeprueba->agregarNuevoEspia(ptrJugador2,3,3,1);
	ptrtablerodeprueba->mostrarPiso(1);
	ptrtablerodeprueba->pasarTurnoTablero(ptrJugador1);
	ptrtablerodeprueba->mostrarPiso(1);
	ptrtablerodeprueba->pasarTurnoTablero(ptrJugador1);ptrtablerodeprueba->pasarTurnoTablero(ptrJugador1);
	ptrtablerodeprueba->pasarTurnoTablero(ptrJugador1);ptrtablerodeprueba->pasarTurnoTablero(ptrJugador1);
	ptrtablerodeprueba->mostrarPiso(1);
	delete ptrtablerodeprueba;
	delete ptrJugador1;
	delete ptrJugador2;
	return 0;
}
