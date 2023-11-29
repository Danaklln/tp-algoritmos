#include "./TDAs/TesoroBinario.h"
#include "./TDAs/Interfaz.h"

int main(){
    
    unsigned int cantidadJugadores;
    unsigned int x,y,z;
    TesoroBinario * juego;
    Interfaz * interfaz;
    bool salir;

    interfaz = new Interfaz;

    cantidadJugadores = interfaz->pedirCantidadJugadores();
    interfaz->pedirDimensiones(&x,&y,&z);
    juego = new TesoroBinario(cantidadJugadores,x,y,z,interfaz);
    
    salir = juego->iniciarJuego();
    if(salir){
        interfaz->msjSalida();
    }

    delete juego;
    delete interfaz;

    return 0;
}

