#include <iostream>
#include "Lista.h"

using namespace std;

/*
* Un Tablero almacena punteros a celdas de según las dimensiones dadas.
*/
class Tablero {

    private:

        unsigned int dimensionX; 
		unsigned int dimensionY;
		unsigned int dimensionZ;
		Lista<Lista<Lista<int>*>*>* ptrContenido;

    public:

		/*
		* Pre: Dimensiones X Y Z son numeros mayor a cero.
		* Post: Crea un Tablero con las dimensiones dadas.
		*/
        Tablero(unsigned int dimensionX, unsigned int dimensionY, unsigned int dimensionZ){
			Lista<Lista<Lista<int>*>*>*   ptrlistptrlistptrlistdeptrcelda = new Lista<Lista<Lista<int>*>*>;
			for (unsigned int k = 1; k <= dimensionZ ; k++){
				Lista<Lista<int>*>*   ptrlistptrlistdeptrcelda = new Lista<Lista<int>*>;
				for (unsigned int j = 1; j <= dimensionY; j++){
					Lista<int>*  ptrlistdeptrcelda = new Lista<int>;
					for (unsigned int i = 1; i <= dimensionX; i++){
						ptrlistdeptrcelda->agregar(i+j+k);
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
		unsigned int obtenerPosicion(unsigned int posicionX, unsigned int posicionY, unsigned int posicionZ){
			Lista<Lista<int>*>* ptrlistptrlistdeptrcelda = this->ptrContenido->obtener(posicionZ);
			Lista<int>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtener(posicionY);
			return ptrlistdeptrcelda->obtener(posicionX);
		}

		/*
		* Pre: -
		* Post: Muestra contenido del Tablero por pantalla. 
		*/
		void mostrarTablero(){
			Lista<Lista<Lista<int>*>*>*   ptrlistptrlistptrlistdeptrcelda = this->ptrContenido;
			ptrlistptrlistptrlistdeptrcelda->iniciarCursor();
			unsigned int k = 1;
			while (ptrlistptrlistptrlistdeptrcelda->avanzarCursor()){
				cout << "TableroXY | Z = " << k << ":" <<endl;
				Lista<Lista<int>*>* ptrlistptrlistdeptrcelda = ptrlistptrlistptrlistdeptrcelda->obtenerCursor();
				ptrlistptrlistdeptrcelda->iniciarCursor();
				while (ptrlistptrlistdeptrcelda->avanzarCursor()){
					Lista<int>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtenerCursor();
					ptrlistdeptrcelda->iniciarCursor();
					while (ptrlistdeptrcelda->avanzarCursor()){
						cout <<  ptrlistdeptrcelda->obtenerCursor() << " ";
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
			Lista<Lista<Lista<int>*>*>*   ptrlistptrlistptrlistdeptrcelda = this->ptrContenido;
			for (unsigned int k = 1; k <= ptrlistptrlistptrlistdeptrcelda->contarElementos(); k++){
				Lista<Lista<int>*>* ptrlistptrlistdeptrcelda = ptrlistptrlistptrlistdeptrcelda->obtener(k);
				for (unsigned int j = 1; j <= ptrlistptrlistdeptrcelda->contarElementos(); j++){
					Lista<int>* ptrlistdeptrcelda = ptrlistptrlistdeptrcelda->obtener(j);
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
	cout << ptrtablerodeprueba->obtenerPosicion(4,2,1); 
	delete ptrtablerodeprueba;
	return 0;
}
