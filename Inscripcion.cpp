#include "Inscripcion.h"
#include <iostream>

Inscripcion::Inscripcion() {}

void mensaje(){
    std::cout << "mensaje de objeto inscripcion." << std::endl; // Mensaje de depuración
}

Candidato Inscripcion::CrearMarca() {
    Candidato candidatos;
    string ced, nomb, apel;
    int votos, idprd;

    ced = "-999999999999";
    nomb = "$$$$$";
    apel = "$$$$$";
    votos = -999999999999;
    idprd = -999999999999;

    candidatos.setCedula(ced);
    candidatos.setNombre(nomb);
    candidatos.setApellido(apel);
    candidatos.setIdPartido(idprd);
    //candidatos.setEstatusInicial();

    return candidatos;
}

bool Inscripcion::verificarDisponibilidad(Candidato cand){
    if (cand.getIdPartido() < 0 || cand.getIdPartido() >= 5) {
        std::cout << "ID de partido no válido." << std::endl;
        return false;
    }
    if (candidatosPorPartido[cand.getIdPartido()] >= 5) {
        std::cout << "El partido ya tiene 5 candidatos inscritos." << std::endl;
        return false;
    }
    if (candidatos.Contar() >= 25) {
        std::cout << "Se alcanzó el máximo de 25 candidatos." << std::endl;
        return false;
    }

    std::cout << "\n Disponibilidad Aprobada" << std::endl; // Mensaje de depuración
    return true;
}

void Inscripcion::RegistrarCandidato(Candidato cand) {

    candidatos.InsertarNodoCola(cand);
    partidos[cand.getIdPartido()].InsertarNodoCola(cand);
    candidatosPorPartido[cand.getIdPartido()]++;
    std::cout << "Candidato inscrito exitosamente en RegistrarCandidato." << std::endl; // Mensaje de depuración
}

void Inscripcion::EliminarCandidato(string cedCandidato) {


    std::cout << "Entrando a EliminarCandidato." << std::endl; // Mensaje de depuración
    // Declara dos objetos de tipo Candidato: candAux y marca

    Candidato candAux, marca;
    // Declara una variable booleana para indicar si se encontró el candidato
    bool encontrado = false;
    // Crea un objeto "marca" que se usará como marcador
    marca = CrearMarca();

// Verifica si la lista de candidatos no está llena
    if (!candidatos.Llena()) {
// Inserta el marcador al final de la lista de candidatos
        candidatos.InsertarNodoCola(marca);
 // Mientras no se haya encontrado el candidato
        while (true){

           // Remueve el último nodo de la lista de candidatos y lo almacena en candAux
            candidatos.RemoverNodoCola(candAux);
          
          // Si el candidato removido es el marcador, se ha llegado al final de la lista

            if (candAux.getCedula() == marca.getCedula()) { break; }

           // Si el candidato removido tiene la cédula que se quiere eliminar
            if (candAux.getCedula() == cedCandidato) {

                    std::cout << "\n\nCandidato eliminado\n\n";
                    encontrado = true;
                    candidatosPorPartido[candAux.getIdPartido()]; // Actualizamos el contador de candidatos por partido
// Si no es el candidato a eliminar, se reinserta en lalista
            } else { candidatos.InsertarNodoCola(candAux); }
        }
      // Si no se encontró el candidato, se imprime un mensaje
        if (!encontrado) { std::cout << "Candidato no encontrado." << std::endl; }
    }
}

void Inscripcion::MostrarCandidatos() {

    nodo<Candidato>* actual = candidatos.ObtPrimero();
    if (!actual) {
        std::cout << "No hay candidatos inscritos en la cola." << std::endl;
        return;
    }

    std::cout << "Candidatos inscritos: \n" << std::endl;
    while (actual) {
        Candidato candidatoActual = candidatos.ObtInfo(actual);
        candidatoActual.mostrarInformacion();
        actual = candidatos.ObtProx(actual);
    }
}

void Inscripcion::ModificarCandidato(string cedula){
    Candidato candAux, marca;
    bool existe = false;
    marca = CrearMarca();
    if(!candidatos.Llena()){
        candidatos.InsertarNodoCola(marca);
        while(true){
        	candidatos.RemoverNodoCola(candAux);

        	if (candAux.getCedula() == marca.getCedula()) {
        		break;
        	}

        	if (candAux.getCedula() == cedula) {
        		cout << "\n\nIngrese los nuevos datos para el candidato con cedula "<<candAux.getCedula()<<" \n\n";
        		existe = true;
        		string nuevoNombre, nuevoApellido, nuevoStatus;
        		int idNuevoPartido;
        		cout<<"Nombre: "; cin>>nuevoNombre;
        		cout<<"Apellido: "; cin>>nuevoApellido;
        		cout<<"Nuevo ID del partido: "; cin>>idNuevoPartido;
        		cout<<"Nuevo estatus del candidato: "; cin>>nuevoStatus;

        		candAux.setNombre(nuevoNombre);
        		candAux.setApellido(nuevoApellido);
        		candAux.setIdPartido(idNuevoPartido);
        		candAux.setStatus(nuevoStatus);

        		cout << "Candidato modificado exitosamente.\n\n";
        	}
        	candidatos.InsertarNodoCola(candAux);
        }
        if (!existe) {
        	cout << "Candidato no encontrado." << endl;
        }
    }
}

void Inscripcion::ReporteGeneral() {
    // hay que mostrar a los candidatos por partido
   int i = 0;
   while (i <= 5) 
   {
       Lista<Candidato> partidoActual = partidos[i];

       if (!partidoActual.Vacia()) {  
       nodo<Candidato>* actual = partidoActual.ObtPrimero();
       std::cout << "==================================" << endl;
       std::cout << "Partido " << partidoActual.ObtInfo(actual).getNombrePartido() << endl;
       std::cout << "==================================" << endl;
       while (actual) {
       Candidato candidatoActual = partidoActual.ObtInfo(actual);
       cout << "Candidato: " << candidatoActual.getNombre()  << " " << candidatoActual.getApellido() <<  endl;
       cout << "Cedula: " << candidatoActual.getCedula() << endl;
       actual = partidoActual.ObtProx(actual);
       }

       std::cout << endl;
    }

    i++;

   }
    
}

Candidato Inscripcion::BuscarCandidato(string ced) {

    if (candidatos.Vacia()) cout << "Lista vacia" << endl;
    Candidato encontrado;
    // crear marca 
    Candidato marca;

    marca = CrearMarca();

   // marca.getCedula() = "$$$";

    candidatos.InsFinal(marca);

    while (candidatos.ObtInfo(candidatos.ObtPrimero()).getCedula() != marca.getCedula()) {
        Candidato actual = candidatos.ObtInfo(candidatos.ObtPrimero());

        if (actual.getCedula() == ced) {
            encontrado = actual;
        }

        candidatos.InsFinal(actual);
        candidatos.AsigPrimero(candidatos.ObtProx(candidatos.ObtPrimero()));


    }

    Candidato primero = candidatos.ObtInfo(candidatos.ObtPrimero());
    if (primero.getCedula() == marca.getCedula()) {
        candidatos.EliComienzo(marca);
        // cout << "eliminada la marca!" << endl; 
    }

    if (encontrado.getNombre().empty()) {
        cout << "Candidato no encontrado" << endl;
        return Candidato();
    }

    return encontrado;
}

