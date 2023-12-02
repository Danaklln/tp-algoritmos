#ifndef JUEGO_H_
#define JUEGO_H_

#include <iostream>
#include "Lista.h"
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "Celda.h"
#include "Tablero.h"

using namespace std;

class Juego{

	private:

		Lista<Jugador*>* ptrListPtrJugador;
		Tablero* ptrtablero;

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
		* Post: Devuelve true si alguien gano el juego.
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
				this->ptrtablero->mostrarPiso(coordenadaZ);
				cout << "Jugador " << idJugador << ": ingrese coordenada X de nueva mina: "; 
				cin >> coordenadaX;
				cout << "Jugador " << idJugador << ": ingrese coordenada Y de nueva mina: "; 
				cin >> coordenadaY;
				this->ptrtablero->agregarNuevaMina(3, ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
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
					this->ptrtablero->mostrarPiso(coordenadaZ);
					cout << "Jugador " << idJugador << ": ingrese coordenada X de nuevo espia: "; 
					cin >> coordenadaX;
					cout << "Jugador " << idJugador << ": ingrese coordenada Y de nuevo espia: "; 
					cin >> coordenadaY;
					this->ptrtablero->agregarNuevoEspia( ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
			}
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: Mueve un tesoro.
		*/
		void realizarMovientoTesoro(Jugador* ptrJugador){
			if (ptrJugador->getEstado() == JUGADOR_ACTIVO){
					this->ptrtablero->moverTesoro(ptrJugador);
				}
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: juega la carta sacada.
		*/
		void jugarCartaN(Jugador* ptrJugador,unsigned int TipoDeCarta){
			switch (TipoDeCarta)
			{
			case 0:
				unsigned int coordenadaX, coordenadaY, coordenadaZ;
				cout << "ingrese coordenada Z para blindar"; 
				cin >> coordenadaZ;
				this->ptrtablero->mostrarPiso(coordenadaZ);
				cout << "ingrese coordenada X para blindar"; 
				cin >> coordenadaX;
				cout << "ingrese coordenada Y para blindar"; 
				cin >> coordenadaY;
				this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->blindarTesoros(ptrJugador, 3);
				break;

			case 1:
				unsigned int coordenadaX, coordenadaY, coordenadaZ;
				cout << "ingrese coordenada Z para Radar"; 
				cin >> coordenadaZ;
				this->ptrtablero->mostrarPiso(coordenadaZ);
				cout << "ingrese coordenada X para radar"; 
				cin >> coordenadaX;
				cout << "ingrese coordenada Y para radar"; 
				cin >> coordenadaY;
				this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				this->ptrtablero->obtenerPtrCelda(coordenadaX+1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				this->ptrtablero->obtenerPtrCelda(coordenadaX+2, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				this->ptrtablero->obtenerPtrCelda(coordenadaX-1, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				this->ptrtablero->obtenerPtrCelda(coordenadaX-2, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY+1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY+2, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY-1, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY-2, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->setVisibilidad(TESORO_REVELADO);
				break;
			case 2:
				this->ponerUnTesoroInicial(ptrJugador, 5);
				break;
			case 3:
				unsigned int coordenadaX, coordenadaY, coordenadaZ;
				cout << "ingrese coordenada Z para Radar"; 
				cin >> coordenadaZ;
				this->ptrtablero->mostrarPiso(coordenadaZ);
				cout << "ingrese coordenada X para radar"; 
				cin >> coordenadaX;
				cout << "ingrese coordenada Y para radar"; 
				cin >> coordenadaY;
				this->ptrtablero->obtenerPtrCelda(coordenadaX, coordenadaY, coordenadaZ)->obtenerTesoroContrario(ptrJugador)->sacarBlindaje();
				break;
			case 4:
				this->ingresarNuevoEspia(ptrJugador);
				this->ingresarNuevoEspia(ptrJugador);
				this->ingresarNuevoEspia(ptrJugador);
				break;
			case 5:
				this->ingresarNuevaMina(ptrJugador);this->ingresarNuevaMina(ptrJugador);this->ingresarNuevaMina(ptrJugador);
				break;
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: juega la carta sacada.
		*/
		void jugarCartaSacada(Jugador* ptrJugador){
			this->jugarcartaN(ptrJugador,ptrJugador->getManoJugador()->getCartaSacada()->getTipoDeCarta());
		}

		/*
		* Pre: Recibe un puntero a jugador.
		* Post: saca nueva carta del mazo y decide si guardar o jugar.
		*/
		void accionarCarta(Jugador* ptrJugador){
			ManoIndividual* manoJugador = ptrJugador->getManoJugador();
			manoJugador->sacarCarta();
			unsigned int jugarOGuardar;
			cout << "ingrese Guardar la carta 0, Jugar la carta 1" << endl;
			cin >> jugarOGuardar;
			switch (jugarOGuardar){
			case 0:
				this->jugarCartaSacada(ptrJugador);
				break;
			case 1:
				manoJugador->guardarCarta();
				manoJugador->getCartasGuardadas();
				unsigned int tipoJugar;
				cout << "ingrese TIPO carta del 0 al 5 :" << endl;
				cin >> tipoJugar;
				Carta* carta =  manoJugador->getCarta(tipoJugar);
				this->jugarcartaN(carta->getTipoDeCarta());
				break;
			}
		}

		/*
		* Pre: -
		* Post: juega el juego hasta que haya un ganador.
		*/
		void jugarJuegadores(){
			Lista<Jugador*>* ptrListPtrJugador = this->ptrListPtrJugador;
			ptrListPtrJugador->iniciarCursor();
			while ((ptrListPtrJugador->avanzarCursor())){ 
				Jugador* ptrJugador = ptrListPtrJugador->obtenerCursor();
				this->ptrtablero->pasarTurnoTablero(ptrJugador);
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
			this->ptrtablero->mostrarPiso(coordenadaZ);
			cout << "Jugador " << idJugador << ": ingrese coordenada X de tesoro " << numeroDeTesoro << ": "; 
			cin >> coordenadaX;
			cout << "Jugador " << idJugador << ": ingrese coordenada Y de tesoro " << numeroDeTesoro << ": "; 
			cin >> coordenadaY;
			this->ptrtablero->agregarNuevoTesoro(ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
		}

		/*
		* Pre: Recibe puntero a jugador y numero de tesoros de cada jugador mayor a 0.
		* Post: Pide a cada jugador que ingrese sus tesoros totales.
		*/
		void ponerTesorosIniciales(Jugador* ptrJugador, unsigned int numeroDeTesorosPorJugador){
			this->ptrtablero->pasarTurnoTablero(ptrJugador);
			unsigned int numeroDeTesoro = 1;
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
			ptrListPtrJugador->iniciarCursor();
			while (ptrListPtrJugador->avanzarCursor()){
				Jugador* ptrJugador = ptrListPtrJugador->obtenerCursor();
				this->ponerTesorosIniciales(ptrJugador, numeroDeTesorosPorJugador);
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
