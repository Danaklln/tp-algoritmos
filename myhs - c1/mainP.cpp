#include <iostream>
#include "Lista.h"
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "Celda.h"
#include "Tablero.h"
#include "Juego.h"
using namespace std;

int main() {
	unsigned int cantidadDeJugadores = 2, dimensionX = 3, dimensionY = 3, dimensionZ = 2, numeroDeTesorosPorJugador = 3;
	cout << "Bienvenido a TesoroBinario, para empezar a jugar especifique las dimensiones del tablero (ancho largo alto): " << endl;
    cin >> dimensionX >> dimensionY >> dimensionZ;
    cout << "Ingrese la cantidad de jugadores" << endl;
    cin >> cantidadDeJugadores;
	Juego* ptrjuego = new Juego(cantidadDeJugadores, dimensionX, dimensionY, dimensionZ);

	// TesoroBinario* instanciaDeJuego = new TesoroBinario(); Crear instancia con los valores que ingreso el usuraio
    //ExportadorTablero* exportadorTablero = new ExportadorTablero(instanciaDeJuego->obtenerTablero());
	ptrjuego->iniciarJuego(numeroDeTesorosPorJugador);
	ptrjuego->jugarJuego();
	// Pedirle opciones al usuario.
        //  Poner espia
        //  Sacar carta
        //     Usar carta
        //

        // Para exportar el tablero, se debe hacer
        
        // JUGADOR TERMINA SU TURNO ///IRIA EN JUEGO
        /*
        *    Es importante que primero termine el turno y luego se exporte, de esa manera se reflejan los cambios correctamente para el proximo jugador
        */
        //exportadorTablero->exportarTablero(instanciaDeJuego->obtenerTablero(), instanciaDeJuego->obtenerTurnoActual());
	delete ptrjuego;
	return 0;
}

