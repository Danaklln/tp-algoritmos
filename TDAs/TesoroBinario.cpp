/*
 * TesoroBinario.cpp
 *
 *  Created on: 19/10/2023
 *      Author: algo2
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "TesoroBinario.h"

using namespace std;

TesoroBinario::TesoroBinario(unsigned int cantidadJugadores,
		                     unsigned int x,
			                 unsigned int y,
							 unsigned int z,
			                 Interfaz * interfaz){

	this->tablero           = new Tablero(x,y,z);
	this->interfaz          = interfaz;
	this->jugadores         = new Jugador *[cantidadJugadores];
	this->cantidadJugadores = cantidadJugadores;

    //se inician los jugadores con sus ID
	for(int i = 0; i<cantidadJugadores; i++){
		this->jugadores[i] = Jugador(i+1);
	}

}

TesoroBinario::~TesoroBinario(){

	delete tablero;
	for(int i = 0; i<cantidadJugadores; i++){
		delete this->jugadores[i];
	}
	delete jugadores;
}

void TesoroBinario::colocarTesoros(Jugador * jugador){

	unsigned int x, y, z;
	Tesoro * nuevoTesoro;
	Lista <Tesoro*> * Tesoros;

	//se itera por los jugadores y se pide posición para cada tesoro
	for( int i=0; i<this->cantidadJugadores; i++ ){
		for(int j=0; j<this->CANTIDAD_TESOROS_INICIAL; j++){
			do{
				this->interfaz->pedirPosicionTesoro(&x,&y,&z);
				tesoros = tablero->obtenerPosicion(x, y, z)->getTesoros();

				//si no hay tesoros en la celda, se crea el nuevo tesoro
				if( tesoros->estaVacia == true ){
					tesoro = new Tesoro(j+1,this->jugadores[i],x,y,z);
					this->jugadores[i]->addTesoroPropio(tesoro);
					break;
				}
				//si ya hay tesoros, se pide otra posición
				else{
					this->interfaz->msj("Ya hay un tesoro en esa posición");
				}
			}
		}
	}

}


bool TesoroBinario::getResultadoPartida(Jugador ** ganador){

	unsigned int activos = 0;
	Jugador * jugador;

	*ganador = NULL;

	//se cuenta cuántos jugadores activos hay
	for(int i=0; i<this->cantidadJugadores; i++){
		if(this->jugadores[i]->getEstado() == ACTIVO){
			++activos;
			jugador = this->jugadores[i];
		}
	}

	//si hay uno solo, es el ganador
	if(activos == 1){
		*ganador = jugador;
		return true;
	}

	return false;
}

bool TesoroBinario::iniciarJuego(){

	unsigned int turno = 1;
	unsigned int x, y, z;
	bool salir = false;
	tError error = OK;
	tResultado resultado;
	tCarta carta;
	Jugador * jugador;
	Jugador * ganador = NULL;

	//se colocan los tesoros en el tablero
	this->colocarTesoros( );
	interfaz->msjTesorosColocados();

	//se dibujan los tableros de cada jugador con las posiciones
	//iniciales de los tesoros
	for(int i=0; i<this->cantidadJugadores; i++){
		this->interfaz->dibujarTablero(this->jugadores[i]);
	}

	while(salir == false){

		for(int i=0; i<this->cantidadJugadores; i++){

			jugador = this->jugadores[i];
			interfaz->msjTurno(jugador->getId());

			//el jugador elige la opción a realizar
			// TODO crear método enum interfaz->pedirAccion()
			accion = this->interfaz->pedirAccion();

			switch(accion){

				case SACAR_CARTA:

					carta = this->sacarCarta( );
					if( interfaz->preguntarJugarCarta() = SI ){
						this->jugarCarta(jugador, carta);
					}
					else{
						jugador->addCarta(carta);
					}
					break;

				case JUGAR_CARTA:

					posicionCarta = this->interfaz->pedirElegirCarta(jugador->getCartasEnMano(), &carta);
					// TODO crear mètodo: Jugador->eliminarCarta(posicion)
					jugador->eliminarCarta(posicionCarta);
					this->jugarCarta(jugador, carta);
					break;

				case MOVER_TESORO:

					this->moverTesoro(jugador);
					break;

				case COLOCAR_ESPIA:

					this->colocarEspia(jugador);
					break;

				case COLOCAR_MINA:

					this->colocarMina(jugador);
					break;
			}

			salir = getResultadoPartida(&ganador);
			if( ganador != NULL ){
				interfaz->msjGanador(ganador->getId());
			}

		}

		this->actualizarCasillasInactivas();
		++turno;
	}

	return salir;
}

void TesoroBinario::moverTesoro(Jugador * jugador){

	bool ok = false;
	unsigned int id;
	unsigned int xi, yi, zi; //posición origen
	unsigned int xf, yf, zf; //posición destino
	Tesoro * tesoro = NULL,
		   * tesoroAux;
	Celda * celdaOrigen,
	      * celdaDestino;

	//se obtiene ID y puntero al tesoro a mover
	while(!tesoro){
		id     = this->interfaz->pedirIdTesoro();
		tesoro = jugador->getTesoro(id);
		if(!tesoro){
			interfaz->msj("Tesoro inválido, ingrese otro")
		}
	}

	while(ok == false)

		//se pide posición destino
		this->interfaz->pedirPosicionTesoro(&xf, &yf, &zf);

		//TODO chequear posición

		tesoro->getPosicion(&xi,&yi,&zi); //TODO
		celdaOrigen  = this->tablero->obtenerPosicion(xi,yi,zi);
		celdaDestino = this->tablero->obtenerPosicion(xf,yf,zf);

		//acciones:

		//celda inactiva: no puede mover
		if( celdaDestino->getEstado() == INACTIVO){
			this->interfaz->msj("Celda inactiva, no se puede mover tesoro");
		}
		//hay mina: pierde tesoro, explota la mina y queda celda inactiva
		else if( celdaDestino->obtenerMina() ){
			celdaDestino->eliminarMina(); //TODO
			celdaDestino->setEstado(INACTIVO);
			celdaDestino->setTurnosInactivosRestantes(this->TURNOS_INACTIVO_INICIAL);
			jugador->eliminarTesoro(tesoro); //TODO
			celdaOrigen->eliminarTesoro(tesoro); //TODO
			this->interfaz->msj("Hay una mina, perdiste el tesoro");
			ok = true;
		}
		//si hay espía rival: pierde el tesoro y se inactiva la celda
		//si es espía propio, puede mover
		else if( espia = celdaDestino->obtenerEspia() ){
			jugadorEspia = espia->getJugador();
			if(jugadorEspia != jugador){
				celdaDestino->setEstado(INACTIVO);
				celdaDestino->eliminarEspia(); //TODO
				celdaDestino->setTurnosInactivosRestantes(this->TURNOS_INACTIVO_INICIAL);
				jugador->eliminarTesoro(tesoro);
				celdaOrigen->eliminarTesoro(tesoro);
			}
			else{
				celdaOrigen->eliminarTesoro(tesoro);
				celdaDestino->addTesoro(tesoro); //TODO
				tesoro->setPosicion(xf,yf,zf);
			}
			ok = true;
		}
		//Si hay algún tesoro rival, mueve y le avisa al jugador
		else if( tesoros = celdaDestino->obtenerTesoros() ){
			tesoros->iniciarCursor();
			while(tesoros->avanzarCursor() == true){
				tesoroAux = tesoros->obtenerCursor();
				if( tesoroAux->getJugador() == jugador ){
					this->interfaz->msj("Encontraste un tesoro rival!")
					break;
				}
			}
			celdaOrigen->eliminarTesoro(tesoro);
			celdaDestino->addTesoro(tesoro);
			tesoro->setPosicion(xf,yf,zf);
			ok = true;
		}
		//se mueve el tesoro
		else{
			celdaOrigen->eliminarTesoro(tesoro);
			celdaDestino->addTesoro(tesoro);
			tesoro->setPosicion(xf,yf,zf);
			this->interfaz->msj("Se movió el tesoro")
			ok = true;
		}
	}

}

void TesoroBinario::colocarEspia(Jugador * jugador){

	bool ok = false;
	unsigned int x, y, z;
	Celda * celdaDestino;
	Espia * espia,
	      * espiaAux;
	Tesoro * tesoroAux;
    Lista<Tesoro *> * tesoros;
    Jugador * jugadorAux;

	while(ok == false){

		this->interfaz->pedirPosicionEspia(&x, &y, &z);
		//TODO chequear posición

		celdaDestino = this->tablero->obtenerPosicion(x,y,z);

		//acciones:

		//celda inactiva: no puede colocar espía
		if( celdaDestino->getEstado() == INACTIVO){
			this->interfaz->msj("Celda inactiva, no se puede colocar espía");
		}
		//hay mina: no se coloca espía, explota la mina y queda celda inactiva
		else if( celdaDestino->obtenerMina() ){
			celdaDestino->eliminarMina();
			celdaDestino->setEstado(INACTIVO);
			celdaDestino->setTurnosInactivosRestantes(this->TURNOS_INACTIVO_INICIAL);
			this->interfaz->msj("Hay una mina, se pierde el espía");
			ok = true;
		}
		//si hay espía rival: no se coloca espía y se elimina el rival
		//si es espía propio: no se puede colocar espía
		else if( espiaAux = celdaDestino->obtenerEspia() ){
			jugadorEspia = espiaAux->getJugador();
			if(jugadorEspia != jugador){
				celdaDestino->eliminarEspia();
				this->interfaz->msj("Hay un espía contrario, se eliminan ambos");
				ok = true;
			}
			else{
				this->interfaz->msj("Ya hay un espía propio en la casilla");
			}
		}
		//Si hay algún tesoro rival, se captura, si no está blindado
		else if( tesoros = celdaDestino->obtenerTesoros() ){
			tesoros->iniciarCursor();
			while(tesoros->avanzarCursor() == true){
				tesoroAux = tesoros->obtenerCursor();
				if( (jugadorAux = tesoroAux->getJugador()) != jugador ){
					if( tesoroAux->estaBlindado == true){
						//tesoro blindado, sólo se coloca espía
						espia = new Espia(jugador,x,y,z);
						celdaDestino->addEspia(espia);
						this->interfaz->msj("Se colocó espía");
					}
					else{
						celdaDestino->setEstado(INACTIVO);
						celdaDestino->setTurnosInactivosRestantes(this->TURNOS_INACTIVO_INICIAL);
						jugadorAux->eliminarTesoro(tesoroAux);
						celdaOrigen->eliminarTesoro(tesoroAux);
						this->interfaz->msj("Se captura un tesoro");
					}
					break;
				}
			}
			ok = true;
		}
		//se coloca espía
		else{
			espia = new Espia(jugador,x,y,z);
			celdaDestino->addEspia(espia);
			this->interfaz->msj("Se colocó espía")
			ok = true;
		}
	}

}

void TesoroBinario::colocarMina(Jugador * jugador){

	bool ok = false;
	bool explota = false;
	Tesoro * tesoro;
	Lista<Tesoro*> * tesoros;
	unsigned int x, y, z;
	Celda * celdaDestino;

	while(ok == false){
		this->interfaz->pedirPosicionMina(&x, &y, &z);

		//TODO chequear posición

		celdaDestino = this->tablero->obtenerPosicion(x,y,z);

		//acciones:

		//celda inactiva: no puede colocar mina
		if( celdaDestino->getEstado() == INACTIVO){
			this->interfaz->msj("Celda inactiva, no se puede colocar mina");
		}
		//hay mina: explotan ambas minas
		else if( celdaDestino->obtenerMina() ){
			celdaDestino->eliminarMina();
			celdaDestino->setEstado(INACTIVO);
			celdaDestino->setTurnosInactivosRestantes(this->TURNOS_INACTIVO_INICIAL);
			this->interfaz->msj("Hay una mina, explotan ambas");
			ok = true;
		}
		//si hay otras piezas se eliminan
		else{

			if( celdaDestino->obtenerEspia() ){
				celdaDestino->eliminarEspia();
				explota = true;
				this->interfaz->msj("Espía destruido!");
			}

			if( tesoros = celdaDestino->obtenerTesoros() ){
				tesoros->iniciarCursor();
				while(tesoros->avanzarCursor() == true){
					tesoro = tesoros->obtenerCursor();
					celdaDestino->eliminarTesoro(tesoro);
					explota = true;
					this->interfaz->msj("Tesoro destruido!");
					}
				}
			}

			if( explota = true){
				//se eliminaron las piezas y explotó la mina
				this->interfaz->msj("Explota la mina");
				celdaDestino->setEstado(INACTIVO);
				celdaDestino->setTurnosInactivosRestantes(this->TURNOS_INACTIVO_INICIAL);
			}
			else{
				//se coloca la mina
				mina = new Mina(jugador,x,y,z);
				celdaDestino->addMina(mina);
				this->interfaz->msj("Se colocó la mina")
			}


			ok = true;
		}
	}

}

unsigned int TesoroBinario::sacarCarta( ){

	//se elige una carta aleatoriamente
	srand(time(0));
	return rand() % 6 + 1;
}

void TesoroBinario::jugarCarta(Jugador * jugador, tCarta carta){

	switch(carta){

		case BLINDAJE:
			this->cartaBlindaje(jugador);
			break;
		case RADAR:
			this->cartaRadar(jugador);
			break;
		case PARTIR_TESORO:
			this->cartaPartirTesoro(jugador);
			break;
		case ROMPER_BLINDAJE:
			this->cartaRomperBlindaje(jugador);
			break;
		case TESORO_EN_PELIGRO:
			this->cartaTesoroEnPeligro(jugador);
			break;
		case TRIPLE_MINA:
			this->cartaTripleMina(jugador);
			break;
		default:
			break;
	}

}

void TesoroBinario::cartaBlindaje(Jugador * jugador){

	do{
		//pedir ID de tesoro a blindar
		idTesoro = this->interfaz->pedirIdTesoro();
		tesoro = jugador->getTesoro(idTesoro);
		if(!tesoro){
			//tesoro inválido
			this->interfaz->msjTesoroInvalido();
		}
		else{
			//se blinda el tesoro
			tesoro->setBlindado(true);
			//Si es parte de un tesoro partido, se blinda también
			//la otra mitad
			if( tesoroPadre = tesoro->getTesoroPadre() ){
				tesoroPadre->setBlindado(true);
			}
			else if( tesoroHijo = tesoro->getTesoroHijo() ){
				tesoroHijo->setBlindado(true);
			}
			break;
		}
	}


}

void TesoroBinario::cartaPartirTesoro(Jugador * jugador){

	do{
		//pedir ID de tesoro a partir
		idTesoro = this->interfaz->pedirIdTesoro();
		tesoro = jugador->getTesoro(idTesoro);
		if(!tesoro){
			//tesoro inválido
			this->interfaz->msjTesoroInvalido();
		}
		else if( tesoro->getTesoroHijo() || tesoro->getTesoroPadre()) ){
			//el tesoro ya fue partido
			this->interfaz->msjTesoroYaPartido();
		}
		else{
			//se agrega nuevo tesoro
			// TODO agregar método que me de ID libre de tesoro
			nuevoTesoro = new Tesoro(jugador->getCantidadTesoros() + 1, jugador);
			nuevoTesoro->setTesoroPadre(tesoro);
			tesoro->setTesoroHijo(nuevoTesoro);
			jugador->addTesoroPropio(nuevoTesoro);
			this->interfaz->pedirPosicion(&x,&y,&z);
			break;
		}
	}


}

void TesoroBinario::cartaRadar(Jugador * jugador){
	//TODO implementar radar

}

void TesoroBinario::cartaRomperBlindaje(Jugador * jugador){
	//TODO implementar romper blindaje

}

void TesoroBinario::cartaTesoroEnPeligro(Jugador * jugador){
	//TODO implementar tesoro en peligro

}

void TesoroBinario::cartaTripleMina(Jugador * jugador){
	//TODO implementar triple mina

}

void TesoroBinario::actualizarCasillasInactivas(){



}

/*agregar método obtenerProximoJugador()


