#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "./ManoIndividual.h"

enum EstadoJugador{
    JUGADOR_ELIMINADO,
    JUGADOR_ACTIVO,
	JUGADOR_PERDIOTURNO
};

class Jugador {
    private:
        unsigned int id;
    	EstadoJugador estado;
        ManoIndividual* manoJugador;

    public:
		/*
		* Pre: -
		* Post: Inicializa un jugador con el id proporcionado como parámetro.
		*/
        Jugador(unsigned int id){
			this->id = id;
			this->estado = JUGADOR_ACTIVO;
            this->manoJugador = new ManoIndividual();
		}

		/*
		* Pre: -
		* Post: Devuelve un entero positivo indicando el id del jugador.
		*/
		unsigned int getId(){
			return this->id;
		}

		/*
		* Pre: -
		* Post: Devuelve el estado del jugador.
		*/
		unsigned int getEstado(){
			return this->estado;
		}

		/*
		* Pre: -
		* Post: Indica que jugador está eliminado del juego.
		*/
		void eliminarJugador(){
			this->estado = JUGADOR_ELIMINADO;
		}

		/*
		* Pre: -
		* Post: Indica que jugador debe perder este turno.
		*/
		void perderTurno(){
			this->estado = JUGADOR_PERDIOTURNO;
		}

		/*
		* Pre: -
		* Post: Reactiva jugador en caso de no estar eliminado.
		*/
		void reactivarJugador(){
			if (this->estado != JUGADOR_ELIMINADO){
				this->estado = JUGADOR_ACTIVO;
			}
		}

        virtual ~Jugador()
        {
            delete this->manoJugador;
        }
};

#endif /* JUGADOR_H_ */

