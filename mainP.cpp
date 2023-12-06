#include "./TDAs/Juego.h"
#include <iostream>

using namespace std;

int main() {
  unsigned int cantidadDeJugadores = 2, dimensionX = 3, dimensionY = 3, dimensionZ = 2, numeroDeTesorosPorJugador = 3;
  cout << "Bienvenido a TesoroBinario, para empezar a jugar especifique las dimensiones del tablero (ancho largo alto): " << endl;
  cin >> dimensionX >> dimensionY >> dimensionZ;
  cout << "Ingrese la cantidad de jugadores" << endl;
  cin >> cantidadDeJugadores;
  Juego* ptrjuego = new Juego(cantidadDeJugadores, dimensionX, dimensionY, dimensionZ);
  ptrjuego->iniciarJuego(numeroDeTesorosPorJugador);
  ptrjuego->jugarJuego();
  delete ptrjuego;
  return 0;
}
