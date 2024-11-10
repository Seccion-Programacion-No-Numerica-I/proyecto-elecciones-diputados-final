#include "Inscripcion.h"
#include <iostream>

Inscripcion::Inscripcion() {}

bool Inscripcion::verificarDisponibilidad(Candidato cand){

    // falta verificar que el candidato no este inscrito 


    if (cand.getIdPartido() < 0 || cand.getIdPartido() > 5) {
        std::cout << "ID de partido no valido." << std::endl;
        return false;
    }
    if (candidatosPorPartido[cand.getIdPartido()-1] >= 5) {
        std::cout << "El partido ya tiene 5 candidatos inscritos." << std::endl;
        return false;
    }
    return true;
}


void Inscripcion::Registrar() {
    int cantidadCandidatos;
    cout << "Registro de Candidatos" << endl;
    cout << "Ingrese la cantidad de candidatos a registrar: ";
    cin >> cantidadCandidatos;
    cin.ignore(); // Limpiar el buffer

    for (int i = 0; i < cantidadCandidatos; i++) {
        string cedula, nombre, apellido;
        int partido = 0;

        cout << "\nRegistro del Candidato " << i + 1 << endl;
        
        while (cedula.empty()) {

        cout << "Ingrese la cédula: ";
        cin >> cedula;cin.ignore();
        if (cedula.empty()) {
            cout << "La cédula no puede estar vacia" << endl;
        } else {

        cout << "Cedula: " << cedula << " guardada" << endl;
        }
        }

        while (nombre.empty()) {

        cout << "Ingrese el nombre: ";
        cin >> nombre; cin.ignore();
        if (nombre.empty()) {
            cout << "el nombre no puede estar vacio" << endl;
        } else {

        cout << "Nombre: " << nombre << " guardado" << endl;
        }
        }

        while (apellido.empty()) {

        cout << "Ingrese el apellido: ";
        cin >> apellido;cin.ignore();
        if (apellido.empty()) {
            cout << "el apellido no puede estar vacio" << endl;
        } else {

        cout << "Apellido: " << apellido << " guardado" << endl;
        }
        }

     
        
        while (partido < 1 || partido > 5) {
            
        cout << "Ingrese el partido político: ";
        cin >> partido;
        if (cin.fail() || partido < 1 || partido > 5) {
                cout << "Ingrese un partido valido (1, 2, 3, 4, 5)" << endl;
                partido = 0; // Reset partido to ensure the loop continues
            }
        }
        
        // Crear un objeto Candidato y agregarlo a la lista
        Candidato candidato(cedula, nombre, apellido, partido);
      if(verificarDisponibilidad(candidato)) {
        candidato.setStatus("ACTIVO");
        candidatos.InsFinal(candidato);
        
        
      }
        // Mostrar la lista de candidatos registrados
    cout << "\nLista de Candidatos Registrados:" << endl;
    nodo<Candidato>* p = candidatos.ObtPrimero();
    while (p != nullptr) {
        candidatos.ObtInfo(p).mostrarInformacion();
        cout << endl;
        p = candidatos.ObtProx(p); // Aquí se corrigió el nombre del método
    }
    }
}









// void Inscripcion::Registrar() {
//     Candidato nuevo; string nuevaCedula, nuevoNombre, nuevoApellido; int idNuevoPartido;

//     cout << "\tRegistrando Candidato  ------------ \n ";

//     cout<<"Cedula:"; cin>>nuevaCedula; cin.ignore();
//     nuevo.setCedula(nuevaCedula);

//     cout<<"Nombre:"; getline(cin, nuevoNombre);
//     nuevo.setNombre(nuevoNombre);

//     cout<<"Apellido:"; getline(cin, nuevoApellido);
//     nuevo.setApellido(nuevoApellido);

//     cout<<"ID del partido:"; cin>>idNuevoPartido;
//     nuevo.setIdPartido(idNuevoPartido);

//     // Establece el estatus como activo al crear un nuevo candidato
//     nuevo.setStatus("Activo");

//     if(verificarDisponibilidad(nuevo)) {
//         candidatos.InsertarNodoCola(nuevo);
//         partidos[nuevo.getIdPartido()].InsertarNodoCola(nuevo);
//         candidatosPorPartido[nuevo.getIdPartido()]++;

//         cout << "\nCandidato registrado exitosamente:\n";
//         nuevo.mostrarInformacion();

//     } else cout << "\nFallo al registrar el candidato\n";
// }

void Inscripcion::Eliminar(Candidato cand) {
    std::cout << "\n\nCandidato Eliminado:\n";
    cand.mostrarInformacion();
    candidatosPorPartido[cand.getIdPartido()-1]--; // Actualizamos el contador de candidatos por partido
}

void Inscripcion::Buscar(Candidato cand) {
    std::cout << "\n\nCandidato Mostrado:\n";
    cand.mostrarInformacion();
}

Candidato Inscripcion::Modificar(Candidato cand, string cedula) {
    Candidato nuevo; string nuevoNombre, nuevoApellido; int idNuevoPartido, opcionEstatus;

    cout << "\n\nCandidato encontrado\n" << endl;
    cand.mostrarInformacion();

    cout << "\tIngrese los nuevos datos para el candidato con cedula "<<cand.getCedula()<<" \n\n";
    nuevo.setCedula(cedula);
    cout<<"Nombre:"; getline(cin, nuevoNombre);
    nuevo.setNombre(nuevoNombre);
    cout<<"Apellido:"; getline(cin, nuevoApellido);
    nuevo.setApellido(nuevoApellido);
    cout<<"ID del partido:"; cin>>idNuevoPartido;
    nuevo.setIdPartido(idNuevoPartido);
    do{
        cout<<"Nuevo estatus del candidato: \n\n1.- Activo\n2.-Inactivo\n"; cin>>opcionEstatus;
        switch (opcionEstatus){
        case 1:
            nuevo.setStatus("ACTIVO");
            break;
        case 2:
            nuevo.setStatus("INACTIVO");
            break;
        default:
            cout<<"Opcion invalida";
            break;
        }
    }while(opcionEstatus < 1 || opcionEstatus > 2);

    if(verificarDisponibilidad(nuevo)) {
        cout << "\nCandidato modificado exitosamente:\n";
        nuevo.mostrarInformacion();
        return nuevo;
    }
    cout << "\nCandidato no modificado\n";
    return cand;
}


void Inscripcion::iterarCandidatos(string busqueda, int opcion) {

    Candidato marca; marca.setCedula("$$$$$$");

    if (candidatos.Vacia()) cout << "No hay candidatos inscritos." << endl; else {
        Candidato candAux;
        bool encontrado = false;

        candidatos.InsertarNodoCola(marca);

        while (true){

            candidatos.RemoverNodoCola(candAux);

            if (candAux.getCedula() == marca.getCedula()) { break; }

            // CODIGO QUE SE EJECUTA PARA CADA ITERACION DE CANDIDATO
            // ⬇️⬇️⬇️⬇️⬇️⬇️⬇️

            if(opcion == 4) { // mostrar todos los candidatos por partido
                if(candAux.getNombrePartido() == busqueda) {
                    encontrado = true;
                    cout << "Candidato: " << candAux.getNombre() << " " << candAux.getApellido() << endl;
                }
            }

            else if (candAux.getCedula() == busqueda) {
                encontrado = true;

                if(opcion == 1) { Buscar(candAux); } // Buscar candidato individual
                if(opcion == 2) { candAux = Modificar(candAux, busqueda); } // Modificar candidato individual
                if(opcion == 3) { Eliminar(candAux); continue; } // Eliminar candidato individual

            }

            // ⬆️⬆️⬆️⬆️⬆️⬆️⬆️
            // FIN DEL CODIGO QUE SE EJECUTA PARA CADA ITERACION DE CANDIDATO

            candidatos.InsertarNodoCola(candAux);
        }

        if (!encontrado) { std::cout << "No se han encontrado un candidato." << std::endl; }
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

void Inscripcion::ReporteGeneral() {
    // hay que mostrar a los candidatos por partido
    string partidos[5] = {"A", "B", "C", "D", "E"};

    for (int i = 0; i < 5; i++) {
        cout << "Partido :" << partidos[i] << endl;
        cout << "========================" << endl;

        if (candidatos.Vacia()) {
            cout << "Lista vacía" << endl;
            break; // Termina el metodo si la lista está vacía
        }

        Candidato marca;
        marca.setCedula("$$$");
        candidatos.InsFinal(marca);

        int contador = 0;

        auto it = candidatos.ObtPrimero();

        while (candidatos.ObtInfo(it).getCedula() != marca.getCedula()) {
            Candidato actual = candidatos.ObtInfo(it);

            if (actual.getNombrePartido() == partidos[i]) {
                cout << "Candidato: " << actual.getNombre() << " " << actual.getApellido() << endl;
                contador++;
            }

            candidatos.InsFinal(actual);
            it = candidatos.ObtProx(it);
        }

        Candidato primero = candidatos.ObtInfo(it);
        if (primero.getCedula() == marca.getCedula()) {
            candidatos.EliComienzo(marca);
        }

        if (contador == 0) {
            cout << "No hay candidatos que pertenezcan al partido " << partidos[i] << "." << endl;
        }
        cout << "========================" << endl;
    }
}




/*
void Inscripcion::MostrarCandidatosPorPartido(string buscarPartido) {
    if (candidatos.Vacia()) {
        cout << "Lista vacía" << endl;
        return; // Termina el método si la lista está vacía
    }
    
    Candidato marca;
    marca.setCedula("$$$"); 
    candidatos.InsFinal(marca);

    int contador = 0;

    auto it = candidatos.ObtPrimero();
    
    while (candidatos.ObtInfo(it).getCedula() != marca.getCedula()) {
        Candidato actual = candidatos.ObtInfo(it);

        if (actual.getNombrePartido() == buscarPartido) {
            cout << "Candidato: " << actual.getNombre() << " " << actual.getApellido() << endl;
            contador++;
        }

        candidatos.InsFinal(actual);
        it = candidatos.ObtProx(it);
    }

    Candidato primero = candidatos.ObtInfo(it);
    if (primero.getCedula() == marca.getCedula()) {
        candidatos.EliComienzo(marca);
    }

    if (contador == 0) {
        cout << "No hay candidatos que pertenezcan al partido " << buscarPartido << "." << endl;
    }
}

*/
