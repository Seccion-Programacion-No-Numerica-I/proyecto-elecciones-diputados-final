//
// Created by arnal on 18/11/2024.
//
#ifndef VOTANTE_H
#define VOTANTE_H
#include <string>
using namespace std;

class Elector {
    private:
    string nombre, apellido, cedula;
    string prioridades[3] = {"Normal", "Embarazadas", "Tercera edad"};

    public:
    // Constructores
    Elector();
    Elector(const string& ced, const string& nom, const string& ape);


    // Setters y Getters
    void setCedula(string ced);
    string getNombre();
    void setNombre(string nombre);
    string getApellido();
    void setApellido(string apellido);
    string getCedula();
    string getNombrePrioridad(int p);

    // Metodos
    void mostrarInfo(int p);

};

#endif //VOTANTE_H
