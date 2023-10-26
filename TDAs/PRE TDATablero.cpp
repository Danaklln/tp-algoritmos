#include <iostream>
#include "Lista.h"

using namespace std;


class Tablero {

    private:

        unsigned int dimensionX; 
		unsigned int dimensionY;
		unsigned int dimensionZ;
		Lista<Lista<Lista<int>*>*>* ptrContenido;

    public:

        Tablero(unsigned int dimensionX, unsigned int dimensionY, unsigned int dimensionZ){
			Lista<Lista<Lista<int>*>*>*   ptrlistptrlistptrlistdeint = new Lista<Lista<Lista<int>*>*>;
			for (unsigned int k = 1; k <= dimensionZ ; k++){
				Lista<Lista<int>*>*   ptrlistptrlistdeint = new Lista<Lista<int>*>;
				for (unsigned int j = 1; j <= dimensionY; j++){
					Lista<int>*  ptrlistdeint = new Lista<int>;
					for (unsigned int i = 1; i <= dimensionX; i++){
						ptrlistdeint->agregar(i+j+k);
					}
					ptrlistptrlistdeint->agregar(ptrlistdeint);
				}
				ptrlistptrlistptrlistdeint->agregar(ptrlistptrlistdeint);
			}
		this->dimensionX = dimensionX;
		this->dimensionY = dimensionY;
		this->dimensionZ = dimensionZ;
		this->ptrContenido = ptrlistptrlistptrlistdeint;
		}

		void mostrarTablero(){
			Lista<Lista<Lista<int>*>*>*   ptrlistptrlistptrlistdeint = this->ptrContenido;
			for (unsigned int k = 1; k <= ptrlistptrlistptrlistdeint->contarElementos(); k++){
				cout << "TableroXY | Z = " << k << ":" <<endl;
				Lista<Lista<int>*>* ptrlistptrlistdeint = ptrlistptrlistptrlistdeint->obtener(k);
				for (unsigned int j = 1; j <= ptrlistptrlistdeint->contarElementos(); j++){
					Lista<int>* ptrlistdeint = ptrlistptrlistdeint->obtener(j);
					for (unsigned int i = 1; i <= ptrlistdeint->contarElementos(); i++){
						cout <<  ptrlistdeint->obtener(i) << " ";
					}
					cout <<  endl;
				}
			}
		} 

        ~Tablero(){
			Lista<Lista<Lista<int>*>*>*   ptrlistptrlistptrlistdeint = this->ptrContenido;
			for (unsigned int k = 1; k <= ptrlistptrlistptrlistdeint->contarElementos(); k++){
				Lista<Lista<int>*>* ptrlistptrlistdeint = ptrlistptrlistptrlistdeint->obtener(k);
				for (unsigned int j = 1; j <= ptrlistptrlistdeint->contarElementos(); j++){
					Lista<int>* ptrlistdeint = ptrlistptrlistdeint->obtener(j);
					delete ptrlistdeint;
				}
				delete ptrlistptrlistdeint;
			}
			delete ptrlistptrlistptrlistdeint;
		}
};


int main() {
	unsigned int dimensionX = 2, dimensionY = 2, dimensionZ = 3;
	Tablero* ptrtablerodeprueba = new Tablero(dimensionX, dimensionY, dimensionZ);
	ptrtablerodeprueba->mostrarTablero();
	delete ptrtablerodeprueba;
	//Tablero tablerodeprueba(dimensionX, dimensionY, dimensionZ); //OBJETO NO ESTA EN HEAP
	//tablerodeprueba.mostrarTablero();
	return 0;
}
