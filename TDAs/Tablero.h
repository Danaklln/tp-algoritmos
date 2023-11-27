#ifndef TABLERO_H_
#define TABLERO_H_

#include <iostream>
#include "Lista.h"
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "Celda.h"

using namespace std;

/*
* Un Tablero almacena punteros a celdas de según las dimensiones dadas.
*/
class Tablero {

    private:

		Lista<Lista<Lista<Celda*>*>*>* ptrContenido;
		Jugador* ptrJugadorActual;
        unsigned int dimensionX; 
		unsigned int dimensionY;
		unsigned int dimensionZ;

    public:

		/*
		* Pre: Dimensiones X Y Z son numeros mayor a cero.
		* Post: Crea un Tablero con las dimensiones dadas.
		*/
        Tablero(unsigned int dimensionX, unsigned int dimensionY, unsigned int dimensionZ, Jugador* ptrPrimerJugador){
			Lista<Lista<Lista<Celda*>*>*>*   ptrlistptrlistptrlistdeptrcelda = new Lista<Lista<Lista<Celda*>*>*>;
			for (unsigned int k = 1; k <= dimensionZ ; k++){
				Lista<Lista<Celda*>*>*   ptrlistptrlistdeptrcelda = new Lista<Lista<Celda*>*>;
				for (unsigned int j = 1; j <= dimensionY; j++){
					Lista<Celda*>*  ptrlistdeptrcelda = new Lista<Celda*>;
					for (unsigned int i = 1; i <= dimensionX; i++){
						Celda* ptrcelda = new Celda(ptrPrimerJugador,i,j,k);
						ptrlistdeptrcelda->agregar(ptrcelda);
					}
					ptrlistptrlistdeptrcelda->agregar(ptrlistdeptrcelda);
				}
				ptrlistptrlistptrlistdeptrcelda->agregar(ptrlistptrlistdeptrcelda);
			}
			this->ptrContenido = ptrlistptrlistptrlistdeptrcelda;
			this->ptrJugadorActual = ptrPrimerJugador;
			this->dimensionX = dimensionX;
			this->dimensionY = dimensionY;
			this->dimensionZ = dimensionZ;
		}

		/*
		* Pre: -
		* Post: Devuelve puntero al contenido del Tablero. 
		*/
		Lista<Lista<Lista<Celda*>*>*>* getContenido(){
			return this->ptrContenido;
		}

		/*
		* Pre: Recibe un numero mayor a 1 en rango.
		* Post: Devuelve puntero a nivel XY segun numero dado.
		*/
		Lista<Lista<Celda*>*>* obtenerPiso(unsigned int posicionZ){
			return this->ptrContenido->obtener(posicionZ);
		}

		/*
		* Pre: Las posiciones X Y Z están entre 1 y dimensión X Y Z del Tablero.
		* Post: Devuelve puntero a celda de la posición pedida. 
		*/
		Celda* obtenerPtrCelda(unsigned int posicionX, unsigned int posicionY, unsigned int posicionZ){
			Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = this->ptrContenido->obtener(posicionZ);
			Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtener(posicionY);
			return ptrlistdeptrcelda->obtener(posicionX);
		}

		/*
		* Pre: Recibe un puntero jugador.
		* Post: Devuelve puntero a primer tesoro propio encontrado si no NULL. 
		*/
		Tesoro* obtenerUnTesoro(Jugador* ptrJugador){
			Lista<Lista<Lista<Celda*>*>*>*  ptrlistptrlistptrlistdeptrcelda = this->ptrContenido;
			ptrlistptrlistptrlistdeptrcelda->iniciarCursor();
			while (ptrlistptrlistptrlistdeptrcelda->avanzarCursor()){
				Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = ptrlistptrlistptrlistdeptrcelda->obtenerCursor();
				ptrlistptrlistdeptrcelda->iniciarCursor();
				while (ptrlistptrlistdeptrcelda->avanzarCursor()){
					Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtenerCursor();
					ptrlistdeptrcelda->iniciarCursor();
					while (ptrlistdeptrcelda->avanzarCursor()){
						Tesoro* ptrTesoro = ptrlistdeptrcelda->obtenerCursor()->obtenerTesoroDeJugador(ptrJugador);
						if(ptrTesoro != NULL){
							return ptrTesoro;
						}
					}
				}
			}
			return NULL;
		}

		/* 
		* Pre: -
		* Post: Muestra todo el contenido del Tablero por pantalla. 
		*/
		void mostrarTableroCompleto(){
			Lista<Lista<Lista<Celda*>*>*>*  ptrlistptrlistptrlistdeptrcelda = this->ptrContenido;
			ptrlistptrlistptrlistdeptrcelda->iniciarCursor();
			unsigned int k = 1;
			while (ptrlistptrlistptrlistdeptrcelda->avanzarCursor()){
                std::cout << "TableroXY | Z = " << k << ":" << std::endl;
				Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = ptrlistptrlistptrlistdeptrcelda->obtenerCursor();
				ptrlistptrlistdeptrcelda->iniciarCursor();
				while (ptrlistptrlistdeptrcelda->avanzarCursor()){
					Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtenerCursor();
					ptrlistdeptrcelda->iniciarCursor();
					while (ptrlistdeptrcelda->avanzarCursor()){
                        std::cout <<  ptrlistdeptrcelda->obtenerCursor()->getCoordenadaX() << ptrlistdeptrcelda->obtenerCursor()->getCoordenadaY() << " ";
					}
                    std::cout << std::endl;
				}
				k++;
			}
		} 

		/*
		* Pre: Recibe un numero mayor a 1.
		* Post: devuelve string ajustado para indicador de coordenada.
		*/
		string ajustarIndicadorCoordenada(unsigned int i){
			if (i < 10){
				return "  |";
			}
			if (i >= 10){
				return " |";
			}
			return "|";
		}


		/*
		* Pre: Recibe un numero mayor a 1 en rango.
		* Post: Muestra nivel XY segun numero dado.
		*/
		void mostrarPiso(unsigned int coordenadaZ){
			Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = this->obtenerPiso(coordenadaZ);
			std::cout << "TableroXY | Z = " << coordenadaZ << ":" << std::endl<< "   |";
			for (unsigned int i = 1; i <= ptrlistptrlistdeptrcelda->obtener(1)->contarElementos(); i++){
					cout << i << this->ajustarIndicadorCoordenada(i);
			}
			std::cout << std::endl;
			ptrlistptrlistdeptrcelda->iniciarCursor();
			unsigned int j = 1;
			while (ptrlistptrlistdeptrcelda->avanzarCursor()){
				Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtenerCursor();
				ptrlistdeptrcelda->iniciarCursor();
				cout << j << this->ajustarIndicadorCoordenada(j);
				while (ptrlistdeptrcelda->avanzarCursor()){
					std::cout <<  ptrlistdeptrcelda->obtenerCursor()->visualizarCelda() << "|";
				}
				std::cout << std::endl;
				j++;
			}
		}

		/*
		* Pre: -
		* Post: Devuelve el jugador actual del Tablero. 
		*/
		Jugador* getJugadorActual(){
			return this->ptrJugadorActual;
		}

		/*
		* Pre: -
		* Post: Devuelve la dimension X del Tablero. 
		*/
		unsigned int getDimensionX(){
			return this->dimensionX;
		}

		/*
		* Pre: -
		* Post: Devuelve la dimension Y del Tablero. 
		*/
		unsigned int getDimensionY(){
			return this->dimensionY;
		}

		/*
		* Pre: -
		* Post: Devuelve la dimension Z del Tablero. 
		*/
		unsigned int getDimensionZ(){
			return this->dimensionZ;
		}

		/*
		* Pre: Recibe puntero al jugador y las coordenadas X Y Z están en rango.
		* Post: Crea nueva mina a nombre del jugador segun coordenadas dadas y devuelve true si la agrega. 
		*/
		bool agregarNuevaMina(unsigned int poder, Jugador* ptrJugador, unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
			Mina* ptrNuevaMina = new Mina(poder, ptrJugador);
			Celda* ptrCelda = this->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ);
			if (ptrCelda->getEstado() == CELDA_ACTIVA){
				ptrCelda->addMina(ptrNuevaMina);
				return true;
			}
			return false;
		}

		/*
		* Pre: Recibe puntero al jugador y las coordenadas X Y Z están en rango.
		* Post: Crea nuevo espia a nombre del jugador segun coordenadas dadas y devuelve true si lo agrega.
		*/
		bool agregarNuevoEspia(Jugador* ptrJugador, unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
			Espia* ptrNuevoEspia = new Espia(ptrJugador);
			Celda* ptrCelda = this->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ);
			if (ptrCelda->getEstado() == CELDA_ACTIVA){
				ptrCelda->addEspia(ptrNuevoEspia);
				return true;
			}
			return false;
		}

		/*
		* Pre: Recibe puntero al jugador y las coordenadas X Y Z están en rango.
		* Post: Crea nuevo Tesoro del jugador segun coordenadas dadas y devuelve true si lo agrega. 
		*/
		bool agregarNuevoTesoro(Jugador* ptrJugador, unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
			Tesoro* ptrNuevoTesoro = new Tesoro(ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
			Celda* ptrCelda = this->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ);
			if (ptrCelda->getEstado() == CELDA_ACTIVA){
				ptrCelda->addTesoro(ptrNuevoTesoro);
				return true;
			}
			return false;
		}

		/*
		* Pre: Recibe puntero a tesoro y las coordenadas X Y Z están en rango.
		* Post: Saca ese tesoro de la celda segun coordenadas y devuelve true si lo saco. 
		*/
		bool sacarUnTesoro(Tesoro* ptrTesoro, unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
			if (this->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->sacarTesoro(ptrTesoro) != NULL){
				return true;
			}
			return false;
		}

		/*
		* Pre: Recibe puntero a tesoro y las coordenadas X Y Z están en rango.
		* Post: Pone ese tesoro de la celda segun coordenadas y devuelve true si lo puso. 
		*/
		bool ponerTesoro(Tesoro* ptrTesoro, unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
			Celda* ptrCelda = this->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ);
			if (ptrCelda->getEstado() == CELDA_ACTIVA){
				ptrCelda->addTesoro(ptrTesoro);
				return true;
			}
			return false;
		}

		/*
		* Pre: -
		* Post: Realiza moviento completo de un tesoro de una celda a otra y avisa si no pudo.
		*/
		void moverTesoro(Jugador *ptrJugador){
			Tesoro* ptrTesoro = this->obtenerUnTesoro(ptrJugador);
			if (ptrTesoro != NULL){
				cout << "Tiene tesoro en: " << ptrTesoro->getCoordenadaX() << "-"<< ptrTesoro->getCoordenadaY() <<"-"<< ptrTesoro->getCoordenadaZ() << "-" << endl;
				unsigned int nuevaCoordenadaX; unsigned int nuevaCoordenadaY; unsigned int nuevaCoordenadaZ;
				cout << "Ingrese nueva coordenadaZ: "; cin >> nuevaCoordenadaZ;
				this->mostrarPiso(nuevaCoordenadaZ);
				cout << "Ingrese nueva coordenadaX: "; cin >> nuevaCoordenadaX;
				cout << "Ingrese nueva coordenadaY: "; cin >> nuevaCoordenadaY;
				Celda* ptrNuevaCelda = this->obtenerPtrCelda(nuevaCoordenadaX, nuevaCoordenadaY, nuevaCoordenadaZ);
				if (ptrNuevaCelda->getEstado() == CELDA_ACTIVA){
					ptrTesoro->actualizarCoordenadas(nuevaCoordenadaX, nuevaCoordenadaY, nuevaCoordenadaZ);
					ptrNuevaCelda->addTesoro(ptrTesoro);
					cout << "El tesoro fue movido" << endl;
				}
				else{
					cout << "tesoro NO se movio"<< endl;
				}
			}
		}

		/*
		* Pre: Recibe puntero a nuevo jugador.
		* Post: Pasa el turno a todo el tablero a ese jugador.
		*/
		void pasarTurnoTablero(Jugador* ptrNuevoJugador){
			Lista<Lista<Lista<Celda*>*>*>*  ptrlistptrlistptrlistdeptrcelda = this->ptrContenido;
			ptrlistptrlistptrlistdeptrcelda->iniciarCursor();
			while (ptrlistptrlistptrlistdeptrcelda->avanzarCursor()){
				Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = ptrlistptrlistptrlistdeptrcelda->obtenerCursor();
				ptrlistptrlistdeptrcelda->iniciarCursor();
				while (ptrlistptrlistdeptrcelda->avanzarCursor()){
					Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtenerCursor();
					ptrlistdeptrcelda->iniciarCursor();
					while (ptrlistdeptrcelda->avanzarCursor()){
						ptrlistdeptrcelda->obtenerCursor()->pasarTurnoCelda(ptrNuevoJugador);
					}
				}
			}
			this->ptrJugadorActual = ptrNuevoJugador;
		}
		
		/*
		* Pre: -
		* Post: Libera el contenido de Tablero. 
		*/
        ~Tablero(){
			Lista<Lista<Lista<Celda*>*>*>*   ptrlistptrlistptrlistdeptrcelda = this->ptrContenido;
			for (unsigned int k = 1; k <= ptrlistptrlistptrlistdeptrcelda->contarElementos(); k++){
				Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = ptrlistptrlistptrlistdeptrcelda->obtener(k);
				for (unsigned int j = 1; j <= ptrlistptrlistdeptrcelda->contarElementos(); j++){
					Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtener(j);
					for (unsigned int i = 1; i <= ptrlistdeptrcelda->contarElementos(); i++){
						Celda* ptrcelda = ptrlistdeptrcelda->obtener(i);
						delete ptrcelda;
					}
					delete ptrlistdeptrcelda;
				}
				delete ptrlistptrlistdeptrcelda;
			}
			delete ptrlistptrlistptrlistdeptrcelda;
		}
};

#endif /* TABLERO_H_ */

