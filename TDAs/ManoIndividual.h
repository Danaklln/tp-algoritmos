#ifndef MAZOINDIVIDUAL_H_
#define MAZOINDIVIDUAL_H_
#include "Carta.h"
#include <iostream>
#include "Lista.h"

class MazoIndividual{

private:
    Lista<Carta*>* cartasGuardadas;
    Carta * cartaSacada;


public:
    
    /**
     * pre: -
     * post: crea el mazo.
    */
    ManoDelJugador(){
        this->cartasGuardadas = new Lista<Carta*>();
    }

    /**
     * pre: -
     * post: elimina los elementos.
    */
    virtual ~ManoDelJugador(){
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
     * pre: -
     * post: devuelve si la carta esta en el mazo individual.
    */
    void getCartasGuardadas(){
        std::string nombresCartas[6]={"Blindaje","Radar","Partir Tesoro","Romper Blindaje","Tesoro en Peligro","Triple Mina"};
        std::cout<<"Las cartas que guardaste son: "<<std::endl;
        this->cartasGuardadas->iniciarCursor();
        while(this->cartasGuardadas->avanzarCursor()){
            std::cout<< nombresCartas[cartasGuardadas->obtenerCursor()->getTipoDeCarta()]<<std::endl;   
        }
    }


    void verificarCarta(Carta * carta){
        if(carta == NULL){
            throw "la carta no puede ser Nula";
        }
    }

};
#endif