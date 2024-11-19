//
// Created by arnal on 18/11/2024.
//

#include "Elector.h"

#include <iostream>
#include <ostream>

Elector::Elector() {}

Elector::Elector(const string& ced, const string& nom, const string& ape, int prio)
    : cedula(ced), nombre(nom), apellido(ape), prioridad(prio) // Inicializa los atributos
{}

void Elector::setCedula(string ced) { cedula = ced; }
void Elector::setNombre(string nom) { nombre = nom; }
void Elector::setApellido(string ape) { apellido = ape; }
void Elector::setPrioridad(int prio) { prioridad = prio; }
string Elector::getCedula() { return cedula; }
string Elector::getNombre() { return nombre; }
string Elector::getApellido() { return apellido; }
int Elector::getPrioridad() const { return prioridad; }
string Elector::getNombrePrioridad() { return prioridades[prioridad-1]; }

void Elector::mostrarInfo() const {
    cout << "\nMostrando Datos del elector" << endl;
    cout << "Cedula: " << cedula << endl;
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Prioridad: " << prioridad << "\n\n"<< endl;
}




