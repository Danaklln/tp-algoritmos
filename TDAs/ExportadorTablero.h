#ifndef GUARD_EXPORTADOR_TABLERO
#define GUARD_EXPORTADOR_TABLERO

#include "Tablero.h"
#include "Jugador.h"
#include "bitmap_image.hpp"
#include "bitmapConfig.h"

typedef unsigned int uint;

class ExportadorTablero {
private:
    uint tableroX;
    uint tableroY;
    uint cantPisos;
    uint imageW;
    uint imageH;

    /*
     * Pre: debe proporcionarse un objeto bitmap_image
     * Post: Modifica el objeto pasado como parámetro para tener la
     * grilla dibujada
     */
    void dibujarGrilla(bitmap_image& imagen);

    /*
     * Pre: Se debe proporcionar un objeto bitmap_image válido y dos coordenadas
     * > 0 dentro del rango del tablero
     * Post: Se modifica el objeto bitmap_image dibujando un tesoro en el casilla
     * correspondiente
     */
    void dibujarTesoro(bitmap_image& image, unsigned int x, unsigned int y, bool esTesoroRival);

    /*
     * Pre: Se debe proporcionar un objeto bitmap_image válido y dos coordenadas
     * > 0 dentro del rango del tablero
     * Post: Se modifica el objeto bitmap_image dibujando un espía en el casilla
     * correspondiente
     */
    void dibujarEspia(bitmap_image& image, unsigned int x, unsigned int y);

    /*
     * Pre: Se debe proporcionar un objeto bitmap_image válido y dos coordenadas
     * > 0 dentro del rango del tablero
     * Post: Se modifica el objeto bitmap_image dibujando una mina en el casilla
     * correspondiente
     */
    void dibujarMina(bitmap_image& image, unsigned int x, unsigned int y);

    /*
     * Pre: Se debe proporcionar un objeto bitmap_image válido y dos coordenadas > 0
     * dentro del rango del tablero del juego
     * Post: Se modifica el objeto bitmap_image dibujando una cruz en la casilla
     * correspondiente
     */
    void dibujarCruz(bitmap_image& image, unsigned int x, unsigned int y);

public:
  /*
   * Pre: -
   * Post: Crea una instancia de TableroPrinter
   */
  ExportadorTablero(Tablero *tablero);

  /*
   * Pre: Se debe proporcionar un tablero válido, un jugador valido y un piso > 0 < tableroZ
   * Post: Se exporta el piso del tablero proporcionado en funcion de lo que veria el jugador
   * pasado como parametro
   */
  void exportarPisoTablero(Tablero *tablero, Jugador* jugador, uint piso);
};

#endif
