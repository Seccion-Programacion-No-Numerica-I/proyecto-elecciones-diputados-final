//
// Created by arnal on 18/11/2024.
//

#include "Votante.h";

Votante::Votante() {}

Votante::Votante(string cedula, string nombre, string apellido, int prioridad) {
    this->cedula = cedula;
    this->nombre = nombre;
    this->apellido = apellido;
    this->prioridad = prioridad;
}

void Votante::setNombre(string nombre) {
    this->nombre = nombre;
}
void Votante::setApellido(string apellido) {
    this->apellido = apellido;
}
void Votante::setPrioridad(int prioridad) {
    this->prioridad = prioridad;
}
string Votante::getNombre() {
    return this->nombre;
}
string Votante::getApellido() {
    return this->apellido;
}
int Votante::getPrioridad() {
    return this->prioridad;
}



