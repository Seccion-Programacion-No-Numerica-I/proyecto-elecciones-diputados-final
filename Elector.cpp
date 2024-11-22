//
// Created by arnal on 18/11/2024.
//

#include "Elector.h"

#include <iostream>
#include <ostream>

Elector::Elector() {}

Elector::Elector(const string& ced, const string& nom, const string& ape)
    : cedula(ced), nombre(nom), apellido(ape) // Inicializa los atributos
{}

void Elector::setCedula(string ced) { cedula = ced; }
void Elector::setNombre(string nom) { nombre = nom; }
void Elector::setApellido(string ape) { apellido = ape; }
string Elector::getCedula() { return cedula; }
string Elector::getNombre() { return nombre; }
string Elector::getApellido() { return apellido; }
string Elector::getNombrePrioridad(int p) { return prioridades[p-1]; }

void Elector::mostrarInfo(int p) {
    cout << "\nMostrando Datos del elector" << endl;
    cout << "Cedula: " << cedula << endl;
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Prioridad: " << getNombrePrioridad(p) << "\n\n"<< endl;
}




