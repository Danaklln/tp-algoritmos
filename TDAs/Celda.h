#ifndef CELDA_H_
#define CELDA_H_

#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "Jugador.h"

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
			return 	this->mina; 
		}

		/*
		* Pre: -
		* Post: Devuelve puntero a los tesoros.
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
		* Pre: recibe puntero a tesoro.
		* Post: agrega ese mismo de la lista.
		*/
		void addTesoro(Tesoro* tesoro){
			this->tesoros->agregar(tesoro);
		}

		/*
		* Pre: recibe puntero a espia.
		* Post: agrega ese mismo.
		*/
		void addEspia(Espia* espia){
			this->espia = espia;
		}

		/*
		* Pre: recibe puntero a mina.
		* Post: agrega esa misma.
		*/
		void addMina(Mina* mina){
			this->mina = mina;
		}

		/*
		* Pre: -
		* Post: Libera puntero a espia.
		*/
		void eliminarEspia(){
			delete this->espia;
			this->espia = NULL;
		}

		/*
		* Pre: -
		* Post: Libera puntero a mina.
		*/
		void eliminarMina(){
			delete this->mina;
			this->mina = NULL;
		}
		
		/*
		* Pre: recibe puntero a tesoro.
		* Post: saca ese mismo de la lista.
		*/
		void eliminarTesoro(Tesoro* tesoro){
			Lista<Tesoro*>* ptrtesoros = this->tesoros;
			unsigned int i = 1;
			ptrtesoros->iniciarCursor();
			while (ptrtesoros->avanzarCursor()){
				if (ptrtesoros->obtenerCursor() == tesoro){
					ptrtesoros->remover(i);
					break;
				}
			}
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

