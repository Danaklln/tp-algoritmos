/*
 * Juego.h
 *
 *  Created on: 19/10/2023
 *      Author: algo2
 */

#ifndef TESOROBINARIO2_H_
#define TESOROBINARIO2_H_

#include "Jugador.h"
#include "Lista.h"
#include "Celda.h"
#include "Tesoro.h"
#include "Tablero.h"
#include "Interfaz.h"

class TesoroBinario{

	private:

	 	const unsigned int CANTIDAD_TESOROS_INICIAL = 4;
	 	const unsigned int TURNOS_INACTIVO_INICIAL = 5;

	 	unsigned int cantidadJugadores;
	 	Jugador ** jugadores;
		Tablero * tablero;
		Interfaz * interfaz;

	public:

		/*
		* Pre: CantidadJugadores y dimensiones x, y, z son enteros mayores a cero.
		*      interfaz es un puntero no nulo
		* Post: Instancia la clase con el número de jugadores recibidos y el tablero
		*       con las dimensiones dadas
		*/
		TesoroBinario(unsigned int cantidadJugadores,
			      unsigned int x,
			      unsigned int y,
				  unsigned int z,
			      Interfaz *   interfaz);

		/*
		* Pre: recibe un jugador válido
		* Post: coloca los tesoros en las posiciones pedidas al usuario
		*/
		void colocarTesoros(Jugador * const);

		/*
		* Pre: -
		* Post: devuelve una carta válida
		*/
		tCarta sacarCarta( );

		/*
		* Pre: recibe un jugador válido
		* Post: el usuario elige un tesoro y una celda destino y se mueve
		* el tesoro a la misma
		*/
		void moverTesoro(Jugador * jugador);

		/*
		* Pre: recibe un jugador válido
		* Post: coloca un espía en la posición elegida por el usuario
		*/
		void colocarEspia(Jugador * jugador);

		/*
		* Pre: recibe un jugador válido
		* Post: coloca una mina en la posición elegida por el usuario
		*/
		void colocarMina(Jugador * jugador);

		/*
		* Pre: -
		* Post: inicia el loop principal del juego
		*/
		bool iniciarJuego();

		/*
		* Pre: recibe una lista de jugadores válidos
		* Post: determina si hay un ganador o un empate según la cantidad
		* de jugadores activos
		*/
		bool getResultadoPartida(Jugador **);

		/*
		* Pre: -
		* Post: decrementa en uno los turnos restantes de las casillas inactivas
		* y las activa si quedaron en cero
		*/
		void actualizarCasillasInactivas();

		/*
		* Pre: recibe un jugador válido y un valor de carta válido
		* Post: ejecuta las acciones según la carta elegida
		*/
		void jugarCarta(Jugador * jugador,
				        tCarta carta);

		/*
		* Pre: recibe un jugador válido
		* Post: activa el blindaje en un tesoro elegido por el usuario
		*/
		void cartaBlindaje(Jugador * jugador);

		/*
		* Pre: recibe un jugador válido
		* Post: activa el radar para el usuario en una casilla elegida por
		* el mismo, por el turno actual
		*/
		void cartaRadar(Jugador * jugador);

		/*
		* Pre: recibe un jugador válido
		* Post: genera un nuevo tesoro a partir de un tesoro elegido por el usuario
		*/
		void cartaPartirTesoro(Jugador * jugador);

		/*
		* Pre: recibe un jugador válido
		* Post: desactiva el blindaje de todos los tesoros rivales en una casilla
		* elegida por el usuario
		*/
		void cartaRomperBlindaje(Jugador * jugador);

		/*
		* Pre: recibe un jugador válido
		* Post: marca los tesoros del usuario que se encuentran en peligro por
		* en el turno actual
		*/
		void cartaTesoroEnPeligro(Jugador * jugador);

		/*
		* Pre: recibe un jugador válido
		* Post: permite al jugador colocar 3 minas en el turno actual
		*/
		void cartaTripleMina(Jugador * jugador);

		virtual ~TesoroBinario();

};

#endif /* TESOROBINARIO2_H_ */
