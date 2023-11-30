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
    Tablero* tablero = new Tablero(3, 3, 3, jugadorUno);
    ExportadorTablero* exportadorTablero = new ExportadorTablero(tablero);

    // Agregando objetos al tablero con jugadorUno de propietario en el segundo piso
    std::cout << tablero->agregarNuevoEspia(jugadorUno, 1, 1, 2);
    std::cout << tablero->agregarNuevoEspia(jugadorUno, 1, 2, 2);
    std::cout << tablero->agregarNuevoEspia(jugadorUno, 1, 3, 2);
    tablero->agregarNuevoTesoro(jugadorUno, 1, 2, 2);
    tablero->agregarNuevoTesoro(jugadorDos, 1, 1, 2);

    // Exportando el piso dos del tablero
    exportadorTablero->exportarPisoTablero(tablero, jugadorUno, 2);
}
