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
    int dimensionX, dimensionY, dimensionZ;
    cout << "Bienvenido a TesoroBinario, para empezar a jugar especifique las dimensiones del tablero (ancho largo alto): ";
    cin >> dimensionX >> dimensionY >> dimensionZ;
    cout << dimensionX << " " << dimensionY << " " << dimensionZ;
    // TesoroBinario* instancia = new TesoroBinario();
}
