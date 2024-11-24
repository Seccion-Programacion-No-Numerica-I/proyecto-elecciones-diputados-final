#include "Candidato.h"

Candidato::Candidato() {
}

Candidato::Candidato(const string& ced, const string& nom, const string& ape, int partidoId)
    : cedula(ced), nombre(nom), apellido(ape), idPartido(partidoId), votos(0) // Inicializa los atributos
{}

void Candidato::setCedula(string ced) {
    cedula = ced;
}

string Candidato::getCedula() {
    return cedula;
}

void Candidato::setNombre(string nomb) {
    nombre = nomb;
}

string Candidato::getNombre() {
    return nombre;
}

void Candidato::setApellido(string apel) {
    apellido = apel;
}

string Candidato::getApellido() {
    return apellido;
}

void Candidato::setIdPartido(int idprd) {
    idPartido = idprd;
}

int Candidato::getIdPartido() {
    return idPartido;
}

string Candidato::getStatus() {
    return status.obtenerPila();
}

void Candidato::setStatus(string str){
	status.insertarPila(str);
}

string Candidato::getNombrePartido() {
    return nombresPartidos[idPartido - 1];
}

int Candidato::getVotos() {
    return votos;
}

void Candidato::mostrarInformacion() {
    cout << "Cedula: " << cedula<< endl;
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Partido: " << getNombrePartido() << endl;
    cout << "Estatus: " << getStatus() << endl;
    cout << "Votos: " << getVotos() << endl;
    cout << "\n" << endl;

};

bool Candidato::operator==(const Candidato& other) const {
    return cedula == other.cedula &&
           nombre == other.nombre &&
           apellido == other.apellido &&
           idPartido == other.idPartido;
}
