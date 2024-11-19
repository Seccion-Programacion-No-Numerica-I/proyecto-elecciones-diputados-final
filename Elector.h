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
    int prioridad = 0;
    string prioridades[3] = {"Normal", "Embarazadas", "Tercera edad"};

    public:
    // Constructores
    Elector();
    Elector(const string& ced, const string& nom, const string& ape, int prio);


    // Setters y Getters
    void setCedula(string ced);
    string getNombre();
    void setNombre(string nombre);
    string getApellido();
    void setApellido(string apellido);
    int getPrioridad() const;
    void setPrioridad(int prioridad);
    string getCedula();
    string getNombrePrioridad();

    // Metodos
    void mostrarInfo() const;

};

#endif //VOTANTE_H
