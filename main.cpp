/*
*           ESTE ES UN MAIN.CPP DE PRUEBA.
*   EL MAIN.CPP ANTERIOR SE RENOMBRO A MAIN.CPP.OLD
*/
#include "./TDAs/Jugador.h"
#include "./TDAs/ExportadorTablero.h"
#include "./TDAs/Tablero.h"
#include "./TDAs/Tesoro.h"
#include "TDAs/Mina.h"

int main()
{
    Jugador* jugadorUno = new Jugador(1);
    Jugador* jugadorDos = new Jugador(2);
    Tablero* tablero = new Tablero(3, 4, 3, jugadorUno);
    ExportadorTablero* exportadorTablero = new ExportadorTablero(tablero);

    // Agregando objetos al tablero con jugadorUno de propietario en el segundo piso
    tablero->agregarNuevoEspia(jugadorUno, 1, 1, 1);
    tablero->agregarNuevoEspia(jugadorUno, 1, 4, 1);
    tablero->agregarNuevoTesoro(jugadorUno, 1, 2, 1);
    tablero->agregarNuevoTesoro(jugadorDos, 1, 2, 1);
    tablero->obtenerPtrCelda(1, 2, 1)->obtenerTesoroDeJugador(jugadorDos)->setVisibilidad(TESORO_REVELADO);
    tablero->obtenerPtrCelda(1, 2, 1)->obtenerTesoroDeJugador(jugadorDos)->setVisibilidad(TESORO_OCULTO);
    tablero->obtenerPtrCelda(1,1,1)->addMina(new Mina(5, jugadorUno));
    // Exportando el piso dos del tablero
    exportadorTablero->exportarPisoTablero(tablero, jugadorUno, 1);
}
