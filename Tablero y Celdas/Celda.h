#ifndef CELDA_H_
#define CELDA_H_

#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "../TDAs/Jugador.h"

enum EstadoCelda{
	INACTIVO,
	ACTIVO,
	BLINDADA
};

/*
* Una Celda almacena objetos e información necesaria para el juego tesoro binario.
*/
class Celda {

    private:

        EstadoCelda estado;
		Espia* espia;
		Mina* mina;
		Lista<Tesoro*>* tesoros;
		unsigned int turnosInactivosRestantes;
		unsigned int turnosBlindajeRestante;
		unsigned int coordenadaX; //no serian necesarias las dejamos por si acaso
		unsigned int coordenadaY;
		unsigned int coordenadaZ;

    public:

		/*
		* Pre: Coordenadas X Y Z son numeros mayor a cero.
		* Post: Inicializa una celda con valores default.
		*/
        Celda(unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
			this->coordenadaX = coordenadaX;
			this->coordenadaY = coordenadaY;
			this->coordenadaZ = coordenadaZ;
			this->estado = ACTIVO;
			this->turnosInactivosRestantes = 0;
			this->turnosBlindajeRestante = 0;
			this->tesoros = new Lista<Tesoro*>;
			this->espia = NULL;
			this->mina = NULL;
		}

		/*
		* Pre: -
		* Post: Devuelve la coordenada X de la celda.
		*/
		unsigned int getCoordenadaX(){
			return this->coordenadaX;
		}


		/*
		* Pre: -
		* Post: Devuelve la coordenada Y de la celda.
		*/
		unsigned int getCoordenadaY(){
			return this->coordenadaY;
		}


		/*
		* Pre: -
		* Post: Devuelve la coordenada Z de la celda.
		*/
		unsigned int getCoordenadaZ(){
			return this->coordenadaZ;
		}

		/*
		* Pre: -
		* Post: Devuelve el estado de la celda
		*/
		EstadoCelda getEstado(){
			return this->estado;
		}

		/*
		* Pre: -
		* Post: Devuelve turnosInactivosRestantes de la celda.
		*/
		unsigned int getTurnosInactivosRestantes(){
			return this->turnosInactivosRestantes;
		}

		/*
		* Pre: -
		* Post: Devuelve turnosBlindajeRestante de la celda.
		*/
		unsigned int getTurnosBlindajeRestante(){
			return this->turnosBlindajeRestante;
		}

		/*
		* Pre: -
		* Post: Devuelve puntero al unico espía de la celda.
		*/
		Espia* obtenerEspia(){
			return this->espia; 
		}

		/*
		* Pre: -
		* Post: Devuelve puntero a la unica mina de la celda.
		*/
		Mina* obtenerMina(){
			return this->mina; 
		}

		/*
		* Pre: -
		* Post: Devuelve puntero a la unica mina de la celda.
		*/
		Lista<Tesoro*>* obtenerTesoros(){
			return this->tesoros; 
		}

		/*
		* Pre: -
		* Post: Modifica el estado de la celda
		*/
		void setEstado(EstadoCelda nuevoEstado ){
			this-> estado = nuevoEstado;
		}


		/*
		* Pre: -
		* Post: Asignar una cantidad de turnos inactivos a la celda
		*/
		void setTurnosInactivosRestantes(unsigned int cantidadTurnosInactivos){
			this->turnosInactivosRestantes = cantidadTurnosInactivos;
		}


		/*
		* Pre: -
		* Post: Asignar una cantidad de turnos de blindaje a la celda
		*/
		void setTurnosBlindajeRestantes(unsigned short cantidadTurnosBlindaje){
			this -> turnosBlindajeRestante = cantidadTurnosBlindaje;
		}
		
		/*
		* Pre: -
		* Post: Libera datos dinamicos de la celda
		*/
		~Celda(){
			delete espia;
			delete mina;
			Lista<Tesoro*>* ptrlistptrtesoro = this->tesoros;
			ptrlistptrtesoro->iniciarCursor();
			while(ptrlistptrtesoro->avanzarCursor()){
				delete ptrlistptrtesoro->obtenerCursor();
			}
			delete tesoros;
		}
};


#endif /* CELDA_H_ */
