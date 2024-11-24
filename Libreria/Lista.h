#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <string>

using namespace std;

template <class Tipo>
class Lista;

template <class Tipo>
class nodo {
    Tipo info;
    nodo<Tipo>* prox;
    friend class Lista<Tipo>; // La clase Lista puede acceder a sus atributos privados
};

template <class Tipo>
class nodoPrioridad {
    Tipo info;
    int prioridad;
    nodoPrioridad<Tipo>* prox;
    friend class Lista<Tipo>; // La clase Lista puede acceder a sus atributos privados
};

template <class Tipo>
class Lista {
    typedef nodo<Tipo>* Apuntador;
    typedef nodoPrioridad<Tipo>* ApuntadorPrioridad;
private:
    nodo<Tipo>* Primero, *Final;
    nodoPrioridad<Tipo>* PrimeroPrioridad, *FinalPrioridad;
public:
    Lista();
    //Lista(const Lista &that);
    nodo<Tipo>* ObtPrimero();
    void AsigPrimero(nodo<Tipo>* p);
    bool Vacia();
    bool Llena();
    bool InsComienzo(Tipo Valor);
    bool EliComienzo(Tipo &Valor);
    bool InsDespues(Apuntador p, Tipo Valor);
    bool EliDespues(Apuntador p, Tipo &Valor);
    ~Lista();
    Lista& operator=(const Lista &that);
    nodo<Tipo>* ObtProx(Apuntador p);
    void AsigProx(Apuntador p, Apuntador q);
    Tipo ObtInfo(Apuntador p);
    void AsigInfo(Apuntador p, Tipo Valor);
    int Contar();
    int ContarNodosPrioridad();
    nodo<Tipo>* Buscar(Tipo Valor);
    void pasarListaAux(Lista<Tipo> &listaFuente, Lista<Tipo> &listaDestino);
    bool InsFinal(Tipo Valor);



    nodo<Tipo>* ObtFinal();

    // metodos de cola prioridad
    bool VaciaPrioridad();

    bool LlenaPrioridad();

    Tipo ObtInfoPrioridad(ApuntadorPrioridad p);

    int ObtPrioridad(ApuntadorPrioridad p);
    nodoPrioridad<Tipo> *ObtPrimeroPrioridad();
    nodoPrioridad<Tipo> *ObtProxPrioridad(ApuntadorPrioridad p);
    bool InsertarNodoColaPrioridad(Tipo Valor, int p);
    bool RemoverNodoColaPrioridad(Tipo &Valor, int &p);

    // Métodos Colas
    bool InsertarNodoCola(Tipo Valor);
    bool RemoverNodoCola(Tipo &Valor);
};

#endif // LISTA_H
