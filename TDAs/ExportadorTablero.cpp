#include "ExportadorTablero.h"
#include "Tablero.h"
#include "Celda.h"
#include "Tesoro.h"
#include "bitmapConfig.h"
#include "bitmap_image.hpp"
#include <iostream>
#include <string>
#include <sstream>

template <typename T>
string NumberToString(T pNumber)
{
 ostringstream oOStrStream;
 oOStrStream << pNumber;
 return oOStrStream.str();
}

ExportadorTablero::ExportadorTablero(Tablero* tablero)
{
    if (!tablero)
    {
        throw "[ERROR] No se proporcionó un tablero";
    }

    uint tableroX = tablero->getDimensionX(),
         tableroY = tablero->getDimensionY();

    this->imageW = tableroX * (TABLERO_TAMANIO_CUADRADO + 2);
    this->imageH = tableroY * (TABLERO_TAMANIO_CUADRADO + 2);
    this->tableroX = tableroX;
    this->tableroY = tableroY;
    this->cantPisos = tablero->getDimensionZ();
}

void ExportadorTablero::dibujarTesoroBlindado(bitmap_image& image, unsigned int x, unsigned int y)
{
    image_drawer draw(image);

    draw.pen_color(COLOR_TESORO_BLINDADO_R,
                   COLOR_TESORO_BLINDADO_G,
                   COLOR_TESORO_BLINDADO_B);
    draw.pen_width(2);

    draw.rectangle(x * (TABLERO_TAMANIO_CUADRADO + 2) + 3,
                   y * (TABLERO_TAMANIO_CUADRADO + 2) + 3,
                   (x + 1) * (TABLERO_TAMANIO_CUADRADO + 2) - 2,
                   (y + 1) * (TABLERO_TAMANIO_CUADRADO + 2) - 2
                   );
}

void ExportadorTablero::dibujarTesoro(bitmap_image& image, unsigned int x, unsigned int y, bool esTesoroRival)
{
    image_drawer draw(image);

    draw.pen_color(esTesoroRival ? COLOR_TESORO_RIVAL_R : COLOR_TESORO_PROPIO_R,
                   esTesoroRival ? COLOR_TESORO_RIVAL_G : COLOR_TESORO_PROPIO_G,
                   esTesoroRival ? COLOR_TESORO_RIVAL_B : COLOR_TESORO_PROPIO_B);
    draw.pen_width(2);

    draw.rectangle(x * (TABLERO_TAMANIO_CUADRADO + 2) + (esTesoroRival ? 3 : 1),
                   y * (TABLERO_TAMANIO_CUADRADO + 2) + (esTesoroRival ? 3 : 1),
                   (x + 1) * (TABLERO_TAMANIO_CUADRADO + 2) - (esTesoroRival ? 4 : 2),
                   (y + 1) * (TABLERO_TAMANIO_CUADRADO + 2) - (esTesoroRival ? 4 : 2)
                   );
}

void ExportadorTablero::dibujarGrilla(bitmap_image& imagen)
{
    if (!imagen) throw "[ERROR] No se proporcionó una imagen";
    imagen.clear();
    imagen.set_all_channels(COLOR_CUADRADO_R, COLOR_CUADRADO_G, COLOR_CUADRADO_B);
    image_drawer draw(imagen);
    draw.pen_color(0, 0, 0);
    for (unsigned int i = 0; i <= this->imageH / (TABLERO_TAMANIO_CUADRADO + 2); i++)
    {
        draw.horiztonal_line_segment(0, this->imageW, i * (TABLERO_TAMANIO_CUADRADO + 2));
    }

    for (unsigned int j = 0; j <= this->imageW / (TABLERO_TAMANIO_CUADRADO + 2); j++)
    {
        draw.vertical_line_segment(0, this->imageH, j * (TABLERO_TAMANIO_CUADRADO + 2));
    }
}

void ExportadorTablero::dibujarEspia(bitmap_image& image, unsigned int x, unsigned int y)
{
    if (!image || x > this->tableroX || y > this->tableroY) throw "[ERROR] Parametros inválidos";

    image_drawer draw(image);

    draw.pen_color(COLOR_ESPIA_R,
                   COLOR_ESPIA_G,
                   COLOR_ESPIA_B);

    draw.pen_width(1);

    draw.triangle(x * (TABLERO_TAMANIO_CUADRADO + 2),
                  (y + 1) * (TABLERO_TAMANIO_CUADRADO + 2),
                  (x + 1) * (TABLERO_TAMANIO_CUADRADO + 2),
                  (y + 1) * (TABLERO_TAMANIO_CUADRADO + 2),
                  (x + 1) * (TABLERO_TAMANIO_CUADRADO + 2) - TABLERO_TAMANIO_CUADRADO / 2,
                  y * (TABLERO_TAMANIO_CUADRADO + 2)
                  );
}

void ExportadorTablero::dibujarMina(bitmap_image& image, unsigned int x, unsigned int y)
{
    if (!image || x > this->tableroX || y > this->tableroY) throw "[ERROR] Parametros inválidos";

    image_drawer draw(image);

    draw.pen_color(COLOR_MINA_R, COLOR_MINA_G, COLOR_MINA_B);

    draw.pen_width(2);
    draw.circle((x + 1) * (TABLERO_TAMANIO_CUADRADO + 2) - TABLERO_TAMANIO_CUADRADO / 2 - 1, // El -1 es por la forma que redondea c++
                (y + 1) * (TABLERO_TAMANIO_CUADRADO + 2) - TABLERO_TAMANIO_CUADRADO / 2 - 1, // "
                (TABLERO_TAMANIO_CUADRADO + 2) / 2);
}

void ExportadorTablero::dibujarCruz(bitmap_image& image, unsigned int x, unsigned int y)
{
    image_drawer draw(image);

    draw.pen_color(COLOR_CASILLA_INACTIVA_R,
                   COLOR_CASILLA_INACTIVA_G,
                   COLOR_CASILLA_INACTIVA_B);
    draw.pen_width(2);

    draw.line_segment(
        x * (TABLERO_TAMANIO_CUADRADO + 2),
        (y) * (TABLERO_TAMANIO_CUADRADO + 2),
        (x + 1) * (TABLERO_TAMANIO_CUADRADO + 2),
        (y + 1) * (TABLERO_TAMANIO_CUADRADO + 2)
    );

    draw.line_segment(
        (x + 1) * (TABLERO_TAMANIO_CUADRADO + 2),
        y * (TABLERO_TAMANIO_CUADRADO + 2),
        x * (TABLERO_TAMANIO_CUADRADO + 2),
        (y + 1) * (TABLERO_TAMANIO_CUADRADO + 2)
    );
}

void ExportadorTablero::exportarPisoTablero(Tablero *tablero, Jugador* jugador, uint piso)
{
    bitmap_image imagenAExportar(this->imageW + 1, this->imageH + 1);
    dibujarGrilla(imagenAExportar);
    Lista<Lista<Celda*>*>* pisoActual = tablero->obtenerPiso(piso);

    pisoActual->iniciarCursor();
    while(pisoActual->avanzarCursor())
    {
        Lista<Celda*>* pisoActualX = pisoActual->obtenerCursor();
        pisoActualX->iniciarCursor();

        while(pisoActualX->avanzarCursor())
        {
            Celda* celdaActual = pisoActualX->obtenerCursor();

            if (celdaActual->getEstado() == CELDA_INACTIVA)
            {
                this->dibujarCruz(imagenAExportar, celdaActual->getCoordenadaX() - 1, celdaActual->getCoordenadaY() - 1);
                continue; // No es necesario dibujar nada mas
            }

            if (celdaActual->tieneTesoro(jugador))
            {
                if (celdaActual->obtenerTesoroDeJugador(jugador)->getEstadoTesoro() == TESORO_BLINDADO)
                {
                  this->dibujarTesoroBlindado(imagenAExportar, celdaActual->getCoordenadaX() - 1, celdaActual->getCoordenadaY() - 1);
                }
                else
                {
                  this->dibujarTesoro(imagenAExportar, celdaActual->getCoordenadaX() - 1, celdaActual->getCoordenadaY() - 1, false);
                }
            }

            if (celdaActual->tieneTesoroRivalRevelado(jugador))
            {
                this->dibujarTesoro(imagenAExportar, celdaActual->getCoordenadaX() - 1, celdaActual->getCoordenadaY() - 1, true);
            }


            if (celdaActual->hayMinaEnLaCasilla() && celdaActual->tieneMina(jugador))
            {
                this->dibujarMina(imagenAExportar, celdaActual->getCoordenadaX() - 1, celdaActual->getCoordenadaY() - 1);
            }

            if (celdaActual->hayEspiaEnLaCasilla() && celdaActual->obtenerEspia()->getPropietario() == jugador)
            {
                this->dibujarEspia(imagenAExportar, celdaActual->getCoordenadaX() - 1, celdaActual->getCoordenadaY() - 1);
            }
        }
    }

    imagenAExportar.save_image("Tablero_piso_" + NumberToString(piso) + ".bmp");
}


void ExportadorTablero::exportarTablero(Tablero* tablero, Jugador* jugador)
{
    for (unsigned int i = 1; i <= this->cantPisos; i++)
    {
        exportarPisoTablero(tablero, jugador, i);
    }
}

