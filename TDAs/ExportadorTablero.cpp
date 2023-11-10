#include "ExportadorTablero.h"
#include "Tablero.h"
#include "bitmapConfig.h"
#include "bitmap_image.hpp"

ExportadorTablero::ExportadorTablero(const Tablero& tablero)
{
    if (!tablero)
    {
        throw "[ERROR] No se procorcionó un tablero";
    }

    uint tableroX =  tablero->getX(),
         tableroY = tableroY->getY();

    this->imageW = tableroX * (TABLERO_TAMANIO_CUADRADO + 2);
    this->imageH = tableroY * (TABLERO_TAMANIO_CUADRADO + 2);
}

void ExportadorTablero::dibujarTesoro(bitmap_image& image, unsigned int x, unsigned int y, bool esTesoroRival)
{
    image_drawer draw(image);

    draw.pen_color(esTesoroRival ? COLOR_TESORO_RIVAL.R : COLOR_TESORO.R,
                   esTesoroRival ? COLOR_TESORO_RIVAL.G : COLOR_TESORO.G,
                   esTesoroRival ? COLOR_TESORO_RIVAL.B : COLOR_TESORO.B);
    draw.pen_width(3);

    draw.rectangle(x * (TABLERO_TAMANIO_CUADRADO + 2),
                   y * (TABLERO_TAMANIO_CUADRADO + 2),
                   (x + 1) * (TABLERO_TAMANIO_CUADRADO + 2),
                   (y + 1) * (TABLERO_TAMANIO_CUADRADO + 2)
                   );
}

void ExportadorTablero::dibujarGrilla(bitmap_image& imagen)
{
    if (!imagen) throw "[ERROR] No se proporcionó una imagen";

    bitmap_image image(this->imageW + 1, this->imageH + 1); // Importante sumar uno para que se dibuje la linea final y no quede cortado.
    imagen.clear();
    imagen.set_all_channels(COLOR_CUADRADO.R, COLOR_CUADRADO.G, COLOR_CUADRADO.B);
    image_drawer draw(image);
    draw.pen_color(0, 0, 0);
    for (int i = 0; i <= this->imageH / (TABLERO_TAMANIO_CUADRADO + 2); i++)
    {
        draw.horiztonal_line_segment(0, this->imageW, i * (TABLERO_TAMANIO_CUADRADO + 2));
    }

    for (int j = 0; j <= this->imageW / (TABLERO_TAMANIO_CUADRADO + 2); j++)
    {
        draw.vertical_line_segment(0, this->imageH, j * (TABLERO_TAMANIO_CUADRADO + 2));
    }
}

void ExportadorTablero::dibujarEspia(bitmap_image& image, unsigned int x, unsigned int y)
{
    if (!image || x > this->tableroX || y > this->tableroY) throw "[ERROR] Parametros inválidos";

    image_drawer draw(image);

    draw.pen_color(COLOR_ESPIA.R,
                   COLOR_ESPIA.G,
                   COLOR_ESPIA.B);

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

    draw.pen_color(COLOR_MINA.R, COLOR_MINA.G, COLOR_MINA.B);
    
    draw.pen_width(2);
    draw.circle(x * (TABLERO_TAMANIO_CUADRADO + 2) - TABLERO_TAMANIO_CUADRADO / 2 - 1, // El -1 es por la forma que redondea c++
                y * (TABLERO_TAMANIO_CUADRADO + 2) - TABLERO_TAMANIO_CUADRADO / 2 - 1, // "
                (TABLERO_TAMANIO_CUADRADO + 2) / 2);
}