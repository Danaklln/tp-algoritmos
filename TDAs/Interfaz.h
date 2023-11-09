//*****************************************************************************
// FIUBA - Algoritmos II 75.41
// TP 1 - Tesoro Binario
// Autor: Javier Romani
// Fecha: 15/09/2023
// Archivo: interfaz.h
// Descripciòn: Cabecera de clase Interfaz para encapsular manejo de E/S de
//              datos y mensajes al usuario.
//*****************************************************************************

#ifndef SRC_INTERFAZ_H_
#define SRC_INTERFAZ_H_

#include <iostream>
#include <fstream>

#include "codigosError.h"

#define SEPARADOR_TURNOS "******************************************************"

//mensajes informativos:
#define MSJ_BIENVENIDA             "Bienvenido a Tesoro Binario! Ingrese una opción:"
#define MSJ_OPC_JUGAR              "1 para jugar"
#define MSJ_OPC_SALIR              "2 para salir"
#define MSJ_SALIDA                 "Hasta luego!"
#define MSJ_INICIA_JUEGO           "Inicia el juego:"
#define MSJ_TESOROS_COLOCADOS      "Se colocaron los tesoros para ambos jugadores"
#define MSJ_TURNO                  "Es el turno del jugador "
#define MSJ_PEDIR_POS_ESPIA        "Ingrese fila y columna para colocar espía, separados por espacio:"
#define MSJ_EMPATE                 "Se ha producido un empate!!"
#define MSJ_PREGUNTA_MOVER_TESORO  "¿Desea mover un tesoro? 1=Sì, 2=No"
#define MSJ_PEDIR_ID_TESORO        "Ingrese número de tesoro a mover:"
#define MSJ_PEDIR_DIRECCION        "Ingrese dirección de movimiento:"
#define MSJ_AYUDA_DIRECCIONES      "1=→ 2=↗ 3=↑ 4=↖ 5=← 6=↙ 7=↓ 8=↘"

//mensajes de error:
#define MSJ_ERROR_JUGADOR_1_NULL          "Error al inicializar jugador 1"
#define MSJ_ERROR_JUGADOR_2_NULL          "Error al inicializar jugador 2"
#define MSJ_ERROR_JUGADOR_NULL            "Error al inicializar jugador"
#define	MSJ_ERROR_ARCHIVO                 "Error al abrir archivo"
#define MSJ_ERROR_POSICION_INVALIDA       "La casilla ingresada no existe"
#define MSJ_ERROR_CASILLA_INACTIVA        "La casilla elegida está inactiva"
#define MSJ_ERROR_CASILLA_INVALIDA        "Ingrese una casilla válida"
#define MSJ_ERROR_TESORO_INVALIDO         "El tesoro ingresado no existe"
#define MSJ_ERROR_HAY_TESORO              "La casilla está ocupada por un tesoro propio"
#define MSJ_ERROR_HAY_ESPIA               "La casilla está ocupada por un espía propio"
#define MSJ_ERROR_DIRECCION_INVALIDA      "Dirección de movimiento no válida"
#define MSJ_ERROR_DESCONOCIDO             "Se ha producido un error desconocido"

//mensajes de resultado de acción:
#define MSJ_ESPIA_COLOCADO         "Se ha colocado el espìa"
#define MSJ_TESORO_COLOCADO        "Se movió el tesoro"
#define MSJ_CAPTURA_TESORO         "Has capturado un tesoro!"
#define MSJ_PIERDE_TESORO          "Perdiste un tesoro!"
#define MSJ_COLISION_DE_ESPIAS     "Ambos jugadores pierden un espìa"
#define MSJ_COLISION_DE_TESOROS    "Se encontrò un tesoro del oponente, coloque un espía en la casilla!"

#define OPC_JUGAR '1'
#define OPC_SALIR '2'

typedef enum{ SI = 1,
              NO = 2
}
tOpcion;

class Interfaz{

	public:
	    std::ofstream archJugador1, archJugador2;
		tError setArchivosSalida(char *, char *);
		bool msjBienvenida( );
		void msjError(tError);
		void msjResultado(tResultado);
		void msjSalida();
		void msjTesorosColocados();
		void msjTurno(int);
		void msjGanador(int);
		void msjEmpate();
		void pedirPosicionEspia(unsigned int *, unsigned int *);
		tOpcion preguntarMoverTesoro();
		unsigned int pedirIdTesoro();
		unsigned char pedirDireccion();
		~Interfaz();
};

#endif /* SRC_INTERFAZ_H_ */
