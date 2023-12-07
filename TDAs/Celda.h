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
  unsigned int turnosInactivosRestantes;
  Mina* ptrMina;
  Espia* ptrEspia;
  Lista<Tesoro*>* ptrlistptrtesoro;
  Jugador* ptrJugadorActual;
  unsigned int coordenadaX;
  unsigned int coordenadaY;
  unsigned int coordenadaZ;

public:

  /*
    * Pre: Coordenadas X Y Z son numeros mayor a cero.
    * Post: Inicializa una celda con valores default y el jugador actual.
  */
  Celda(Jugador* ptrJugadorActual, unsigned int coordenadaX, unsigned int coordenadaY, unsigned int coordenadaZ){
    this->estado = CELDA_ACTIVA;
    this->turnosInactivosRestantes = 0;
    this->ptrMina = NULL;
    this->ptrEspia = NULL;
    this->ptrlistptrtesoro = new Lista<Tesoro*>;
    this->ptrJugadorActual = ptrJugadorActual;
    this->coordenadaX = coordenadaX;
    this->coordenadaY = coordenadaY;
    this->coordenadaZ = coordenadaZ;
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
    * Post: Devuelve turnosInactivosRestantes de la celda.
  */
  unsigned int getTurnosInactivosRestantes(){
    return this->turnosInactivosRestantes;
  }

  /*
    * Pre: -
    * Post: Devuelve puntero a la unica mina de la celda.
  */
  Mina* obtenerMina(){
    return this->ptrMina;
  }

  /*
    * Pre: Recibe un puntero a un jugador.
    * Post: Devuelve true si tiene mina en esta celda.
  */
  bool tieneMina(Jugador* ptrJugador){
    if (this->ptrMina == NULL){
      return false;
    }
    return (this->ptrMina->getPropietario() == ptrJugador);
  }

  /*
         *  Pre: -
         *  Post: Devuelve un booleano indicando si hay una mina en la
         *  casilla
         */
  bool hayMinaEnLaCasilla()
  {
    return !(!this->ptrMina);
  }

  /*
    * Pre: Recibe un puntero a un jugador.
    * Post: Devuelve true si hay mina contraria en esta celda.
  */
  bool tieneMinaContraria(Jugador* ptrJugador){
    if (this->ptrMina == NULL){
      return false;
    }
    return (this->ptrMina->getPropietario() != ptrJugador);
  }

  /*
    * Pre: Recibe un puntero a un jugador.
    * Post: Acciona mina contraria si jugador la descubrió.
  */
  void descubrioMina(Jugador* ptrJugador){
    if (this->tieneMinaContraria(ptrJugador)){
      cout << "descubriste una mina!" << endl;
      ptrJugador->perderTurno();
      this->accionarMina();
    }
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
         * Post: Devuelve un booleano indicando si hay un
         * espia en la casilla.
         */
  bool hayEspiaEnLaCasilla()
  {
    return !(!this->ptrEspia);
  }

  /*
    * Pre: Recibe un puntero a un jugador.
    * Post: Devuelve true si el espia pertenece al jugador
        * indicado en el parámetro.
  */
  bool tieneEspia(Jugador* ptrJugador){
    if (this->ptrEspia == NULL){
      return false;
    }
    return (this->ptrEspia->getPropietario() == ptrJugador);
  }

  /*
    * Pre: Recibe un puntero a un jugador.
    * Post: Devuelve true si hay espia contrario en esta celda.
  */
  bool tieneEspiaContrario(Jugador* ptrJugador){
    if (this->ptrEspia == NULL){
      return false;
    }
    return (this->ptrEspia->getPropietario() != ptrJugador);
  }

  /*
    * Pre: -
    * Post: Devuelve puntero a lista de punteros a tesoro.
  */
  Lista<Tesoro*>* obtenerTesoros(){
    return this->ptrlistptrtesoro;
  }

  /*
    * Pre: Recibe puntero a jugador y numero indicadorDeUso (0 de jugador o 1 contrario).
    * Post: Devuelve puntero al 1er tesoro pedido si no devuelve NULL.
  */
  Tesoro* obtenerTesoro(Jugador* ptrJugador, unsigned int indicadorDeUso){
    if (ptrlistptrtesoro->estaVacia()){
      return NULL;
    }
    Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
    ptrlistptrtesoro->iniciarCursor();
    while (ptrlistptrtesoro->avanzarCursor()){
      if ((ptrlistptrtesoro->obtenerCursor()->getPropietario() == ptrJugador) && (indicadorDeUso == 0)){
        return ptrlistptrtesoro->obtenerCursor();
      }
      if ((ptrlistptrtesoro->obtenerCursor()->getPropietario() != ptrJugador) && (indicadorDeUso == 1)){
        return ptrlistptrtesoro->obtenerCursor();
      }
    }
    return NULL;
  }

  /*
    * Pre: Recibe puntero a jugador.
    * Post: Devuelve puntero al 1er tesoro de jugador recibido si no devuelve NULL.
  */
  Tesoro* obtenerTesoroDeJugador(Jugador* ptrJugador){
    return obtenerTesoro(ptrJugador, 0);
  }

  /*
    * Pre: Recibe puntero a jugador.
    * Post: Devuelve puntero al 1er tesoro de jugador distinto al recibido si no devuelve NULL.
  */
  Tesoro* obtenerTesoroContrario(Jugador* ptrJugador){
    return obtenerTesoro(ptrJugador, 1);
  }

  void aplicarRadar(Jugador* ptrJugador){
	  Tesoro * tesoro = obtenerTesoro(ptrJugador, 1);
	  if (tesoro){
		  tesoro->setVisibilidad(TESORO_REVELADO);
		  tesoro->setRevelador(ptrJugador);

	  }
  }

  /*
    * Pre: Recibe un puntero a un jugador.
    * Post: Devuelve true si hay algun objeto contrario en esta celda.
  */
  bool tieneObjetoContrario(Jugador* ptrJugador){
    if (this->tieneMinaContraria(ptrJugador) || this->tieneEspiaContrario(ptrJugador) || this->obtenerTesoroContrario(ptrJugador) != NULL){
      return true;
    }
    return false;
  }

  /*
         * Pre: Se debe proporcionar un puntero a Jugador valido
         * Post: Devuelve un booleano indicando si hay un tesoro en
         * la casilla que no pertenezca al jugador indicado
         */
  bool tieneTesoroRival(Jugador* jugador)
  {
    Lista<Tesoro*>* tesorosEnCasilla = this->ptrlistptrtesoro;
    tesorosEnCasilla->iniciarCursor();

    while(tesorosEnCasilla->avanzarCursor())
    {
      Tesoro* tesoroActual = tesorosEnCasilla->obtenerCursor();
      if (tesoroActual->getPropietario() != jugador)
      {
        return true;
      }
    }

    return false;
  }

  /*
         * Pre: Se debe proporcionar un puntero a Jugador valido
         * Post: Devuelve un booleano indicando si hay un tesoro en
         * la casilla que no pertenezca al jugador indicado
         */
  bool tieneTesoroRivalRevelado(Jugador* jugador)
  {
    Lista<Tesoro*>* tesorosEnCasilla = this->ptrlistptrtesoro;
    tesorosEnCasilla->iniciarCursor();

    while(tesorosEnCasilla->avanzarCursor())
    {
      Tesoro* tesoroActual = tesorosEnCasilla->obtenerCursor();
      if (tesoroActual->getPropietario() != jugador && tesoroActual->getVisibilidad() == TESORO_REVELADO &&
      tesoroActual->getRevelador() != jugador)
      {
        return true;
      }
    }

    return false;

  }

  /*
         * Pre: Se debe proporcionar un punteor a Jugador valido
         * Post: Devuelve un booleano indicando si el jugador indicado
         * posee un tesoro en la casilla.
         */
  bool tieneTesoro(Jugador* jugador)
  {
    Lista<Tesoro*>* tesorosEnCasilla = this->ptrlistptrtesoro;
    tesorosEnCasilla->iniciarCursor();

    while(tesorosEnCasilla->avanzarCursor())
    {
      Tesoro* tesoroActual = tesorosEnCasilla->obtenerCursor();
      if (tesoroActual->getPropietario() == jugador)
      {
        return true;
      }
    }

    return false;
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
    this->estado = CELDA_INACTIVA;
    this->turnosInactivosRestantes = cantidadTurnosInactivos;
  }

  /*
    * Pre: -
    * Post: Reactiva celda si la cantidad de turnos inactivos es 0.
  */
  void reactivarCelda(){
    if ((this->estado == CELDA_INACTIVA) && (this->turnosInactivosRestantes == 0)){
      this->estado = CELDA_ACTIVA;
    }
  }

  /*
    * Pre: recibe puntero a mina.
    * Post: agrega esa misma.
  */
  void addMina(Mina* nuevoPtrMina){
    if (this->ptrMina == NULL){
      this->ptrMina = nuevoPtrMina;
    }
    else if (this->tieneMina(nuevoPtrMina->getPropietario())){
      this->eliminarMina();
      this->ptrMina = nuevoPtrMina;
    }
    else{
      delete nuevoPtrMina;
      this->accionarMina();
    }
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
    * Post: Acciona el comportamiento de mina.
  */
  void accionarMina(){
    if (this->ptrMina != NULL){
      if (this->tieneObjetoContrario(this->ptrMina->getPropietario())){
        this->inactivarCelda(this->ptrMina->getPoder());
        this->eliminarMina();
        this->eliminarEspia();
        this->eliminarTodosTesoros();
        cout << "Mina exploto!" << endl;
      }
    }
  }

  /*
    * Pre: recibe puntero a espia.
    * Post: Lo agrega si no hay o ya tiene eliminando anterior y si hay contrario elimina ambos
  */
  void addEspia(Espia* nuevoPtrEspia){
    Jugador* ptrPropietario =  nuevoPtrEspia->getPropietario();
    if (this->ptrEspia == NULL){
      this->ptrEspia = nuevoPtrEspia;
    }
    else if(this->tieneEspia(ptrPropietario)){
      this->eliminarEspia();
      this->ptrEspia = nuevoPtrEspia;
    }
    else{
      this->eliminarEspia();
      delete nuevoPtrEspia;
    }
    this->descubrioMina(ptrPropietario);
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
    * Post: Acciona el comportamiento de espia.
  */
  void accionarEspia(){
    if (this->ptrEspia != NULL){
      Jugador* ptrPropietarioEspia = this->ptrEspia->getPropietario();
      Tesoro* ptrTesoroContrario = this->obtenerTesoroContrario(ptrPropietarioEspia);
      if (ptrTesoroContrario != NULL){
        if (ptrTesoroContrario->getEstadoTesoro() == TESORO_NO_BLINDADO){
          this->inactivarCelda(4);
          eliminarTesoro(ptrTesoroContrario);
        }
      }
    }
  }

  /*
    * Pre: recibe puntero a tesoro.
    * Post: agrega ese mismo de la lista.
  */
  void addTesoro(Tesoro* nuevoPtrTesoro){
    if (obtenerTesoroContrario(nuevoPtrTesoro->getPropietario()) != NULL){
      cout<< "Tesoro enemigo en celda:" << this->coordenadaX <<"-"<< this->coordenadaY <<"-"<<this->coordenadaZ <<endl;
    }
    this->ptrlistptrtesoro->agregar(nuevoPtrTesoro);
    this->descubrioMina(nuevoPtrTesoro->getPropietario());
  }

  /*
    * Pre: recibe puntero a tesoro y este esta en lista.
    * Post: saca ese mismo de la lista y lo devuelve.
  */
  Tesoro* sacarTesoro(Tesoro* ptrTesoroASacar){
    Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
    unsigned int i = 1;
    ptrlistptrtesoro->iniciarCursor();
    while (ptrlistptrtesoro->avanzarCursor()){
      Tesoro* ptrTesoro = ptrlistptrtesoro->obtenerCursor();
      if (ptrTesoro == ptrTesoroASacar){
        ptrlistptrtesoro->remover(i);
        return ptrTesoro;
      }
      i++;
    }
    return NULL;
  }

  /*
    * Pre: -
    * Post: Libera punteros a tesoros y vacía la lista.
  */
  void eliminarTodosTesoros(){
    Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
    while(ptrlistptrtesoro->contarElementos()>0){
      delete ptrlistptrtesoro->obtener(1);
      ptrlistptrtesoro->remover(1);
    }
  }

  /*
    * Pre: recibe puntero a tesoro.
    * Post: saca y elimina ese mismo de la lista.
  */
  void eliminarTesoro(Tesoro* ptrTesoro){
    this->sacarTesoro(ptrTesoro);
    delete ptrTesoro;
  }

  /*
    * Pre: -
    * Post: Pasa los turnos de blindaje a todos los tesoros.
  */
  void pasarTurnosDeTesoros(){
    Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
    if (!ptrlistptrtesoro->estaVacia()){
      ptrlistptrtesoro->iniciarCursor();
      while (ptrlistptrtesoro->avanzarCursor()){
        ptrlistptrtesoro->obtenerCursor()->pasarTurnoBlindado();
      }
    }
  }

  /*
    * Pre: Recibe un puntero a jugador y un numero positivo.
    * Post: Blinda todos los tesoros de ese jugador en la celda segun el numero dado.
  */
  void blindarTesoros(Jugador* ptrJugador, unsigned int cantidadTurnosBlindaje){
    Lista<Tesoro*>* ptrlistptrtesoro = this->ptrlistptrtesoro;
    if (!ptrlistptrtesoro->estaVacia()){
      ptrlistptrtesoro->iniciarCursor();
      while (ptrlistptrtesoro->avanzarCursor()){
        if (ptrlistptrtesoro->obtenerCursor()->getPropietario() == ptrJugador){
          ptrlistptrtesoro->obtenerCursor()->blindarTesoro(cantidadTurnosBlindaje);
        }
      }
    }
  }

  /*
    * Pre: Recibe un puntero a un jugador.
    * Post: Pasa el turno a la celda y al nuevo jugador.
  */
  void pasarTurnoCelda(Jugador* ptrNuevoJugadorActual){
    if (this->turnosInactivosRestantes > 0){
      this->turnosInactivosRestantes--;
    }
    this->accionarMina();
    this->accionarEspia();
    this->reactivarCelda();
    this->pasarTurnosDeTesoros();
    this->ptrJugadorActual = ptrNuevoJugadorActual;
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
      Tesoro* ptrTesoro = this->obtenerTesoroDeJugador(ptrJugadorActual);
      if (ptrTesoro != NULL){
        texto[0] = 'T';
        if (ptrTesoro->getEstadoTesoro() == TESORO_BLINDADO){
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
