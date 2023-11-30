/*
*           ESTE ES UN MAIN.CPP DE PRUEBA.
*   EL MAIN.CPP ANTERIOR SE RENOMBRO A MAIN.CPP.OLD
*/
#include "./TDAs/Jugador.h"
#include "./TDAs/ExportadorTablero.h"
#include "./TDAs/Tablero.h"
#include "./TDAs/Tesoro.h"

int main()
{
    Jugador* jugadorUno = new Jugador(1);
    Jugador* jugadorDos = new Jugador(2);
    Tablero* tablero = new Tablero(3, 5, 3, jugadorUno);
    ExportadorTablero* exportadorTablero = new ExportadorTablero(tablero);

    // Agregando objetos al tablero con jugadorUno de propietario en el segundo piso
    tablero->agregarNuevoEspia(jugadorUno, 1, 1, 1);
    tablero->agregarNuevoEspia(jugadorUno, 1, 2, 1);
    tablero->agregarNuevoEspia(jugadorUno, 1, 3, 1);
    tablero->agregarNuevoEspia(jugadorUno, 1, 4, 1);
    tablero->agregarNuevoEspia(jugadorUno, 1, 5, 1);
    tablero->agregarNuevoTesoro(jugadorUno, 1, 2, 1);
    tablero->agregarNuevoTesoro(jugadorDos, 1, 2, 1);

    // Exportando el piso dos del tablero
    exportadorTablero->exportarPisoTablero(tablero, jugadorUno, 1);
}
