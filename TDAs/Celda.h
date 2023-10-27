#include <iostream>
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"


enum EstadoCelda
{
	INACTIVO,
	ACTIVO,
	BLINDADA
};


class Celda
{
private:
	Espia* espia;
	EstadoCelda estado;
	unsigned short turnosInactivosRestantes;
	unsigned short turnosBlindajeRestante;
	Mina* mina;
	unsigned int coordenadaX;
	unsigned int coordenadaY;
	unsigned int coordenadaZ;
public:

	/*
	 * Pre: -
	 * Post: Devuelve la coordenada X de la celda del jugador actual
	 */
	unsigned int getCoordenadaX();


	/*
	 * Pre: -
	 * Post: Devuelve la coordenada Y de la celda del jugador actual
	 */
	unsigned int getCoordenadaY();


	/*
	 * Pre: -
	 * Post: Devuelve la coordenada Z de la celda del jugador actual
	 */
	unsigned int getCoordenadaZ();


	/*
	 * Pre: La celda debe haber sido afectada por un espia, mina o tesoro
	 * Post: Modifica el estado de la celda
	 */
	void setEstado(EstadoCelda nuevoEstado )
	{
		this-> estado = nuevoEstado;
	}


	/*
	 * Pre: -
	 * Post: Devuelve el estado de la celda
	 */
	EstadoCelda getEstado();
	{
		this-> estado;
	}


	/*
	 * Pre: -
	 * Post: Agrega un tesoro en la celda especificada
	 */
	void addTesoro(Tesoro*);


	/*
	 * Pre: -
	 * Post: Devuelve la coordenada X de la celda del jugador actual
	 */
	Lista <Tesoro*> getTesoros();


	/*
	 * Pre: La celda debe encontrarse en EstadoCelda = INACTIVO
	 * Post: Devuelve la cantidad de turnos inactivos restantes de la celda, de otra forma emite error
	 */
	unsigned short getTurnosInactivosRestantes();
	{
		if((this->turnosInactivosRestantes) <1){
			std:: cout << "La celda no cuenta con turnos inactivos restantes" << std::endl;
		} else {
			std:: cout << "La celda cuenta con : "<< (this->turnosInactivosRestantes) <<" turnos inactivos restantes"<<std::endl;
		}
	}


	/*
	 * Pre: -
	 * Post: Asignar una cantidad de turnos inactivos a la celda
	 */
	void setTurnosInactivosRestantes(unsigned short cantidadTurnosInactivos)
	{
		this -> turnosInactivosRestantes = cantidadTurnosInactivos;
	}


	/*
	 * Pre: La celda debe encontrarse en EstadoCelda = BLINDADA
	 * Post: Devuelve la cantidad de turnos de blindaje restantes de la celda, de otra forma emite error
	 */
	unsigned short getTurnosBlindajeRestante()
	{
		if((this->turnosBlindajeRestante) <1){
			throw std:: cout << "La celda no cuenta con turnos de blindaje restantes" << std::endl;
		} else {
			std:: cout << "La celda cuenta con : "<< (this->turnosBlindajeRestante) <<" turnos restantes de blindaje"<<std::endl;

		}
	}


	/*
	 * Pre: -
	 * Post: Asignar una cantidad de turnos de blindaje a la celda
	 */
	void setTurnosBlindajeRestantes(unsigned short cantidadTurnosBlindaje)
	{
		this -> turnosBlindajeRestante = cantidadTurnosBlindaje;
	}


	/*
	 * Pre: -
	 * Post: Devolver el poder de una mina, de otra forma emite error
	 */
	Mina* getMina()
	{
		if(!(this->mina)){
			throw std:cout<<"No se ha colocado una mina en dicha posicion"<<std:endl;
		} else {
			std::cout<<"El poder de la mina es: "<<(this -> mina)<<std::endl;
		}
	}


	/*
	 * Pre: -
	 * Post: Agrega una mina en la celda especificada
	 */
	void setMina(Mina*)
	{
		this -> mina = Mina*;
	}


	/*
	 * Pre: -
	 * Post: Eliminar la celda
	 */
	~Celda();
};
