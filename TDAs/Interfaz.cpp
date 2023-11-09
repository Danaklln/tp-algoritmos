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

tError Interfaz::setArchivosSalida(char * archJugador1, char * archJugador2){

	this->archJugador1.open(archJugador1, ofstream::out | ofstream::trunc);
	if(this->archJugador1.fail()){
		return ERROR_ARCHIVO;
	}

	this->archJugador2.open(archJugador2, ofstream::out | ofstream::trunc);
	if(this->archJugador2.fail()){
		return ERROR_ARCHIVO;
	}

	return OK;
}

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

void Interfaz::msjError(tError error){

	switch(error){
		case OK:
			break;
		case ERROR_JUGADOR_1_NULL:
			cout << MSJ_ERROR_JUGADOR_1_NULL << endl;
			break;
		case ERROR_JUGADOR_2_NULL:
			cout << MSJ_ERROR_JUGADOR_2_NULL << endl;
			break;
		case ERROR_JUGADOR_NULL:
			cout << MSJ_ERROR_JUGADOR_NULL << endl;
			break;
		case ERROR_ARCHIVO:
			cout << MSJ_ERROR_ARCHIVO << endl;
			break;
		case ERROR_POSICION_INVALIDA:
			cout << MSJ_ERROR_POSICION_INVALIDA << endl;
			break;
		case ERROR_CASILLA_INACTIVA:
			cout << MSJ_ERROR_CASILLA_INACTIVA << endl;
			break;
		case ERROR_CASILLA_INVALIDA:
			cout << MSJ_ERROR_CASILLA_INVALIDA << endl;
			break;
		case ERROR_TESORO_INVALIDO:
			cout << MSJ_ERROR_TESORO_INVALIDO << endl;
			break;
		case ERROR_HAY_TESORO:
			cout << MSJ_ERROR_HAY_TESORO << endl;
			break;
		case ERROR_HAY_ESPIA:
			cout << MSJ_ERROR_HAY_ESPIA << endl;
			break;
		case ERROR_DIRECCION_INVALIDA:
			cout << MSJ_ERROR_DIRECCION_INVALIDA << endl;
			break;
		case ERROR_DESCONOCIDO:
			cout << MSJ_ERROR_DESCONOCIDO << endl;
			break;
		default:
			cout << MSJ_ERROR_DESCONOCIDO << endl;
			break;
	}

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

void Interfaz::pedirPosicionEspia(unsigned int * fila, unsigned int * col){

	cout << MSJ_PEDIR_POS_ESPIA << endl;
	cin >> *fila >> *col;
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
		default:
			break;
	}
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

Interfaz::~Interfaz(){

	this->archJugador1.close();
	this->archJugador2.close();

}

