#ifndef JUEGO_H_
#define JUEGO_H_

#include <iostream>
#include "Lista.h"
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "Celda.h"
#include "Tablero.h"
#include "ExportadorTablero.h"

using namespace std;

class Juego{

	private:
		Lista<Jugador*>* ptrListPtrJugador;
		Tablero* ptrtablero;
		ExportadorTablero * imagen;

	public:
		/*
		* Pre: Recibe dimenciones de tablero y numero de jugadores, siendo todo mayor a 0.
		* Post: Inicializa un juego con los datos dados.
		*/
		Juego(unsigned int numeroDeJugadores, unsigned int dimensionX, unsigned int dimensionY, unsigned int dimensionZ){
			this->ptrListPtrJugador = new Lista<Jugador*>;
			for (unsigned int i = 1; i <= numeroDeJugadores; i++){
				Jugador* ptrJugador = new Jugador(i);
				this->ptrListPtrJugador->agregar(ptrJugador);
			}
			this->ptrtablero = new Tablero(dimensionX, dimensionY, dimensionZ, this->ptrListPtrJugador->obtener(1));


			this->imagen = new ExportadorTablero(this->ptrtablero);
		}

		/*
		* Pre: -
		* Post: Devuelve true si alguien gano el juego.
		*/
		bool juegoGanado(){
			Lista<Jugador*>* ptrListPtrJugador = this->ptrListPtrJugador;
			unsigned int contadorJugadoresActivos = 0;
			ptrListPtrJugador->iniciarCursor();
			while (ptrListPtrJugador->avanzarCursor()){
				Jugador* ptrJugador = ptrListPtrJugador->obtenerCursor();
				if (ptrJugador->getEstado() != JUGADOR_ELIMINADO){
					contadorJugadoresActivos++;
				}
			}
			if (contadorJugadoresActivos <= 1){
				return true;
			}
			return false;
		}

		/*
		* Pre: -
		* Post: Devuelve el jugador que gano el juego.
		*/
		Jugador* obtenerGanador(){
			Lista<Jugador*>* ptrListPtrJugador = this->ptrListPtrJugador;
			ptrListPtrJugador->iniciarCursor();
			while (ptrListPtrJugador->avanzarCursor()){
				Jugador* ptrJugador = ptrListPtrJugador->obtenerCursor();
				if (ptrJugador->getEstado() != JUGADOR_ELIMINADO){
					return ptrJugador;
				}
			}
			return NULL;
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: Elimina del juego a jugador si no tiene ningun tesoro.
		*/
		void eliminarJugador(Jugador* ptrJugador){
			if (this->ptrtablero->obtenerUnTesoro(ptrJugador) == NULL){
					ptrJugador->eliminarJugador();
			}
		}

		/*
		* Pre: -
		* Post: Elimina del juego a cualquier jugador que no tenga ningun tesoro.
		*/
		void eliminarJugadores(){
			Lista<Jugador*>* ptrListPtrJugador = this->ptrListPtrJugador;
			ptrListPtrJugador->iniciarCursor();
			while (ptrListPtrJugador->avanzarCursor()){
				this->eliminarJugador(ptrListPtrJugador->obtenerCursor());
			}
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: Agrega mina en tablero segun lo ingresado.
		*/
		void ingresarNuevaMina(Jugador* ptrJugador){
			unsigned int idJugador = ptrJugador->getId();
			if (ptrJugador->getEstado() == JUGADOR_ACTIVO){
				unsigned int coordenadaX, coordenadaY, coordenadaZ;
				cout << "Jugador " << idJugador << ": Ingrese coordenada Z de nueva mina: ";
				cin >> coordenadaZ;
				//this->ptrtablero->mostrarPiso(coordenadaZ);
				cout << "Jugador " << idJugador << ": ingrese coordenada X de nueva mina: ";
				cin >> coordenadaX;
				cout << "Jugador " << idJugador << ": ingrese coordenada Y de nueva mina: ";
				cin >> coordenadaY;
				this->ptrtablero->agregarNuevaMina(3, ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
				this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
			}
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: Agrega espia en tablero segun lo ingresado.
		*/
		void ingresarNuevoEspia(Jugador* ptrJugador){
			unsigned int idJugador = ptrJugador->getId();
			if (ptrJugador->getEstado() == JUGADOR_ACTIVO){
					unsigned int coordenadaX, coordenadaY, coordenadaZ;
					cout << "turno de Jugador " << idJugador << ": Ingrese coordenada Z de nuevo espia: ";
					cin >> coordenadaZ;
					//this->ptrtablero->mostrarPiso(coordenadaZ);
					cout << "Jugador " << idJugador << ": ingrese coordenada X de nuevo espia: ";
					cin >> coordenadaX;
					cout << "Jugador " << idJugador << ": ingrese coordenada Y de nuevo espia: ";
					cin >> coordenadaY;
					this->ptrtablero->agregarNuevoEspia( ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
			}
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: Mueve un tesoro.
		*/
		void realizarMovientoTesoro(Jugador* ptrJugador){
			if (ptrJugador->getEstado() == JUGADOR_ACTIVO){
					this->ptrtablero->moverTesoro(ptrJugador);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
				}
		}

		/*
		* Pre: Recibe un puntero a jugador valido.
		* Post: juega la carta sacada.
		*/
		void jugarCartaN(Jugador* ptrJugador,unsigned int TipoDeCarta){
			unsigned int coordenadaX, coordenadaY, coordenadaZ;
			switch (TipoDeCarta){
				case 0:
					cout << "ingrese coordenada Z para blindar"; 
					cin >> coordenadaZ;
					cout << "ingrese coordenada X para blindar"; 
					cin >> coordenadaX;
					cout << "ingrese coordenada Y para blindar"; 
					cin >> coordenadaY;
					this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->blindarTesoros(ptrJugador, 3);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					break;

				case 1:
					unsigned int dimensionX, dimensionY;
					dimensionX = this->ptrtablero->getDimensionX();
					dimensionY = this->ptrtablero->getDimensionY();
					cout << "ingrese coordenada Z para Radar"; 
					cin >> coordenadaZ;
					this->ptrtablero->mostrarPiso(coordenadaZ);
					cout << "ingrese coordenada X para radar"; 
					cin >> coordenadaX;
					cout << "ingrese coordenada Y para radar"; 
					cin >> coordenadaY;
					if(coordenadaX+1 <= dimensionX && coordenadaY+1 <= dimensionY && coordenadaX-1 >= 1 && coordenadaY-1 >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					} else if(coordenadaX <= dimensionX && coordenadaY+1 <= dimensionY && coordenadaX-1 >= 1 && coordenadaY-1 >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					} else if(coordenadaX+1 <= dimensionX && coordenadaY <= dimensionY && coordenadaX-1 >= 1 && coordenadaY-1 >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					} else if(coordenadaX <= dimensionX && coordenadaY <= dimensionY && coordenadaX-1 >= 1 && coordenadaY-1 >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					} else if(coordenadaX+1 <= dimensionX && coordenadaY+1 <= dimensionY && coordenadaX-1 >= 1 && coordenadaY >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					} else if(coordenadaX <= dimensionX && coordenadaY+1 <= dimensionY && coordenadaX-1 >= 1 && coordenadaY >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					} else if(coordenadaX+1 <= dimensionX && coordenadaY+1 <= dimensionY && coordenadaX >= 1 && coordenadaY-1 >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					} else if(coordenadaX+1 <= dimensionX && coordenadaY <= dimensionY && coordenadaX >= 1 && coordenadaY-1 >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					} else if(coordenadaX+1 <= dimensionX && coordenadaY+1 <= dimensionY && coordenadaX >= 1 && coordenadaY >= 1){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
					}
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					break;
				case 2:
					this->ponerUnTesoroInicial(ptrJugador, 5);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					break;
				case 3:
					cout << "ingrese coordenada Z para romper blindaje";
					cin >> coordenadaZ;
					cout << "ingrese coordenada X para romper blindaje";
					cin >> coordenadaX;
					cout << "ingrese coordenada Y para romper blindaje";
					cin >> coordenadaY;
					if(this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)){
						this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->sacarBlindaje();
					}
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					break;
				case 4:
					this->ingresarNuevoEspia(ptrJugador);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					this->ingresarNuevoEspia(ptrJugador);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					this->ingresarNuevoEspia(ptrJugador);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					break;
				case 5:
					this->ingresarNuevaMina(ptrJugador);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					this->ingresarNuevaMina(ptrJugador);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					this->ingresarNuevaMina(ptrJugador);
					this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
					break;
			}
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: juega la carta sacada.
		*/
		void jugarCartaSacada(Jugador* ptrJugador){
			this->jugarCartaN(ptrJugador,ptrJugador->getManoJugador()->getCartaSacada()->getTipoDeCarta());
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: saca nueva carta del mazo y decide si guardar o jugar.
		*/
		void accionarCarta(Jugador* ptrJugador){
			string nombresCartas[6]={"Blindaje","Radar","Partir Tesoro","Romper Blindaje","Triple Espia","Triple Mina"};
			if(ptrJugador->getEstado() == JUGADOR_ACTIVO){
				ManoIndividual* manoJugador = ptrJugador->getManoJugador();
				manoJugador->sacarCarta();
				manoJugador->printCartaSacada();
				unsigned int jugarOGuardar;
				cout << "ingrese 0 para jugar la carta / 1 Guardar la carta" << endl;
				cin >> jugarOGuardar;
				switch (jugarOGuardar){
				case 0:
					this->jugarCartaSacada(ptrJugador);
					break;
				case 1:
					manoJugador->guardarCarta();
					manoJugador->printCartasGuardadas();
					cout << " -------- " << endl;
					unsigned int tipoJugar;
					for(int i = 0; i < 6; i++){
						cout << nombresCartas[i] << " - " << i << endl;
					}
					cout << "6 - No jugar carta" << endl;
					cout << "ingrese TIPO carta del 0 al 5 :" << endl;
					cin >> tipoJugar;
					while(tipoJugar != 6 && !manoJugador->verificarCartaEnMazo((TipoDeCarta(tipoJugar)))){
						cout << "No tienes esa carta en tu mano, por favor elige otra..." << endl;
						cout << "ingrese TIPO carta del 0 al 5 :" << endl;
						cin >> tipoJugar;
					}
					if(tipoJugar != 6){
						Carta* carta =  manoJugador->getCarta(tipoJugar);
						this->jugarCartaN(ptrJugador, carta->getTipoDeCarta());
					}
					break;
				}
			}
		}

		/*
		* Pre: -
		* Post: juega el juego hasta que haya un ganador.
		*/
		void jugarJuegadores(){
			Lista<Jugador*>* ptrListPtrJugador = this->ptrListPtrJugador;
			ptrListPtrJugador->iniciarCursor();
			while ((ptrListPtrJugador->avanzarCursor()) ){ //&& (!this->juegoGanado()) NOOO REINICIA CURSOR SAINCE ES MISMA LISTA
				Jugador* ptrJugador = ptrListPtrJugador->obtenerCursor();
				this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
				this->eliminarJugador(ptrJugador);
				this->accionarCarta(ptrJugador);
				this->ingresarNuevaMina(ptrJugador);
				this->ingresarNuevoEspia(ptrJugador);
				this->realizarMovientoTesoro(ptrJugador);
				ptrJugador->reactivarJugador();
			}
		}

		/*
		* Pre: Recibe puntero a jugador y numero mayor a cero.
		* Post: Pide a jugador que ingrese su tesoro.
		*/
		void ponerUnTesoroInicial(Jugador* ptrJugador, unsigned int numeroDeTesoro){
			unsigned int coordenadaX, coordenadaY, coordenadaZ;
			unsigned int idJugador = ptrJugador->getId();
			cout << "Jugador " << idJugador << ": ingrese coordenada Z de tesoro " << numeroDeTesoro << ": ";
			cin >> coordenadaZ;
			//this->ptrtablero->mostrarPiso(coordenadaZ);
			cout << "Jugador " << idJugador << ": ingrese coordenada X de tesoro " << numeroDeTesoro << ": ";
			cin >> coordenadaX;
			cout << "Jugador " << idJugador << ": ingrese coordenada Y de tesoro " << numeroDeTesoro << ": ";
			cin >> coordenadaY;
			this->ptrtablero->agregarNuevoTesoro(ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
			this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
		}

		/*
		* Pre: Recibe puntero a jugador y numero de tesoros de cada jugador mayor a 0.
		* Post: Pide a cada jugador que ingrese sus tesoros totales.
		*/
		void ponerTesorosIniciales(Jugador* ptrJugador, unsigned int numeroDeTesorosPorJugador){
			unsigned int numeroDeTesoro = 1;
			this->imagen->exportarTablero(this->ptrtablero, ptrJugador);
			cout << "Jugador " << ptrJugador->getId() << ": ingresara sus " << numeroDeTesorosPorJugador << " tesoros" << endl;
			while (numeroDeTesoro <= numeroDeTesorosPorJugador){
				this->ponerUnTesoroInicial(ptrJugador, numeroDeTesoro);
				numeroDeTesoro++;
			}
		}


		/*
		* Pre: Recibe numero de tesoros de cada jugador mayor a 0.
		* Post: Pide a cada jugador que ingrese sus tesoros totales.
		*/
		void iniciarJuego(unsigned int numeroDeTesorosPorJugador){
			Lista<Jugador*>* ptrListPtrJugador = this->ptrListPtrJugador;
			string aux;


			ptrListPtrJugador->iniciarCursor();
			while (ptrListPtrJugador->avanzarCursor()){
				Jugador* ptrJugador = ptrListPtrJugador->obtenerCursor();
				this->ponerTesorosIniciales(ptrJugador, numeroDeTesorosPorJugador);
				cout << "Ingrese cualquier caracter para continuar: " << endl;
				cin >> aux;
			}
		}

		/*
		* Pre: -
		* Post: juega el juego hasta que haya un ganador.
		*/
		void jugarJuego(){
			while (!this->juegoGanado()){
				this->jugarJuegadores();
				this->eliminarJugadores();
			}
			cout << "Jugador " << this->obtenerGanador()->getId() << " gano.";
		}

		/*
		* Pre: -
		* Post: Libera los datos dinamicos de juego.
		*/
		~Juego(){
			Lista<Jugador*>* ptrListPtrJugador = this->ptrListPtrJugador;
			ptrListPtrJugador->iniciarCursor();
			while (ptrListPtrJugador->avanzarCursor()){
				delete ptrListPtrJugador->obtenerCursor();
			}
			delete this->ptrListPtrJugador;
			delete this->ptrtablero;
		}
};

#endif /* JUEGO_H_ */
