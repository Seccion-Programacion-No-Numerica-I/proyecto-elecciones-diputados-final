//
// Created by arnal on 18/11/2024.
//
#ifndef VOTANTE_H
#define VOTANTE_H
#include <string>
using namespace std;

class Votante {
    private:
    string nombre, apellido, cedula;
    int prioridad = 0;

    public:
    // Constructores
    Votante();
    Votante(string cedula, string nombre, string apellido, int prioridad);

    // Setters y Getters
    string getNombre();
    void setNombre(string nombre);
    string getApellido();
    void setApellido(string apellido);
    int getPrioridad();
    void setPrioridad(int prioridad);

    // Metodos

};

#endif //VOTANTE_H
