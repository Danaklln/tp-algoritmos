#ifndef MANOINDIVIDUAL_H_
#define MANOINDIVIDUAL_H_
#include "Carta.h"
#include <iostream>
#include "Lista.h"

class ManoIndividual{

private:
    Lista<Carta*>* cartasGuardadas;
    Carta * cartaSacada;


public:

    /**
     * pre: -
     * post: crea el mazo.
    */
    ManoIndividual(){
        this->cartasGuardadas = new Lista<Carta*>();
        this->cartaSacada = 0;
    }

    /**
     * pre: -
     * post: elimina los elementos.
    */
    virtual ~ManoIndividual(){
        delete this->cartasGuardadas;
    }

    /**
     * pre: -
     * post: saca una carta.
    */
    void sacarCarta(){
        this->cartaSacada = new Carta();
    }

    /**
     * pre: -
     * post: guarda la carta en cartasGuardadas.
    */
    void guardarCarta(){
        this->cartasGuardadas->agregar(this->cartaSacada);
    }



    /**
     * pre: -
     * post: devuelve si la carta esta en el mazo individual.
    */
    bool verificarCartaEnMazo(Carta * carta){
        this->cartasGuardadas->iniciarCursor();
        while(this->cartasGuardadas->avanzarCursor()){
            if(carta == this->cartasGuardadas->obtenerCursor()){
                return true;
            }
        }
        return false;
    }

    /**
    * pre: tipo de cartas debe existir
    * post: devuelve si la carta con ese tipo está en el mazo
    */
    bool verificarCartaEnMazo(TipoDeCarta tipo){
        this->cartasGuardadas->iniciarCursor();
        while(this->cartasGuardadas->avanzarCursor()){
             if(tipo == this->cartasGuardadas->obtenerCursor()->getTipoDeCarta()){
                return true;
           }
       }
       return false;
    }

    /**
     * pre: -
     * post: devuelve si la carta esta en el mazo individual.
    */
    void printCartasGuardadas(){
        std::string nombresCartas[6]={"Blindaje","Radar","Partir Tesoro","Romper Blindaje","Triple Espia","Triple Mina"};
        std::cout<<"Las cartas que guardaste son: "<<std::endl;
        this->cartasGuardadas->iniciarCursor();
        while(this->cartasGuardadas->avanzarCursor()){
            std::cout<< nombresCartas[cartasGuardadas->obtenerCursor()->getTipoDeCarta()]<<std::endl;
        }
    }

    /**
     * pre: Se debe haber sacado al menos una carta antes.
    * post: muestra por consola la ultima carta sacada.
    */
    void printCartaSacada(){
    	std::string nombresCartas[6]={"Blindaje","Radar","Partir Tesoro","Romper Blindaje","Triple Espia","Triple Mina"};
    	std::cout << "La carta sacada es: " << nombresCartas[this->cartaSacada->getTipoDeCarta()] << std::endl;
    }

    /**
    * pre: -
    * post: verifica que la carta no sea nula
    */
    void verificarCarta(Carta * carta){
        if(carta == NULL){
            throw "la carta no puede ser Nula";
        }
    }

    /**
    * pre: el numero debe ser mayor o igual a 0 y menor o igual a 5
    * post: devuelve la carta 
    */
    Carta * getCarta(unsigned int numero){
        if(numero < 0 && numero > 5){
            throw "el numero no puede ser mayor a 5";
        }
        this->cartasGuardadas->iniciarCursor();
        while(this->cartasGuardadas->avanzarCursor()){
            if(this->cartasGuardadas->obtenerCursor()->getTipoDeCarta() == numero){
                return cartasGuardadas->obtenerCursor();
            }
        }
        return 0;
    }

    /**
    * pre: -
    * post: devuelve la carta sacada
    */
    Carta * getCartaSacada(){
        return this->cartaSacada;
    }

};
#endif
