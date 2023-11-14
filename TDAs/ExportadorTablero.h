#ifndef GUARD_EXPORTADOR_PRINTER
#define GUARD_EXPORTADOR_PRINTER

#include "Tablero.h"
#include "bitmap_image.hpp"
#include "bitmapConfig.h"

typedef unsigned int uint;

class ExportadorTablero {
private:
    uint tableroX;
    uint tableroY;
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
   * Pre: Se debe proporcionar un tablero válido y un piso > 0
   * Post: Se exporta el piso del tablero proporcionado a un archivo BMP nombrado
   * segun el archivo de configuracion.
   */
  void exportarPisoTablero(Tablero &tablero, uint piso);
};

#endif
