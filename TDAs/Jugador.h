#include "Lista.h"
#include "Tesoro.h"

enum EstadoJugador 
{
    ELIMINADO,
    ACTIVO
};

class Jugador 
{
private:
    unsigned int id;
    unsigned short tesorosVigentes;
    unsigned short CantidadCartasSacadas;
    EstadoJugador estado;
    Lista<Tesoro*>* tesorosPropios;
    Lista<Carta*>* cartasEnMano;

public:
    /*
     * Pre: -
     * Post: Inicializa un jugador con el id proporcionado como
     * parámetro
    */
    Jugador(unsigned int id)
    {
        this->id = id;
    }

    /*
     * Pre: -
     * Post: Devuelve un entero positivo indicando el id del
     * jugador
    */
    unsigned int getId()
    {
        return this->id;
    }

    /*
     * Pre: Debe proporcionarse un tesoro como parámetro
     * Post: Agrega un tesoro al final de la lista tesorosPropios
    */
    void addTesoroPropio(Tesoro* tesoro)
    {
        if (!tesoro) throw "[ERROR] No se proporcionó un tesoro válido";
        this->tesorosPropios->iniciarCursor();
        this->tesorosPropios->agregar(tesoro);
    }

    /*
     * Pre: -
     * Post: Devuelve la lista con los tesoros del jugador actual
    */
    Lista<Tesoro*>* getTesorosPropios()
    {
        return this->tesorosPropios;
    }

    /*
     * Pre: -
     * Post: Devuelve la cantidad de cartas que sacó del mazo
     * el jugador
    */
    unsigned short getCantidadCartasSacadas()
    {
        return this->cantidadCartasSacadas;
    }

    /*
     * Pre: -
     * Post: Cambia el valor de cantidadCartasSacadas por el
     * proporcionado como parámetro
    */
    void setCantidadCartasSacadas(unsigned short nuevaCantidad)
    {
        this->cantidadCartasSacadas = nuevaCantidad;
    }

    /*
     * Pre: -
     * Post: Devuelve un puntero a la lista de cartas en la
     * mano del jugador
    */
    Lista<Carta*>* getCartasEnMano()
    {
        return this->cartasEnMano;
    }

    /*
     * Pre: -
     * Post: Destruye la instancia de Jugador, liberando la memoria
     * utilizada
    */
    ~Jugador()
    {
        this->tesorosPropios->iniciarCursor();
        while(this->tesorosPropios->avanzarCursor())
        {
            delete this->tesorosPropios->obtenerCursor();
        }
        delete this->tesorosPropios;

        this->cartasEnMano->iniciarCursor();
        while (this->cartasEnMano->avanzarCursor())
        {
            delete this->cartasEnMano->obtenerCursor();
        }
        delete this->cartasEnMano;
    }
};
