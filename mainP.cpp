#include "./TDAs/Juego.h"
#include <iostream>

using namespace std;

int main() {
  bool condicion = false;
  unsigned int cantidadDeJugadores = 2, dimensionX = 3, dimensionY = 3, dimensionZ = 3, numeroDeTesorosPorJugador = 3;
  cout << "Bienvenido a TesoroBinario, para empezar a jugar especifique las dimensiones del tablero mayores o iguales a 3 (ancho largo alto): " << endl;
  while(!condicion){
    cin >> dimensionX >> dimensionY >> dimensionZ;
    if(dimensionX >= 3 && dimensionY >= 3  && dimensionZ >= 3){
        condicion = true;
    }
    else{
        cout << "dimensiones invalidas, para empezar a jugar especifique las dimensiones del tablero mayores o iguales a 3 (ancho largo alto): " << endl;
    }
  }
  cout << "Ingrese la cantidad de jugadores" << endl;
  cin >> cantidadDeJugadores;
  Juego* ptrjuego = new Juego(cantidadDeJugadores, dimensionX, dimensionY, dimensionZ);
  ptrjuego->iniciarJuego(numeroDeTesorosPorJugador);
  ptrjuego->jugarJuego();
  delete ptrjuego;
  return 0;
}
