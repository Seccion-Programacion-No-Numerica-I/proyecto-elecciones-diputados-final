#include "Inscripcion.h"
#include <iostream>
#include <fstream>

Inscripcion::Inscripcion() {}

bool Inscripcion::verificarDisponibilidad(Candidato cand) {

	// falta verificar que el candidato no este inscrito

	if (cand.getIdPartido() < 0 || cand.getIdPartido() > 5) {
		std::cout << "ID de partido no valido." << std::endl;
		return false;
	}
	if (candidatosPorPartido[cand.getIdPartido() - 1] >= 5) {
		std::cout << "El partido ya tiene 5 candidatos inscritos." << std::endl;
		return false;
	}
	return true;
}

void Inscripcion::CargarCandidatos() {
	string dato, urlArchivo = "candidatos.txt";
	fstream archivo;
	archivo.open(urlArchivo.c_str());

	int cont = 0; // Declaramos un contador para llevar el control de la estructura de archivo
	auto *candidato = new Candidato();
	// int partido = 1;
	while (archivo >> dato) {
		// leemos cada palabra del archivo y la asignamos al dato.
		cont++;
		// dependiendo de la estructura que se lleve, se asigna el dato al atributo
		if (cont % 5 == 1) { candidato->setCedula(dato); }
		if (cont % 5 == 2) { candidato->setNombre(dato); }
		if (cont % 5 == 3) { candidato->setApellido(dato); }
		 if (cont % 5 == 4) { 
			int partido = std::stoi(dato);
			candidato->setIdPartido(partido); 
			}
		if (dato == ";") { // al encontrar un ; en el archivo registra el candidato
			
			candidato->setStatus("ACTIVO"); // el candidato esta activo
			candidato->mostrarInformacion(); // muestra la informacion del candidato
			candidatos.InsertarNodoCola(*candidato); 
			// candidatosPorPartido[partido - 1]++;
			// insertamos el candidato en la cola
			candidato = new Candidato();

		}
	}
	archivo.close();
	 delete candidato;
	// cout << "\033[H\033[2J";
	cout<<"\nRegistrados " << cont/5 << " candidatos."<< endl;
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

			cout << "Ingrese la cedula: ";
			cin >> cedula;
			cin.ignore();
			if (cedula.empty()) {
				cout << "La cedula no puede estar vacia" << endl;
			} else {

				cout << "Cedula: " << cedula << " guardada" << endl;
			}
		}

		while (nombre.empty()) {

			cout << "Ingrese el nombre: ";
			cin >> nombre;
			cin.ignore();
			if (nombre.empty()) {
				cout << "el nombre no puede estar vacio" << endl;
			} else {

				cout << "Nombre: " << nombre << " guardado" << endl;
			}
		}

		while (apellido.empty()) {

			cout << "Ingrese el apellido: ";
			cin >> apellido;
			cin.ignore();
			if (apellido.empty()) {
				cout << "el apellido no puede estar vacio" << endl;
			} else {

				cout << "Apellido: " << apellido << " guardado" << endl;
			}
		}

		while (partido < 1 || partido > 5) {

			cout << "Ingrese el partido politico: ";
			cin >> partido;
			if (cin.fail() || partido < 1 || partido > 5) {
				cout << "Ingrese un partido valido (1, 2, 3, 4, 5)" << endl;
				partido = 0; // Reiniciar el partido para asegurar que el ciclo continua
			}
		}

		// Crear un objeto Candidato y agregarlo a la lista
		Candidato candidato(cedula, nombre, apellido, partido);
		if (verificarDisponibilidad(candidato)) {
			candidato.setStatus("ACTIVO");
			candidatos.InsFinal(candidato);
		}
		// Mostrar la lista de candidatos registrados
		cout << "\nLista de Candidatos Registrados:" << endl;
		nodo<Candidato> *p = candidatos.ObtPrimero();
		while (p != nullptr) {
			candidatos.ObtInfo(p).mostrarInformacion();
			cout << endl;
			p = candidatos.ObtProx(p); // Aquí se corrigió el nombre del metodo
		}
		cout << "Pulse enter para continuar...";
		cin.ignore();
		cin.get();
	}
}

void Inscripcion::Eliminar(Candidato cand) {
	std::cout << "\n\nCandidato Eliminado:\n";
	cand.mostrarInformacion();
	candidatosPorPartido[cand.getIdPartido() - 1]--; // Actualizamos el contador de candidatos por partido

	cout << "Pulse enter para continuar...";
	cin.get();
}

void Inscripcion::Buscar(Candidato cand) {
	std::cout << "\n\nCandidato Mostrado:\n";
	cand.mostrarInformacion();

	cout << "Pulse enter para continuar...";
	cin.get();
}

Candidato Inscripcion::Modificar(Candidato cand, string cedula) {
	Candidato nuevo;
	string nuevoNombre, nuevoApellido;
	int idNuevoPartido, opcionEstatus;

	cout << "\n\nCandidato encontrado\n"
	     << endl;
	cand.mostrarInformacion();

	cout << "\tIngrese los nuevos datos para el candidato con cedula " << cand.getCedula() << " \n\n";
	nuevo.setCedula(cedula);
	cout << "Nombre:";
	getline(cin, nuevoNombre);
	nuevo.setNombre(nuevoNombre);
	cout << "Apellido:";
	getline(cin, nuevoApellido);
	nuevo.setApellido(nuevoApellido);
	cout << "ID del partido:";
	cin >> idNuevoPartido;
	nuevo.setIdPartido(idNuevoPartido);
	do {
		cout << "Nuevo estatus del candidato: \n\n1.- Activo\n2.-Inactivo\n";
		cin >> opcionEstatus;
		switch (opcionEstatus) {
			case 1:
				nuevo.setStatus("ACTIVO");
				break;
			case 2:
				nuevo.setStatus("INACTIVO");
				break;
			default:
				cout << "Opcion invalida";
				break;
		}
	} while (opcionEstatus < 1 || opcionEstatus > 2);

	if (verificarDisponibilidad(nuevo)) {
		cout << "\nCandidato modificado exitosamente:\n";
		nuevo.mostrarInformacion();

		cout << "Pulse enter para continuar...";
		cin.ignore();
		cin.get();

		return nuevo;
	}
	cout << "\nCandidato no modificado\n";

	cout << "Pulse enter para continuar...";
	cin.get();

	return cand;
}

void Inscripcion::iterarCandidatos(string busqueda, int opcion) {

	Candidato marca;
	marca.setCedula("$$$$$$");

	if (candidatos.Vacia())
		cout << "No hay candidatos inscritos." << endl;
	else {
		Candidato candAux;
		bool encontrado = false;

		candidatos.InsertarNodoCola(marca);

		while (true) {

			candidatos.RemoverNodoCola(candAux);

			if (candAux.getCedula() == marca.getCedula()) {
				break;
			}

			// CODIGO QUE SE EJECUTA PARA CADA ITERACION DE CANDIDATO
			// ⬇️⬇️⬇️⬇️⬇️⬇️⬇️

			if (opcion == 4) {
				// mostrar todos los candidatos por partido
				if (candAux.getNombrePartido() == busqueda) {
					encontrado = true;
					cout << "Candidato: " << candAux.getNombre() << " " << candAux.getApellido() << endl;
				}
			}

			else if (candAux.getCedula() == busqueda) {
				encontrado = true;

				if (opcion == 1) {
					Buscar(candAux); // Buscar candidato individual
				}
				if (opcion == 2) {
					candAux = Modificar(candAux, busqueda); // Modificar candidato individual
				}
				if (opcion == 3) {
					Eliminar(candAux); // Eliminar candidato individual
					continue;
				}
			}

			// ⬆️⬆️⬆️⬆️⬆️⬆️⬆️
			// FIN DEL CODIGO QUE SE EJECUTA PARA CADA ITERACION DE CANDIDATO

			candidatos.InsertarNodoCola(candAux);
		}

		if (!encontrado) {
			std::cout << "No se han encontrado un candidato." << std::endl;
		}
	}
}

void Inscripcion::MostrarCandidatos() {

	nodo<Candidato> *actual = candidatos.ObtPrimero();
	if (!actual) {
		std::cout << "No hay candidatos inscritos en la cola." << std::endl;

		cout << "Pulse enter para continuar...";
		cin.get();

		return;
	}

	std::cout << "Candidatos inscritos: \n"
	          << std::endl;
	while (actual) {
		Candidato candidatoActual = candidatos.ObtInfo(actual);
		candidatoActual.mostrarInformacion();
		actual = candidatos.ObtProx(actual);
	}

	cout << "Pulse enter para continuar...";
	cin.get();
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
	cout << "Pulse enter para continuar...";
	cin.get();
}

void Inscripcion::MostrarReporteCompleto() {
	int cont = 1;
	// variable auxiliar que utilizamos para almacenar si hay candidatos en algun partido y posteriormente mostar un mensaje.
	bool AuxHayCandidatos = false;
	string partidos[5] = {"A", "B", "C", "D", "E"};

	if (candidatos.Vacia()) {
		cout << "\n No hay Candidatos inscritos. \n"
		     << endl;

		cout << "Pulse enter para continuar...";
		cin.get();

		return;
	}

	for (int i = 0; i < 5; i++) {
		AuxHayCandidatos = false;
		cout << "\n Candidatos Por el partido: " << endl;

		cout<<partidos[i]<<endl;
		cout<<generarEsloganAletorio()<<endl;

		nodo<Candidato> *actualCandidato = candidatos.ObtPrimero();
		while (actualCandidato) {
			Candidato cand = candidatos.ObtInfo(actualCandidato);
			if (i == cand.getIdPartido() - 1) {

				string nombreCompleto = cand.getNombre() + " " + cand.getApellido();
				cout << " " << cont << ".";
				cout << "\n " << nombreCompleto << endl;
				cout << " C.I: " << cand.getCedula() << endl;
				cont++;
				AuxHayCandidatos = true;
			}
			actualCandidato = candidatos.ObtProx(actualCandidato);
		}
		if (!AuxHayCandidatos) {
			cout << " No Hay Candidatos Inscritos por el partido " << "\"" << partidos[i] << "\". \n"
			     << endl;
		}
		cont = 1;
		
	}
	cout << "Pulse enter para continuar...";
	cin.get();
	return;
}

int Inscripcion::generarNumeroAleatorio() {
	srand(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	// generar numero aleatorio desde el 0 hasta el 9
	int numeroAleatorio = rand() % 10;
	return numeroAleatorio;
}

string Inscripcion::generarEsloganAletorio() {
	return esloganes[generarNumeroAleatorio()];
}

Lista<Candidato>& Inscripcion::getCandidatos() {
	return candidatos;
}
