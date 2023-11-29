/*
*           ESTE ES UN MAIN.CPP DE PRUEBA.
*   EL MAIN.CPP ANTERIOR SE RENOMBRO A MAIN.CPP.OLD
*/
#include "./TDAs/Jugador.h"
#include "./TDAs/ExportadorTablero.h"
#include "./TDAs/Tablero.h"

int main()
{
    Jugador* jugadorUno = new Jugador(1);
    Tablero* tablero = new Tablero(3, 3, 3, jugadorUno);
    ExportadorTablero* exportadorTablero = new ExportadorTablero(tablero);

    // Agregando objetos al tablero con jugadorUno de propietario en el segundo piso
    tablero->agregarNuevoEspia(jugadorUno, 1, 1, 2);
    tablero->agregarNuevoEspia(jugadorUno, 1, 2, 2);
    tablero->agregarNuevoEspia(jugadorUno, 1, 3, 2);
    tablero->agregarNuevoTesoro(jugadorUno, 1, 1, 2);

    // Exportando el piso dos del tablero
    exportadorTablero->exportarPisoTablero(tablero, jugadorUno, 2);
}
