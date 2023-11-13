#ifndef GUARD_BITMAP_CONFIG
#define GUARD_BITMAP_CONFIG
#include <string>

// Archivo de configuracion para las constantes

const unsigned int TABLERO_TAMANIO_CUADRADO = 32;
const std::string NOMBRE_ARCHIVO_TABLERO = "Tablero.bmp"; // Extension importante!

const struct { // Azul... medio raro
    unsigned int R = 30;
    unsigned int G = 84;
    unsigned int B = 173;
} COLOR_CUADRADO;

const struct { // Blanco
    unsigned int R = 255;
    unsigned int G = 255;
    unsigned int B = 255;
} COLOR_LINEAS;

const struct {
    unsigned int R = 53;
    unsigned int G = 255;
    unsigned int B = 31;
} COLOR_TESORO;

const struct {
    unsigned int R = 255;
    unsigned int G = 46;
    unsigned int B = 31;
} COLOR_TESORO_RIVAL;

const struct {
    unsigned int R = 255;
    unsigned int G = 255;
    unsigned int B = 255;
} COLOR_ESPIA;

const struct {
    unsigned int R = 255;
    unsigned int G = 0;
    unsigned int B = 0;
} COLOR_MINA;

const struct {
    unsigned int R = 255;
    unsigned int G = 255;
    unsigned int B = 255;
} COLOR_CASILLA_INACTIVA;

#endif
