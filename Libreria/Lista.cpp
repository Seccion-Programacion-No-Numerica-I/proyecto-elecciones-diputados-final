#include "Lista.h"
#include "../Candidato.h" // Include the header file where Candidato is defined
#include "../Elector.h"

template <class Tipo>
nodo<Tipo>* Lista<Tipo>::ObtPrimero() {
    return Primero;
};

template <class Tipo>
void Lista<Tipo>::AsigPrimero(nodo<Tipo>* p) {
    Primero = p;
};

template <class Tipo>
Lista<Tipo>::Lista(){
    Primero = NULL;
    Final = NULL; // Asegurarse de inicializar Final

    PrimeroPrioridad = NULL;
    FinalPrioridad = NULL;
} ;

template <class Tipo>
Lista<Tipo>& Lista<Tipo>::operator= (const Lista<Tipo> &that) {
    if (this != &that) {
        Apuntador p;
        Apuntador thatP;

        while (!Vacia()) {
            p = Primero->prox;
            delete Primero;
            Primero = p;
        }

        if (that.Primero != NULL) {
            thatP = that.Primero;
            InsComienzo(thatP->info);
            thatP = thatP->prox;
            p = ObtPrimero();
            while (thatP != NULL) {
                Apuntador nuevo;
                if (!Llena()) {
                    nuevo = new nodo<Tipo>;
                    nuevo->info = thatP->info;
                    nuevo->prox = p->prox;
                    p->prox = nuevo;
                    p = p->prox;
                }
                thatP = thatP->prox;
            }
        }
    }
    return *this;
};

template <class Tipo>
bool Lista<Tipo>::Vacia() {
    return Primero == NULL;
};

template <class Tipo>
bool Lista<Tipo>::Llena() {
    nodo<Tipo> *p;
    p = new nodo<Tipo>;
    if (p == NULL)
        return true;
    else {
        delete p;
        return false;
    }
};

template <class Tipo>
bool Lista<Tipo>::InsComienzo(Tipo Valor) {
    Apuntador nuevo;
    if (!Llena()) {
        nuevo = new nodo<Tipo>;
        nuevo->info = Valor;
        nuevo->prox = Primero;
        Primero = nuevo;
        return true;
    } else
        return false;
};

template <class Tipo>
bool Lista<Tipo>::EliComienzo(Tipo &Valor) {
    Apuntador viejo;
    if (!Vacia()) {
        viejo = Primero;
        Valor = viejo->info;
        Primero = Primero->prox;
        delete viejo;
        return true;
    } else
        return false;
};

template <class Tipo>
bool Lista<Tipo>::InsDespues(Apuntador p, Tipo Valor) {
    Apuntador nuevo;
    if (!Llena())
        if (p == NULL)
            return false;
        else {
            nuevo = new nodo<Tipo>;
            nuevo->info = Valor;
            nuevo->prox = p->prox;
            p->prox = nuevo;
            return true;
        }
    else
        return false;
};

template <class Tipo>
bool Lista<Tipo>::EliDespues(Apuntador p, Tipo &Valor) {
    Apuntador viejo;
    if (p == NULL)
        return false;
    else if (p->prox == NULL)
        return false;
    else {
        viejo = p->prox;
        Valor = viejo->info;
        p->prox = viejo->prox;
        delete viejo;
        return true;
    };
};

template <class Tipo>
nodo<Tipo>* Lista<Tipo>::ObtProx(Apuntador p) {
    return p->prox;
};

template <class Tipo>
void Lista<Tipo>::AsigProx(Apuntador p, Apuntador q) {
    p->prox = q;
};

template <class Tipo>
Tipo Lista<Tipo>::ObtInfo(Apuntador p) {
    return p->info;
};

template <class Tipo>
void Lista<Tipo>::AsigInfo(Apuntador p, Tipo Valor) {
    p->info = Valor;
};

template <class Tipo>
Lista<Tipo>::~Lista() {
    nodo<Tipo> *p;
    while (!Vacia()) {
        p = Primero->prox;
        delete Primero;
        Primero = p;
    };
};

template <class Tipo>
int Lista<Tipo>::Contar() {
    nodo<Tipo>* p;
    int cont = 0;
    p = Primero;
    while (p != NULL) {
        cont++;
        p = p->prox;
    }
    return cont;
};

template <class Tipo>
int Lista<Tipo>::ContarNodosPrioridad() {
    nodoPrioridad<Tipo>* p;
    int cont = 0;
    p = PrimeroPrioridad;
    while (p != NULL) {
        cont++;
        p = p->prox;
    }
    return cont;
};

/*template <class Tipo>
nodo<Tipo>* Lista<Tipo>::Buscar(Tipo Valor) {
    nodo<Tipo> *aux = NULL;
    Apuntador ap;
    if (ap != NULL) {
        aux = ap;
        while (aux != NULL) {
            if (aux->info == Valor) {
                return aux;
            }
            aux = aux->prox;
        }
    }
};*/

template <class Tipo>
void Lista<Tipo>::pasarListaAux(Lista<Tipo> &listaFuente, Lista<Tipo> &listaDestino) {
    Tipo valor;
    int tamano = 0;
    tamano = listaFuente.Contar();
    for (int i = 0; i < tamano; i++) {
        listaFuente.EliComienzo(valor);
        listaDestino.InsComienzo(valor);
    }
};

template <class Tipo>
bool Lista<Tipo>::RemoverNodoCola(Tipo &Valor) {

    Apuntador viejo;
    // verificar si la lista no estaa vacia
    if (!Vacia()) {
        viejo = Primero;
        Valor = viejo->info;
        Primero = viejo->prox;
        if (Primero == NULL)
            Final = NULL;
        delete viejo;

        return true;
    }
    return false;

};

template <class Tipo>
bool Lista<Tipo>::InsertarNodoCola(Tipo Valor) {

    Apuntador nuevo;

    // verificar si la lista no estaa llena
    if (!Llena()) {
        
        // crear un nodo
        nuevo = new nodo<Tipo>;
        nuevo->info = Valor;
        nuevo->prox = NULL;
        if (Final == NULL) {
            Primero = nuevo;
        } else {
            Final->prox = nuevo;
        }
        Final = nuevo;
        return true;
    } else {
        std::cout << "Memoria insuficiente para insertar nodo." << std::endl; // Mensaje de depuración
        return false;
    }
};

template <class Tipo>
bool Lista<Tipo>::InsFinal(Tipo Valor) {
    Apuntador nuevo;
    if (!Llena()) {
        nuevo = new nodo<Tipo>;
        if (nuevo == nullptr) {
            // Manejar error de asignación de memoria
            return false;
        }
        nuevo->info = Valor;
        nuevo->prox = nullptr; // Inicializar prox a nullptr

        if (Vacia()) {
            Primero = nuevo;
            Final = Primero;
            return true; // Retorno temprano para simplificar la lógica
        }

        Final->prox = nuevo;
        Final = nuevo;
        return true;
    }
    else {
        return false;
    }
}

template <class Tipo>
nodo<Tipo>* Lista<Tipo>::ObtFinal() {
    return Final;
}




// METODOS DE COLA PRIORIDAD

template <class Tipo>
bool Lista<Tipo>::VaciaPrioridad() {
    return PrimeroPrioridad == NULL;
};

template <class Tipo>
bool Lista<Tipo>::LlenaPrioridad() {
    nodoPrioridad<Tipo> *p;
    p = new nodoPrioridad<Tipo>;
    if (p == NULL)
        return true;
    else {
        delete p;
        return false;
    }
};

template <class Tipo>
Tipo Lista<Tipo>::ObtInfoPrioridad(ApuntadorPrioridad p) {
    return p->info;
};

template <class Tipo>
int Lista<Tipo>::ObtPrioridad(ApuntadorPrioridad p) {
    return p->prioridad;
};

template <class Tipo>
nodoPrioridad<Tipo>* Lista<Tipo>::ObtPrimeroPrioridad() {
    return PrimeroPrioridad;
};

template <class Tipo>
nodoPrioridad<Tipo>* Lista<Tipo>::ObtProxPrioridad(ApuntadorPrioridad p) {
    return p->prox;
};

template <class Tipo>
bool Lista<Tipo>::InsertarNodoColaPrioridad(Tipo Valor, int p) {

    ApuntadorPrioridad nuevo;

    // verificar si la lista no estaa llena
    if (!LlenaPrioridad()) {

        // crear un nodo
        nuevo = new nodoPrioridad<Tipo>;
        nuevo->info = Valor;
        nuevo->prioridad = p;
        nuevo->prox = NULL;
        if (FinalPrioridad == NULL) {
            PrimeroPrioridad = nuevo;
        } else {
            FinalPrioridad->prox = nuevo;
        }
        FinalPrioridad = nuevo;
        return true;
    } else {
        std::cout << "Memoria insuficiente para insertar nodo." << std::endl; // Mensaje de depuración
        return false;
    }
};

template <class Tipo>
bool Lista<Tipo>::RemoverNodoColaPrioridad(Tipo &Valor, int &p) {
    // verificar si la lista no estaa vacia
    if (!VaciaPrioridad()) {
        ApuntadorPrioridad viejo = PrimeroPrioridad;
        Valor = viejo->info;
        p = viejo->prioridad;
        PrimeroPrioridad = viejo->prox;
        if (PrimeroPrioridad == NULL)
            FinalPrioridad = NULL;
        delete viejo;

        return true;
    }
    return false;
};

template <class Tipo>
bool Lista<Tipo>::InsertarNodoOrdenado(Tipo inf, int prio)
{
    bool result = false;
    Tipo marca;

    if (VaciaPrioridad()) {
        InsertarNodoColaPrioridad(inf, prio);
        result = true;
    }
    else
    {
        Tipo infAux;
        int prioAux;

        InsertarNodoColaPrioridad(marca,777);

        do{

            RemoverNodoColaPrioridad(infAux,prioAux);

            if (prioAux > prio && result == false) {
                InsertarNodoColaPrioridad(inf, prio);
                result = true;
            }

            if (prioAux == 777){ break; }
            InsertarNodoColaPrioridad(infAux, prioAux);

        }while (prioAux != 777);
    }

    return result;
}


// Explicit instantiation
template class Lista<std::string>;
template class Lista<Elector>;
template class Lista<Candidato>;

