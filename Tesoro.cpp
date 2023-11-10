#include "Tesoro.h"
#include "Jugador.h"

    Tesoro::Tesoro(Jugador*, unsigned int x, unsigned int y, unsigned int z)
    {
        this-> propietario = new Jugador*;
        this-> coordenadaCeldaContenedoraX = x;
        this-> coordenadaCeldaContenedoraY = y;
        this-> coordenadaCeldaContenedoraZ = z;
    }

    Jugador* Tesoro:: getPropietario()
    {
        this-> propietario;
    }

    unsigned int Tesoro::getCeldaContenedoraX()
    {
        this->coordenadaCeldaContenedoraX;
    }

    unsigned int Tesoro::getCeldaContenedoraY()
    {
        this->coordenadaCeldaContenedoraY;
    }

    unsigned int Tesoro::getCeldaContenedoraZ()
    {
        this->coordenadaCeldaContenedoraZ;
    }

    Tesoro::~Tesoro()
    {
        delete propietario;
    };

