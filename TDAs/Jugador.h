#ifndef JUGADOR_H_
#define JUGADOR_H_

enum EstadoJugador {
    JUGADORELIMINADO,
    JUGADORACTIVO,
	JUGADORPERDIOTURNO
};

class Jugador{

    private:
        unsigned int id;
    	EstadoJugador estado;

    public:
		/*
		* Pre: -
		* Post: Inicializa un jugador con el id proporcionado como parámetro.
		*/
        Jugador(unsigned int id){
			this->id = id;
			this->estado = JUGADORACTIVO;
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
			this->estado = JUGADORELIMINADO;
		}

		/*
		* Pre: -
		* Post: Indica que jugador debe perder este turno.
		*/
		void perderTurno(){
			this->estado = JUGADORPERDIOTURNO;
		}

		/*
		* Pre: -
		* Post: Reactiva jugador en caso de no estar eliminado.
		*/
		void reactivarJugador(){
			if (this->estado != JUGADORELIMINADO){
				this->estado = JUGADORACTIVO;
			}
		}

};


#endif /* JUGADOR_H_ */
