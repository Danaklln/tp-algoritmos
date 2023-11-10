//*****************************************************************************
// FIUBA - Algoritmos II 75.41
// TP 1 - Tesoro Binario
// Autor: Javier Romani
// Fecha: 15/09/2023
// Archivo: interfaz.cpp
// Descripciòn: Implementaciòn de clase Interfaz
//*****************************************************************************

#include "interfaz.h"

using namespace std;


bool Interfaz::msjBienvenida(){

	char opcion;

	cout << MSJ_BIENVENIDA << endl
		 << MSJ_OPC_JUGAR << endl
		 << MSJ_OPC_SALIR << endl;

	while( cin >> opcion ){
		switch (opcion){
		case OPC_JUGAR:
			return false;
		case OPC_SALIR:
			return true;
		default:
			continue;
		}
	}

	return true;

}


void Interfaz::msjSalida(){

	cout << MSJ_SALIDA << endl;

}

void Interfaz::msjTesorosColocados(){

	cout << MSJ_INICIA_JUEGO << endl
	     << MSJ_TESOROS_COLOCADOS << endl;

}

void Interfaz::msjTurno(int jugador){

	cout << endl << SEPARADOR_TURNOS << endl
	     << MSJ_TURNO << jugador << endl
		 << SEPARADOR_TURNOS << endl << endl;
}

void Interfaz::pedirPosicionEspia(unsigned int * x, unsigned int * y, unsigned int * z){

	cout << MSJ_PEDIR_POS_ESPIA << endl;
	cin >> *x >> *y >> *z;
}

void Interfaz::pedirPosicionMina(unsigned int * x, unsigned int * y, unsigned int * z){

	cout << MSJ_PEDIR_POS_MINA << endl;
	cin >> *x >> *y >> *z;
}

void Interfaz::pedirPosicionTesoro(unsigned int * x, unsigned int * y, unsigned int * z){

	cout << MSJ_PEDIR_POS_TESORO << endl;
	cin >> *x >> *y >> *z;
}

void Interfaz::msjResultado(tResultado resultado){

	switch(resultado){
		case ESPIA_COLOCADO:
			cout << MSJ_ESPIA_COLOCADO << endl;
			break;
		case TESORO_COLOCADO:
			cout << MSJ_TESORO_COLOCADO << endl;
			break;
		case PIERDE_TESORO:
			cout << MSJ_PIERDE_TESORO << endl;
			break;
		case CAPTURA_TESORO:
			cout << MSJ_CAPTURA_TESORO << endl;
			break;
		case COLISION_DE_ESPIAS:
			cout << MSJ_COLISION_DE_ESPIAS << endl;
			break;
		case TESORO_RIVAL_ENCONTRADO:
			cout << MSJ_COLISION_DE_TESOROS << endl;
			break;
		case TESORO_RIVAL_BLINDADO:
			cout << "Se encontro un tesoro blindado del oponenete!" << endl;
			break;
		case RADAR_ENCONTRO_TESORO:
			cout << "El radar ha encontrado un tesoro enemigo!" << endl;
			break;
		case BLINDAJE_ENEMIGO_ROTO:
			cout << "Has roto el blindaje de un tesoro enemigo!" << endl;
			break;
		case BLINDAJE_PROPIO_ROTO:
			cout << "El enemigo ha roto el blindaje de uno de tus tesoros!" << endl;
			break;
		case MINA_DESCUBIERTA:
			cout << "Has descubierto una mina enemiga, pierdes el turno!" << endl;
			break;
		case MINA_ACIERTO:
			cout << "La mina destruyo un tesoro!" << endl;
			break;
		case MINA_FALLO:
			cout << "La mina no encontro ningun tesoro" << endl;
			break;
		default:
			break;
	}
}

void Interfaz::msjYaHayTesoro(){
	cout << "Ya hay un tesoro en la casilla que seleccionaste." << endl;
}

void Interfaz::msjGanador(int id){
	cout << "El jugador " << id << " gana la partida!" << endl;
}

void Interfaz::msjEmpate(){
	cout << MSJ_EMPATE << endl;
}

tOpcion Interfaz::preguntarMoverTesoro(){

	int opcionAux;
	tOpcion opcion;

	cout << MSJ_PREGUNTA_MOVER_TESORO << endl;
	while(true){
		cin >> opcionAux;
		opcion = (tOpcion) opcionAux;
		switch (opcion){
			case SI:
				return opcion;
			case NO:
				return opcion;
			default:
				continue;
		}
	}

	return opcion; //sólo para evitar warning del compilador ;)
}

unsigned int Interfaz::pedirIdTesoro(){

	unsigned int id;

	cout << MSJ_PEDIR_ID_TESORO << endl;
	cin >> id;
	return id;
}

unsigned char Interfaz::pedirDireccion(){

	unsigned int direccion;

	cout << MSJ_PEDIR_DIRECCION << endl
	     << MSJ_AYUDA_DIRECCIONES << endl;
	cin >> direccion;
	return( (unsigned char) direccion );
}


unsigned int Interfaz::pedirElegirCarta(Lista<tCarta> * cartas){
	tCarta cartaElegida;
	int cartaAux;
	unsigned int posicion = 0;
	while(posicion == 0){
		cout << "Estas son las cartas de tu mano:" << endl;

		unsigned int blindaje = 0, radar = 0, partirTesoro = 0, romperBlindaje = 0, tesoroEnPeligro = 0, tripleMina = 0;
		cartas->iniciarCursor();
		while(cartas->avanzarCursor()){
			switch(cartas->obtenerCursor()){
			case BLINDAJE:
				blindaje++;
				break;
			case RADAR:
				radar++;
				break;
			case PARTIR_TESORO:
				partirTesoro++;
				break;
			case ROMPER_BLINDAJE:
				romperBlindaje++;
				break;
			case TESORO_EN_PELIGRO:
				tesoroEnPeligro++;
				break;
			case TRIPLE_MINA:
				tripleMina++;
				break;
			default:
				break;
			}
		}

		cout << "1-BLINDAJE x" << blindaje << endl
			<< "2-RADAR x" << radar << endl
			<< "3-PARTIR TESORO x" << partirTesoro << endl
			<< "4-ROMPER BLINDAJE x" << romperBlindaje << endl
			<< "5-TESORO EN PELIGRO x" << tesoroEnPeligro << endl
			<< "6-TRIPLE MINA x" << tripleMina << endl;

		cout << "Elige que carta quieres jugar:" << endl;
		cin >> cartaAux;
		cartaElegida = (tCarta) cartaAux;

		unsigned int indice = 1;
		cartas->iniciarCursor();
		while (cartas->avanzarCursor() && posicion == 0){
			if (cartas->obtenerCursor() == cartaElegida){
				posicion = indice;
			}
			indice++;
		}
		if(posicion == 0){
			cout << "No puedes usar la carta que seleccionaste." << endl;
		}

	}
	return posicion;
}

tOpcion Interfaz::preguntarJugarCarta(){
	int opcionAux;
	tOpcion opcion;

	cout << "¿Desea jugar una carta? 1=Sì, 2=No" << endl;
	while(true){
		cin >> opcionAux;
		opcion = (tOpcion) opcionAux;
		switch (opcion){
			case SI:
				return opcion;
			case NO:
				return opcion;
			default:
				continue;
		}
	}

	return opcion; //sólo para evitar warning del compilador ;)
}

void Interfaz::pedirDimensiones(unsigned int * x, unsigned int * y, unsigned int * z){

	cout << "Indique las dimensiones del tablero con las que quiere jugar:" << endl;

	cout << "Ancho: ";
	cin >> *x;

	cout << "Alto: ";
	cin >> *y;

	cout << "Profundidad: ";
	cin >> *z;

}

unsigned int Interfaz::pedirCantidadJugadores(){
	unsigned int cantidad;

	cout << "Indique la cantidad de jugadores: ";
	cin >> cantidad;

	return cantidad;
}





Interfaz::~Interfaz(){

	this->archJugador1.close();
	this->archJugador2.close();

}

