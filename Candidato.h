#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <iostream>
#include <string>
#include "Libreria/Lista.h"
#include "Libreria/Pila.h"
using namespace std;

class Candidato {
private:
    string cedula, nombre, apellido, partido;
    int idPartido, votos;
    Pila status;
    string nombresPartidos[5] = {"A", "B", "C", "D", "E"};

public:
    Candidato();
    Candidato(const string& ced, const string& nom, const string& apel, int partidoId);

    // Setter y getters
    void setCedula(string ced);
    string getCedula();
    void setNombre(string n);
    string getNombre();
    void setApellido(string apel);
    string getApellido();
    void setIdPartido(int idprd);
    int getIdPartido();
    void setVotos(int v);
    int getVotos();
    // Métodos para modificar información del candidato
    void agregarVoto() { votos++; }

    // Métodos para pila estatus
    void setStatus(string st);
    string getStatus();


    // Método para obtener el nombre del partido según el ID
    string getNombrePartido();

    void mostrarInformacion();

    // Operador de igualdad
    bool operator==(const Candidato& other) const;
};

#endif // CANDIDATO_H