#include "Candidato.h"

Candidato::Candidato() {
}

Candidato::Candidato(const string& ced, const string& nom, const string& ape, int partidoId)
    : cedula(ced), nombre(nom), apellido(ape), idPartido(partidoId), votos(0) // Inicializa los atributos
{
    // Establece el estatus inicial como "Activo" al crear un nuevo candidato
    //std::cout << "Pila estatus " << pilaEstatus.ObtInfo(pilaEstatus.ObtPrimero()) << std::endl; // Mensaje de depuración
    //pilaEstatus.InsComienzo("Activo");
    //std::cout << "Pila estatus " << pilaEstatus.ObtInfo(pilaEstatus.ObtPrimero()) << std::endl; // Mensaje de depuración
    
}

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

string Candidato::getNombrePartido() {
    return nombresPartidos[idPartido - 1];
}

string Candidato::getEstatus() {
    string est;  // Se declara una variable de tipo string
    //pilaEstatus.EliComienzo(est);  // Se intenta eliminar el estado de la pila y se almacena en 'estatus'
    //pilaEstatus.InsComienzo(est);  // Se vuelve a insertar el estado eliminado en la pila
    return est;  // Se retorna el estado
}

void Candidato::ModificarEstatus(string nuevoEstatus) {
    /*
    string est;

    if (!pilaEstatus.Vacia()) {
        pilaEstatus.EliComienzo(est);
    }

    pilaEstatus.InsComienzo(nuevoEstatus);
}

void Candidato::setEstatusInicial() {
    pilaEstatus.InsComienzo("Activo");
    */

}
void Candidato::mostrarInformacion() {
    cout << "Nombre: " << nombre << endl;
    cout << "Partido: " << getNombrePartido() << endl;
   // cout << "\n" << endl;

};

bool Candidato::operator==(const Candidato& other) const {
    return cedula == other.cedula &&
           nombre == other.nombre &&
           apellido == other.apellido &&
           idPartido == other.idPartido;
}