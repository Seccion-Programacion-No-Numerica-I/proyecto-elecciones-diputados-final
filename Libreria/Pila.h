#ifndef LIBRERIA_PILA_H_
#define LIBRERIA_PILA_H_
#include <string>
#include <stdlib.h>
#include <iostream>

class NodoPila {
public:
    string info;
    NodoPila *sig;
    NodoPila(std::string str){
    	info = str;
    	sig = NULL;
    }
};

class Pila{
	private:
	NodoPila* tope;
	public:
		Pila(){
			tope = NULL;
		}
		void insertarPila(std::string str){
			NodoPila* nuevoNodo = new NodoPila(str);
			tope = nuevoNodo;
		}
		std::string obtenerPila(){
			return tope->info;
		}
};




#endif /* LIBRERIA_PILA_H_ */
