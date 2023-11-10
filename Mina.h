#ifndef MINA_H_
#define MINA_H_

class Mina
{
private:
    unsigned short poder;

public:

    /*
	 * Pre: -
	 * Post: Inicializa Mina indicando el poder de la misma
	 */
    Mina(unsigned short poderMina)
    {
        this -> poder = poderMina;
    }

    /*
	 * Pre: -
	 * Post: Devuelve el poder de la Mina especificada
	 */
    getPoder()
    {
        return this -> poder;
    }

    /*
	 * Pre: -
	 * Post: Elimina Mina
	 */
    ~Mina();
};


#endif MINA_H_