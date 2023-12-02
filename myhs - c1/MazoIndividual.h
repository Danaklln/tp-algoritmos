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
    MazoIndividual(){
        this->cartasGuardadas = new Lista<Carta*>();
    }

    /**
     * pre: -
     * post: elimina los elementos.
    */
    virtual ~MazoIndividual(){
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
     * pre: carta no puede ser NULL y debe estar en cartasGuardadas.
     * post: juega la carta.
    */
    void jugarCartaGuardada(Carta * carta){
        verificarCarta(carta);
        if(!this->verificarCartaEnMazo(carta)){
            throw "esa carta no esta en el mazo individual";
        }
        this->jugarCarta(carta);
        this->removerCarta(carta);
    }

    /**
     * pre: -
     * post: juega la carta recien sacada.
    */
    void jugarCartaSacada(){
        this->jugarCarta(this->cartaSacada);
    }

    /**
     * pre: carta no puede ser NULL
     * post: juega la carta dependiendo el tipo.
    */
    void jugarCarta(Carta * carta){
        verificarCarta(carta);
        switch (carta->getTipoDeCarta()){
            case 0 :
                cartaBlindaje();
                break;

            case 1 :
                cartaRadar();
                break;

            case 2:
                cartaPartirTesoro();
                break;

            case 3:
                cartaRomperBlindaje();
                break;

            case 4:
                cartaTesoroEnPeligro();
                break;

            case 5:
                cartaTripleMina();
                break;
        }
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
    
    void removerCarta(Carta * carta){
        verificarCarta(carta);
        int contador = 0;
        bool eliminada = false;
        this->cartasGuardadas->iniciarCursor();
        while(this->cartasGuardadas->avanzarCursor() && eliminada == false){
            if(this->cartasGuardadas->obtenerCursor() == carta){
                this->cartasGuardadas->remover(contador);
                eliminada = true;
            }
            contador++;
        }
    }

    void verificarCarta(Carta * carta){
        if(carta == NULL){
            throw "la carta no puede ser Nula";
        }
    }
    

};

#endif
