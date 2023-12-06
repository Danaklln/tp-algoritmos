#ifndef TESORO_H_
#define TESORO_H_

#include "Jugador.h"

enum EstadoTesoro{
	TESORO_NO_BLINDADO,
    TESORO_BLINDADO
};

enum VisibilidadTesoro {
    TESORO_OCULTO, // Estado normal de un tesoro
    TESORO_REVELADO
};

class Tesoro{

    private:

        Jugador* ptrPropietario;
        EstadoTesoro estado;
        VisibilidadTesoro visibilidad;
        unsigned int turnosBlindajeRestante;
        unsigned int coordenadaX;
        unsigned int coordenadaY;
        unsigned int coordenadaZ;

    public:
    
        /*
        * Pre: recibe puntero a un jugador y 3 numeros mayores a cero
        * Post: Inicializa Tesoro indicando el jugador ptrPropietario del mismo y las coordenadas del Tesoro
        */
        Tesoro(Jugador* ptrJugador, unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
            this->ptrPropietario = ptrJugador;
            this->estado = TESORO_NO_BLINDADO;
            this->visibilidad = TESORO_OCULTO;
            this->turnosBlindajeRestante = 0;
            this->coordenadaX = coordenadaX;
            this->coordenadaY = coordenadaY;
            this->coordenadaZ = coordenadaZ;
        };

        /*
        * Pre: -
        * Post: Devuelve puntero al jugador propietario del tesoro
        */
        Jugador* getPropietario(){
            return this-> ptrPropietario;
        }

        /*
        * Pre: -
        * Post: Devuelve estado del tesoro.
        */
        EstadoTesoro getEstadoTesoro(){
            return this->estado;
        }

        /*
        * Pre: -
        * Post: Devuelve la cantidad de turnos de blindaje restantes del tesoro.
        */
        unsigned int getTurnosBlindajeRestante(){
            return this -> turnosBlindajeRestante;
        }

        /*
        * Pre: -
        * Post: Devuelve la coordenada X.
        */
        unsigned int getCoordenadaX(){
            return this->coordenadaX;
        }

        /*
        * Pre: -
        * Post: Devuelve la coordenada Y.
        */
        unsigned int getCoordenadaY(){
            return this->coordenadaY;
        }

        /*
        * Pre: -
        * Post: Devuelve la coordenada Z.
        */
        unsigned int getCoordenadaZ(){
            return this->coordenadaZ;
        }

        /*
         * Pre: -
         * Post: Devuelve la visibilidad del tesoro
         */
        VisibilidadTesoro getVisibilidad()
        {
            return this->visibilidad;
        }

        /*
         * Pre: -
         * Post: Devuelve la visibilidad del tesoro
         */
        void setVisibilidad(VisibilidadTesoro nuevaVisibilidad)
        {
            this->visibilidad = nuevaVisibilidad;
        }

        /*
        * Pre: cantidad de turnos de blindaje debe ser positivo mayor a 0
        * Post: Blinda celda segun los turnos de blindaje asignados.
        */
        void blindarTesoro(unsigned int cantidadTurnosBlindaje){
            this->turnosBlindajeRestante = cantidadTurnosBlindaje;
            this->estado = TESORO_BLINDADO;
        }

        /*
        * Pre: -
        * Post: Desblinda la celda si pasaron sus turnos de blindaje
        */
        void sacarBlindaje(){
            if ( this->turnosBlindajeRestante<=0){
                this->estado = TESORO_NO_BLINDADO;
                this->turnosBlindajeRestante = 0;
            }
        }

        /*
        * Pre: -
        * Post: Asigna una cantidad de turnos de blindaje a la celda.
        */
        void setTurnosBlindajeRestantes(unsigned int cantidadTurnosBlindaje){
            this->turnosBlindajeRestante = cantidadTurnosBlindaje;
        }

        /*
        * Pre: -
        * Post: Desblinda o resta un turno de blindaje si corresponde.
        */
        void pasarTurnoBlindado(){
            this->sacarBlindaje();
            if (this->turnosBlindajeRestante > 0){
                this->turnosBlindajeRestante--;
            } 
        }

        /*
        * Pre: recibe 3 numeros mayores a cero.
        * Post: Modifica las coordenadas guardadas.
        */
        void actualizarCoordenadas(unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
            this->coordenadaX = coordenadaX;
            this->coordenadaY = coordenadaY;
            this->coordenadaZ = coordenadaZ;
        }
};

#endif /* TESORO_H_ */

