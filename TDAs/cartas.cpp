#include <iostream>
#include<stdlib.h>
#include<time.h>

struct TipoCarta{
    int blindaje = 1;
    int radar = 2;           //no es necesario el struct
    int partirTesoro = 3;
    int romperBlindaje = 4;
    int tesoroEnPeligro = 5;
    int tripleMina = 6;

};

void insertarCarta(int cartaSeleccionada){
    switch (cartaSeleccionada){
        case 1 :
        cartaBlindaje();
        break;

        case 2 :
        cartaRadar();
        break;

        case 3:
        cartaPartirTesoro();
        break;

        case 4:
        cartaRomperBlindaje();
        break;

        case 5:
        cartaTesoroEnPeligro();
        break;

        case 6:
        cartaTripleMina();
        break;
    }
}

int sacarCarta(){
    int cartaSeleccionada;
    int limiteInferior = 1;  //luego de sacar hay que agregarla a cantidadCartasSacadas y cartasEnMano
    int limiteSuperior = 6;                                       
    srand(time(NULL));
    cartaSeleccionada = limiteInferior + rand()%(limiteSuperior +1 - limiteInferior);
    return cartaSeleccionada;

}

void cartaBlindaje(){  //pregunta en que tesoro quiere poner blindaje(da las opciones)
                       //lo ubica en el tablero
                       //se agrega a setTurnosBlindajeRestantes

}

void cartaRadar(){     //Pide una posición para colocarlo, verifica que no haya tesoro propio
                       //revisa si hay algún tesoro enemigo en el cubo 3x3 que se forma a su alrededor
}                      //si hay, da el veredicto de que hay un tesoro cerca(para no complicar)

void cartaPartirTesoro(){ //deja otro tesoro en alguna casilla de su alrededor, verificando
                          //que no haya uno propio o que se escape de los límites
}

void cartaRomperBlindaje(){ //da las opciones de jugador que tiene algun blindaje
                            //reduce la cantidad de turnos de casilla blindada a 0 del oponente elegido
}                           //(si tiene más de una casilla blindada, se lo aplica a la primera que encuentre)

void cartaTesoroEnPeligro(){//la cambiaría por "pierdeElJuego" para esta entrega

}

void cartaTripleMina(){ //concede el poder de poner tres minas juntas
    int x,y,z;          //pide 'x','y','z' y pone las otras dos minas en el 'z' anterior(z--) y siguiente(z++)
    std::cout<<'ingrese las coordenas donde quiere poner las minas:\nX-';
    std::cin>>x;        //no me fijo si hay tesoros propios, queda al criterio del jugador volarlos
    std::cout<<'\nY-';
    std::cin>>y;
    std::cout<<'\nZ-';
    std::cin>>z;
    
}


/* En el juego si elige sacar carta se emplea la función sacarCarta que devuelve un número random
del 1 al 6, representando las cartas(1.blindaje, 2.radar, 3.partirTesoro, 4.romperBlindaje,
5.tesoroEnPeligro y 6.tripleMina).
  Si el jugador decide usarla en ese mismo turno, se utiliza la funcion insertarCarta, la cual toma
el numero de la carta seleccionada y cumple la funcion correspondiente segun la carta que represente.
  Si el jugador decide guardarla, se almacena en la lista <Carta*>*


En este método simplemente pondría " cantidadCartasSacadas ++ "
    void setCantidadCartasSacadas(unsigned short nuevaCantidad)
    {
        this->cantidadCartasSacadas = nuevaCantidad;
    }

Crear para la clase jugador un setCartasEnMano para agregar las cartas nuevas a la lista