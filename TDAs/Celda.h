#ifndef CELDA_H_
#define CELDA_H_
#include <iostream>
#include <string>
#include "Lista.h"
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"

using namespace std;

enum EstadoCelda{
	CELDA_INACTIVA,
	CELDA_ACTIVA
};



/*
* Una Celda almacena objetos e información necesaria para el juego tesoro binario.
*/
class Celda {

    private:
        EstadoCelda estado;
		Espia* ptrEspia;
		Mina* ptrMina;
		Lista<Tesoro*>* ptrlistptrtesoro;
		Jugador* ptrJugadorActual;
		unsigned int turnosInactivosRestantes;
		unsigned int coordenadaX; //no serian necesarias las dejamos por si acaso
		unsigned int coordenadaY;
		unsigned int coordenadaZ;

    public:
		/*
		* Pre: Coordenadas X Y Z son numeros mayor a cero.
		* Post: Inicializa una celda con valores default y el jugador actual.
		*/
        Celda(Jugador* ptrJugadorActual, unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
			this->ptrJugadorActual = ptrJugadorActual;
			this->coordenadaX = coordenadaX;
			this->coordenadaY = coordenadaY;
			this->coordenadaZ = coordenadaZ;
			this->estado = CELDA_ACTIVA;
			this->turnosInactivosRestantes = 0;
			this->ptrlistptrtesoro = new Lista<Tesoro*>;
			this->ptrEspia = NULL;
			this->ptrMina = NULL;
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
		* Post: Devuelve puntero al unico espía de la celda.
		*/
		Espia* obtenerEspia(){
			return this->ptrEspia; 
		}

		/*
		* Pre: -
		* Post: Devuelve puntero a la unica mina de la celda.
		*/
		Mina* obtenerMina(){
			return 	this->ptrMina; 
		}

		/*
		* Pre: -
		* Post: Devuelve puntero a lista de punteros a tesoro.
		*/
		Lista<Tesoro*>* obtenerTesoros(){
			return this->ptrlistptrtesoro; 
		}

		/*
		* Pre: -
		* Post: Devuelve puntero al 1er tesoro de jugador actual si no devuelve NULL.
		*/
		Tesoro* obtenerTesoroActual(){
			Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
			if (!ptrlistptrtesoro->estaVacia()){
				ptrlistptrtesoro->iniciarCursor();
				while (ptrlistptrtesoro->avanzarCursor()){
					if (ptrlistptrtesoro->obtenerCursor()->getPropietario() == this->ptrJugadorActual){
						return ptrlistptrtesoro->obtenerCursor();
					}
				}
				return NULL;
			}
			return NULL;
		}

		/*
		* Pre: Recibe puntero a jugador.
		* Post: Devuelve puntero al 1er tesoro de jugador recibido si no devuelve NULL.
		*/
		Tesoro* obtenerTesoroDeJugador(Jugador* ptrJugador){
			Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
			if (!ptrlistptrtesoro->estaVacia()){
				ptrlistptrtesoro->iniciarCursor();
				while (ptrlistptrtesoro->avanzarCursor()){
					if (ptrlistptrtesoro->obtenerCursor()->getPropietario() == ptrJugador){
						return ptrlistptrtesoro->obtenerCursor();
					}
				}
				return NULL;
			}
			return NULL;
		}

		/*
		* Pre: Recibe puntero a jugador.
		* Post: Devuelve puntero al 1er tesoro de jugador distinto al recibido si no devuelve NULL.
		*/
		Tesoro* obtenerTesoroContrario(Jugador* ptrJugador){
			Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
			if (!ptrlistptrtesoro->estaVacia()){
				ptrlistptrtesoro->iniciarCursor();
				while (ptrlistptrtesoro->avanzarCursor()){
					if (ptrlistptrtesoro->obtenerCursor()->getPropietario() != ptrJugador){
						//cout<<"FUE LLAMADO"<< ptrlistptrtesoro->obtenerCursor()->getPropietario() << " " <<ptrJugador<<endl;
						return ptrlistptrtesoro->obtenerCursor();
					}
				}
				return NULL;
			}
			return NULL;
		}

		/*
		* Pre: -
		* Post: Devuelve puntero a jugador actual.
		*/
		Jugador* obtenerJugadorActual(){
			return this->ptrJugadorActual;
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
		* Pre: Cantidad de turnos inactivos es mayor a cero.
		* Post: Inactiva celda según la cantidad dada.
		*/
		void inactivarCelda(unsigned int cantidadTurnosInactivos){
			this->turnosInactivosRestantes = cantidadTurnosInactivos;
			this->estado = CELDA_INACTIVA;
		}

		/*
		* Pre: -
		* Post: Reactiva celda si la cantidad de turnos inactivos es 0.
		*/
		void reactivarCelda(){
			if ((this->estado == CELDA_INACTIVA) && (this->turnosInactivosRestantes == 0)){
				this->turnosInactivosRestantes = 0;
				this->estado = CELDA_ACTIVA;
			}
		}

		/*
		* Pre: recibe puntero a espia.
		* Post: Lo agrega si no hay o ya tiene eliminando anterior y si hay contrario elimina ambos 
		*/
		void addEspia(Espia* ptrEspia){
			if (this->ptrEspia == NULL){
				this->ptrEspia = ptrEspia;
			}
			else if(this->tieneEspia(ptrEspia->getPropietario())){
				this->eliminarEspia();
				this->ptrEspia = ptrEspia;
			}
			else{
				this->eliminarEspia();
				delete ptrEspia;
			}
		}

		/*
		* Pre: recibe puntero a mina.
		* Post: agrega esa misma.
		*/
		void addMina(Mina* ptrMina){
			if (this->ptrMina == NULL){
				this->ptrMina = ptrMina;
			}
			else{
				this->eliminarMina();
				delete ptrMina;
			}
		}

		/*
		* Pre: recibe puntero a tesoro.
		* Post: agrega ese mismo de la lista.
		*/
		void addTesoro(Tesoro* tesoro){
			if (!this->ptrlistptrtesoro->estaVacia() && !tieneTesoro(tesoro->getPropietario())){
				cout<< "tesoro enemigo en celda:" << this->coordenadaX <<"-"<< this->coordenadaY <<"-"<<this->coordenadaZ <<endl;  
			}
			this->ptrlistptrtesoro->agregar(tesoro);
		}

		/*
		* Pre: -
		* Post: Libera puntero a espia.
		*/
		void eliminarEspia(){
			delete this->ptrEspia;
			this->ptrEspia = NULL;
		}

		/*
		* Pre: -
		* Post: Libera puntero a mina.
		*/
		void eliminarMina(){
			delete this->ptrMina;
			this->ptrMina = NULL;
		}

		/*
		* Pre: -
		* Post: Libera punteros a tesoros y vacía la lista.
		*/
		void eliminarTodosTesoros(){
			Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
			ptrlistptrtesoro->iniciarCursor();
			while(ptrlistptrtesoro->avanzarCursor()){
				delete ptrlistptrtesoro->obtenerCursor();
			}
			delete ptrlistptrtesoro;
			this->ptrlistptrtesoro = new Lista<Tesoro*>;
		}

		/*
		* Pre: recibe puntero a tesoro.
		* Post: saca y elimina ese mismo de la lista.
		*/
		void eliminarTesoro(Tesoro* tesoro){
			this->sacarTesoro(tesoro);
			delete tesoro;
		}
		
		/*
		* Pre: recibe puntero a tesoro.
		* Post: saca ese mismo de la lista.
		*/
		void sacarTesoro(Tesoro* tesoro){
			Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
			unsigned int i = 1;
			ptrlistptrtesoro->iniciarCursor();
			while (ptrlistptrtesoro->avanzarCursor()){
				if (ptrlistptrtesoro->obtenerCursor() == tesoro){
					ptrlistptrtesoro->remover(i);
					break;
				}
			}
		}

		/*
		* Pre: -
		* Post: Devuelve un booleano indicando si hay un
        * espía en la casilla
		*/
		bool tieneEspia(){
            return !(!this->ptrEspia);
		}

        /*
         * Pre: Debe haber un espía en la casilla
         * Post: Devuelve un puntero al propietario del espia
         * en cuestión
         */
		bool obtenerPropietarioEspia(){
            if (!this->tieneEspia()) throw "[ERROR] No hay un espía en la casilla";

			return this->ptrEspia->getPropietario();
		}


		/*
		* Pre: -
		* Post: Devuelve un booleano indicando si hay una
        * mina en la casilla
		*/
		bool tieneMina(){
            return !(!this->ptrMina);
		}

        /*
         * Pre: Debe haber una mina colocada en la casilla
         * Post: Devuelve un puntero a el jugador propietario de la
         * mina.
         */
        Jugador* obtenerPropietarioMina()
        {
            if (!this->ptrMina)
            {
                throw "[ERROR] No hay una mina en la casilla";
            }

            return this->ptrMina->getPropietario(); 
        }

		/*
		* Pre: Recibe un puntero a un jugador.
		* Post: Devuelve true si tiene algún tesoro en esta celda.
		*/
		bool tieneTesoro(Jugador* ptrJugador){
			Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
			if (!ptrlistptrtesoro->estaVacia()){
				ptrlistptrtesoro->iniciarCursor();
				while (ptrlistptrtesoro->avanzarCursor()){
					if (ptrlistptrtesoro->obtenerCursor()->getPropietario() == ptrJugador){
						return true;
					}
				}
			}
			return false;
		}

        /*
         * Pre: Se debe proporcionar un puntero a jugador valido
         * Post: Devuelve un booleano indicando si hay tesoros en la casilla
         * que no pertenezcan al jugador en cuestion
         */
        bool tieneTesoroRival(Jugador* jugador)
        {
            Lista<Tesoro*>* tesorosEnLaCasilla = this->ptrlistptrtesoro;
            tesorosEnLaCasilla->iniciarCursor();
            while (tesorosEnLaCasilla->avanzarCursor())
            {
                Tesoro* tesoroActual = tesorosEnLaCasilla->obtenerCursor();
                if (tesoroActual->getPropietario() != jugador)
                {
                    return true;
                }
            }

            return false;
        }

		/*
		* Pre: -
		* Post: Devuelve contenidos visibles por jugador actual de la celda.
		*/
		string visualizarCelda(){
			string texto = "   ";
			if (this->estado == CELDA_INACTIVA){
				texto = "XXX";
			}
			else{
				Jugador* ptrJugadorActual = this->ptrJugadorActual;
				if (this->tieneTesoro(ptrJugadorActual)){
					texto[0] = 'T';
					if (this->obtenerTesoroActual()->getEstadoTesoro() == TESOROBLINDADO){
						texto[0] = 'B';
						}
				}
				if (this->tieneEspia(ptrJugadorActual)){
					texto[1] = 'E';
				}
				if (this->tieneMina(ptrJugadorActual)){
					texto[2] = 'M';
				}
			}
			return texto; 
		}

		/*
		* Pre: -
		* Post: Acciona el comportamiento de espia.
		*/
		void accionarEspia(){
			if (this->ptrEspia != NULL){
				Jugador* ptrPropietarioEspia = this->ptrEspia->getPropietario();
				Tesoro* ptrTesoroContrario = this->obtenerTesoroContrario(ptrPropietarioEspia);
				if (ptrTesoroContrario != NULL){
					this->inactivarCelda(4);
					eliminarTesoro(ptrTesoroContrario);
				}
			}
		}

		/*
		* Pre: -
		* Post: Acciona el comportamiento de mina.
		*/
		void accionarMina(){
			if (this->ptrMina != NULL){
				this->inactivarCelda(this->ptrMina->getPoder());
				this->eliminarMina();
				this->eliminarEspia();
				this->eliminarTodosTesoros();
			}
		}

		/*
		* Pre: Recibe un puntero a un jugador.
		* Post: Pasa el turno a la celda y al nuevo jugador.
		*/
		void pasarTurnoCelda(Jugador* ptrNuevoJugadorActual){
			if ((this->estado == CELDA_INACTIVA) && (this->turnosInactivosRestantes > 0)){
				this->turnosInactivosRestantes--;
			}
			this->accionarMina();
			this->accionarEspia();
			this->reactivarCelda();
			this->ptrJugadorActual = ptrNuevoJugadorActual;
		}

		/*
		* Pre: -
		* Post: Libera datos dinamicos de la celda
		*/
		~Celda(){
			delete ptrEspia;
			delete ptrMina;
			Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
			ptrlistptrtesoro->iniciarCursor();
			while(ptrlistptrtesoro->avanzarCursor()){
				delete ptrlistptrtesoro->obtenerCursor();
			}
			delete ptrlistptrtesoro;
		}
};


#endif /* CELDA_H_ */
