//
// Created by arnal on 18/11/2024.
//

#ifndef VOTANTES_H
#define VOTANTES_H

#include "Libreria/Lista.h"
#include "Elector.h"
#include <string>
using namespace std;

class Votantes {
    private:
    Lista<Elector> electores;

    public:
    Votantes(); //Constructor

    //Registrar un elector
    //void insertarElector(Elector elector, int prioridad);
    void RegistrarElector();

    //Mostrar los electores registrados
    void MostrarElectores();

    void CargarDatos();
};

#endif //VOTANTES_H
