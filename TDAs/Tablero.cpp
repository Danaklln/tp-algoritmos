#include <iostream>
#include "Lista.h"
#include "Espia.h"
#include "Mina.h"
#include "Tesoro.h"
#include "Celda.h"


using namespace std;


/*
* Un Tablero almacena punteros a celdas de según las dimensiones dadas.
*/
class Tablero {

    private:

        unsigned int dimensionX; 
		unsigned int dimensionY;
		unsigned int dimensionZ;
		Lista<Lista<Lista<Celda*>*>*>* ptrContenido;

    public:

		/*
		* Pre: Dimensiones X Y Z son numeros mayor a cero.
		* Post: Crea un Tablero con las dimensiones dadas.
		*/
        Tablero(unsigned int dimensionX, unsigned int dimensionY, unsigned int dimensionZ){
			Lista<Lista<Lista<Celda*>*>*>*   ptrlistptrlistptrlistdeptrcelda = new Lista<Lista<Lista<Celda*>*>*>;
			for (unsigned int k = 1; k <= dimensionZ ; k++){
				Lista<Lista<Celda*>*>*   ptrlistptrlistdeptrcelda = new Lista<Lista<Celda*>*>;
				for (unsigned int j = 1; j <= dimensionY; j++){
					Lista<Celda*>*  ptrlistdeptrcelda = new Lista<Celda*>;
					for (unsigned int i = 1; i <= dimensionX; i++){
						Celda* ptrcelda = new Celda(i,j,k);
						ptrlistdeptrcelda->agregar(ptrcelda);
					}
					ptrlistptrlistdeptrcelda->agregar(ptrlistdeptrcelda);
				}
				ptrlistptrlistptrlistdeptrcelda->agregar(ptrlistptrlistdeptrcelda);
			}
			this->dimensionX = dimensionX;
			this->dimensionY = dimensionY;
			this->dimensionZ = dimensionZ;
			this->ptrContenido = ptrlistptrlistptrlistdeptrcelda;
		}

		/*
		* Pre: -
		* Post: Devuelve la dimension X del Tablero. 
		*/
		unsigned int getDimensionX(){
			return this->dimensionX;
		}

		/*
		* Pre: -
		* Post: Devuelve la dimension Y del Tablero. 
		*/
		unsigned int getDimensionY(){
			return this->dimensionY;
		}

		/*
		* Pre: -
		* Post: Devuelve la dimension Z del Tablero. 
		*/
		unsigned int getDimensionZ(){
			return this->dimensionZ;
		}

		/*
		* Pre: Las posiciones X Y Z están entre 1 y dimensión X Y Z del Tablero.
		* Post: Devuelve el contenido de la posición indicada del Tablero. 
		*/
		Celda* obtenerPosicion(unsigned int posicionX, unsigned int posicionY, unsigned int posicionZ){
			Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = this->ptrContenido->obtener(posicionZ);
			Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtener(posicionY);
			return ptrlistdeptrcelda->obtener(posicionX);
		}

		/* se usara bitmap esto es solo para probar
		* Pre: -
		* Post: Muestra contenido del Tablero por pantalla. 
		*/
		void mostrarTablero(){
			Lista<Lista<Lista<Celda*>*>*>*   ptrlistptrlistptrlistdeptrcelda = this->ptrContenido;
			ptrlistptrlistptrlistdeptrcelda->iniciarCursor();
			unsigned int k = 1;
			while (ptrlistptrlistptrlistdeptrcelda->avanzarCursor()){
				cout << "TableroXY | Z = " << k << ":" <<endl;
				Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = ptrlistptrlistptrlistdeptrcelda->obtenerCursor();
				ptrlistptrlistdeptrcelda->iniciarCursor();
				while (ptrlistptrlistdeptrcelda->avanzarCursor()){
					Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtenerCursor();
					ptrlistdeptrcelda->iniciarCursor();
					while (ptrlistdeptrcelda->avanzarCursor()){
						cout <<  ptrlistdeptrcelda->obtenerCursor()->getCoordenadaX() << ptrlistdeptrcelda->obtenerCursor()->getCoordenadaY() << " ";
					}
					cout << endl;
				}
				k++;
			}
		} 

		/*
		* Pre: -
		* Post: Libera el contenido de Tablero. 
		*/
        ~Tablero(){
			Lista<Lista<Lista<Celda*>*>*>*   ptrlistptrlistptrlistdeptrcelda = this->ptrContenido;
			for (unsigned int k = 1; k <= ptrlistptrlistptrlistdeptrcelda->contarElementos(); k++){
				Lista<Lista<Celda*>*>* ptrlistptrlistdeptrcelda = ptrlistptrlistptrlistdeptrcelda->obtener(k);
				for (unsigned int j = 1; j <= ptrlistptrlistdeptrcelda->contarElementos(); j++){
					Lista<Celda*>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtener(j);
					for (unsigned int i = 1; i <= ptrlistdeptrcelda->contarElementos(); i++){
						Celda* ptrcelda = ptrlistdeptrcelda->obtener(i);
						delete ptrcelda;
					}
					delete ptrlistdeptrcelda;
				}
				delete ptrlistptrlistdeptrcelda;
			}
			delete ptrlistptrlistptrlistdeptrcelda;
		}
};


int main() {
	unsigned int dimensionX = 4, dimensionY = 3, dimensionZ = 2;
	Tablero* ptrtablerodeprueba = new Tablero(dimensionX, dimensionY, dimensionZ);
	ptrtablerodeprueba->mostrarTablero();
	cout << ptrtablerodeprueba->obtenerPosicion(4,2,1)->getEstado() << endl;
	ptrtablerodeprueba->obtenerPosicion(4,2,1)->setEstado(INACTIVO);
	cout << ptrtablerodeprueba->obtenerPosicion(4,2,1)->getEstado() << endl;
	ptrtablerodeprueba->mostrarTablero();
	delete ptrtablerodeprueba;
	return 0;
}