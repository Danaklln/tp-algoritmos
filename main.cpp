#include "./TDAs/Jugador.h"
#include "./TDAs/ExportadorTablero.h"
#include "./TDAs/Tablero.h"
#include "./TDAs/Tesoro.h"
#include "./TDAs/Mina.h"
// #include "./TDAs/TesoroBinario.h"
#include <iostream>

using namespace std;

int main()
{
    int dimensionX,
        dimensionY,
        dimensionZ,
        cantJugadores;

    cout << "Bienvenido a TesoroBinario, para empezar a jugar especifique las dimensiones del tablero (ancho largo alto): " << endl;
    cin >> dimensionX >> dimensionY >> dimensionZ;
    cout << "Ingrese la cantidad de jugadores" << endl;
    cin >> cantJugadores;

    // TesoroBinario* instanciaDeJuego = new TesoroBinario(); Crear instancia con los valores que ingreso el usuraio

    while(!instanciaDeJuego->terminoElJuego())
    {
        cout << "El turno actual es del jugador " << instanciaDeJuego->obtenerTurnoActual()->getId();
        // Pedirle opciones al usuario.
        //  Poner espia
        //  Sacar carta
        //     Usar carta
    }

}
