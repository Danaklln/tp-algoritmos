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
		* Pre: Recibe numero de tesoros de cada jugador mayor a 0.
		* Post: Pide a cada jugador que ingrese sus tesoros totales.
		*/
		void ponerTesorosIniciales(Jugador* ptrJugador, unsigned int numeroDeTesorosPorJugador){
			unsigned int coordenadaX, coordenadaY, coordenadaZ;
			this->ptrtablero->pasarTurnoTablero(ptrJugador);
			unsigned int idJugador = ptrJugador->getId();
			unsigned int numeroDeTesoro = 1;
			cout << "Jugador " << idJugador << " ingresara sus " << numeroDeTesorosPorJugador << " tesoros" << endl;
			while (numeroDeTesoro <= numeroDeTesorosPorJugador){
				cout << "Jugador " << idJugador << ": ingrese coordenada Z de tesoro " << numeroDeTesoro << ": "; 
				cin >> coordenadaZ;
				this->ptrtablero->mostrarPiso(coordenadaZ);
				cout << "Jugador " << idJugador << ": ingrese coordenada X de tesoro " << numeroDeTesoro << ": "; 
				cin >> coordenadaX;
				cout << "Jugador " << idJugador << ": ingrese coordenada Y de tesoro " << numeroDeTesoro << ": "; 
				cin >> coordenadaY;
				this->ptrtablero->agregarNuevoTesoro(ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
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
		* Post: Elimina del juego a cualquier jugador que no tenga ningun tesoro.
		*/
		void eliminarJugadores(){
			Lista<Jugador*>* ptrListPtrJugador = this->ptrListPtrJugador;
			ptrListPtrJugador->iniciarCursor();
			while (ptrListPtrJugador->avanzarCursor()){
				Jugador* ptrJugador = ptrListPtrJugador->obtenerCursor();
				if (this->ptrtablero->obtenerUnTesoro(ptrJugador) == NULL){
					ptrJugador->eliminarJugador();
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
			while (ptrListPtrJugador->avanzarCursor()){
				Jugador* ptrJugador = ptrListPtrJugador->obtenerCursor();
				this->ptrtablero->pasarTurnoTablero(ptrJugador);
				unsigned int idJugador = ptrJugador->getId();
				if (ptrJugador->getEstado() == JUGADOR_ACTIVO){
					unsigned int coordenadaX, coordenadaY, coordenadaZ;
					cout << "turno de Jugador " << idJugador << ": Ingrese coordenada Z de nueva mina: ";
					cin >> coordenadaZ;
					this->ptrtablero->mostrarPiso(coordenadaZ);
					cout << "Jugador " << idJugador << ": ingrese coordenada X de nueva mina: "; 
					cin >> coordenadaX;
					cout << "Jugador " << idJugador << ": ingrese coordenada Y de nueva mina: "; 
					cin >> coordenadaY;
					this->ptrtablero->agregarNuevaMina(3, ptrJugador, coordenadaX, coordenadaY, coordenadaZ);
				}
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
				if (ptrJugador->getEstado() == JUGADOR_ACTIVO){
					this->ptrtablero->moverTesoro(ptrJugador);
				}
				ptrJugador->reactivarJugador();
			}	
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




int main() {
	unsigned int numeroDeJugadores = 2, dimensionX = 4, dimensionY = 3, dimensionZ = 2, numeroDeTesorosPorJugador = 1;
	Juego* ptrjuego = new Juego(numeroDeJugadores, dimensionX, dimensionY, dimensionZ);
	ptrjuego->iniciarJuego(numeroDeTesorosPorJugador);
	ptrjuego->jugarJuego();
	return 0;
}
