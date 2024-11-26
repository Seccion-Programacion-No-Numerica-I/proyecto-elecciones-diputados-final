//
// Created by arnal on 18/11/2024.
//

#include "Votantes.h"
#include <fstream>
#include <iostream>
#include <bits/parse_numbers.h>

Votantes::Votantes() {}

void Votantes::RegistrarElector() {
	cout << "\t Registro de Elector\n"
	     << endl;
	string cedula, nombre, apellido;
	int prioridad = 0;

	while (cedula.empty()) {
		cout << "Ingrese la cedula: ";
		cin >> cedula;
		cin.ignore();
		if (cedula.empty()) {
			cout << "La cedula no puede estar vacia" << endl;
		}
	}

	while (nombre.empty()) {
		cout << "Ingrese el nombre: ";
		cin >> nombre;
		cin.ignore();
		if (nombre.empty()) {
			cout << "el nombre no puede estar vacio" << endl;
		}
	}

	while (apellido.empty()) {
		cout << "Ingrese el apellido: ";
		cin >> apellido;
		cin.ignore();
		if (apellido.empty()) {
			cout << "el apellido no puede estar vacio" << endl;
		}
	}

	do {
		cout << "Prioridades (1.- Tercera edad 2.- Embarazadas 3.- Normal)" << endl;
		cout << "Selecciona una prioridad: ";
		cin >> prioridad;
		cin.ignore();
		if (prioridad != 1 && prioridad != 2 && prioridad != 3) {
			cout << "Ingrese una prioridad valida (1, 2, 3)" << endl;
			prioridad = 0; // Reiniciar la prioridad para asegurar que el ciclo continua
		}
	} while (prioridad != 1 && prioridad != 2 && prioridad != 3);

	// Crear un objeto Elector y agregarlo a la lista
	Elector elector(cedula, nombre, apellido);
	insertarElector(elector, prioridad);
};

void Votantes::insertarElector(Elector elector, int electorPrioridad) {
	Elector marca;
	marca.setCedula("$$$$$$");

	// si es el primer elector a registrar o si la prioridad es normal, insertamos al final
	if (electores.VaciaPrioridad() || electorPrioridad == 3) {
		electores.InsertarNodoColaPrioridad(elector, electorPrioridad);
		cout << "Elector registrado" << endl;
	} else {
		Elector elecAux;
		int elecPrioAux;
		bool realizado = false;

		electores.InsertarNodoColaPrioridad(marca, 777);

		do {

			electores.RemoverNodoColaPrioridad(elecAux, elecPrioAux);

			// CODIGO QUE SE EJECUTA PARA CADA ITERACION DE ELECTOR
			// ⬇️⬇️⬇️⬇️⬇️⬇️⬇️

			// buscamos el primer elector de la prioridad siguiente para registrar antes el nuevo elector
			if (elecPrioAux > electorPrioridad && realizado == false) {
				electores.InsertarNodoColaPrioridad(elector, electorPrioridad);
				realizado = true;
				cout << "Elector registrado" << endl;
			}

			// ⬆️⬆️⬆️⬆️⬆️⬆️⬆️
			// FIN DEL CODIGO QUE SE EJECUTA PARA CADA ITERACION DE ELECTOR

			if (elecAux.getCedula() != marca.getCedula()) {
				electores.InsertarNodoColaPrioridad(elecAux, elecPrioAux);
			} else if (elecAux.getCedula() == marca.getCedula()) {
				break;
			}

		} while (true);

		if (!realizado) {
			cout << "No se ha registrado el elector." << std::endl;
		}
	}
}

void Votantes::MostrarElectores() {
	nodoPrioridad<Elector> *actual = electores.ObtPrimeroPrioridad();
	if (!actual) {
		cout << "No hay electores inscritos en la cola." << endl;
		return;
	}

	cout << "Electores inscritos: \n"
	     << endl;
	while (actual) {
		Elector electorActual = electores.ObtInfoPrioridad(actual);
		electorActual.mostrarInfo(electores.ObtPrioridad(actual));
		actual = electores.ObtProxPrioridad(actual);
	}
}

void Votantes::CargarDatos() {
	string dato, urlArchivo = "electores.txt";
	fstream archivo;
	archivo.open(urlArchivo.c_str());

	int cont = 0; // Declaramos un contador para llevar el control de la estructura de archivo
	auto *elector = new Elector();
	int electorPrioridad = 3;
	while (archivo >> dato) {
		// leemos cada palabra del archivo y la asignamos al dato.
		cont++;
		// dependiendo de la estructura que se lleve, se asigna el dato al atributo
		if (cont % 5 == 1) {
			elector->setCedula(dato);
		}
		if (cont % 5 == 2) {
			elector->setNombre(dato);
		}
		if (cont % 5 == 3) {
			elector->setApellido(dato);
		}
		if (cont % 5 == 4) {
			electorPrioridad = stoi(dato);
		}
		if (dato == ";") {
			// al encontrar un ; en el archivo registra el elector
			insertarElector(*elector, electorPrioridad);
			// elector->mostrarInfo(electorPrioridad);
			elector = new Elector();
			electorPrioridad = 3;
		}
	}
	archivo.close();
	delete elector;
	cout << "\033[2J\033[1;1H";
	cout << "\nRegistrados " << cont / 5 << " electores." << endl;
}

void Votantes::ListarCandidatos(Lista<Candidato> &cadidatos, bool mostrarVotos) {
	nodo<Candidato> *actual = cadidatos.ObtPrimero();
	int counter = 1;
	if (!actual) {
		cout << "No hay candidatos inscritos en la lista." << endl;
	}
	while (actual) {
		Candidato candidatoActual = cadidatos.ObtInfo(actual);
		string info = to_string(counter) + ". " + candidatoActual.getNombre() + " " + candidatoActual.getApellido() + " - " + candidatoActual.getNombrePartido();
		info += mostrarVotos ? "Votos: " + to_string(candidatoActual.getVotos()) : "";
		cout << info << endl;
		actual = cadidatos.ObtProx(actual);
		counter++;
	}
}

bool Votantes::ProcesarVotantes(Lista<Candidato> candidatos) {
	// Iterar sobre los electores

	nodoPrioridad<Elector> *currentNode = electores.ObtPrimeroPrioridad();
	while (currentNode) {
		Elector currentElector = electores.ObtInfoPrioridad(currentNode);
		// preguntamos si la persona votara o no
		int procesarElector = 0;
		cout << "Desea procesar el voto del ciudadano(a) " << currentElector.getNombre() << " de C.I. " << currentElector.getCedula() << " Si(1) No(2)" << endl;
		cin >> procesarElector;

		int elecciones[5] = {0};
		// en caso de no procesarlo, se lleva a la cola de no votantes
		if (procesarElector != 1) {
			colaNoVotantes.InsertarNodoColaPrioridad(currentElector, electores.ObtPrioridad(currentNode));
			currentNode = electores.ObtProxPrioridad(currentNode);
			continue;
		} else {

			for (int i = 0; i < 5; i++) {
				// mostrar las opciones para los candidatos zzzz
				bool votoCorrecto = false;
				while (!votoCorrecto) {
					nodo<Candidato> *iterator = candidatos.ObtPrimero();
					// iteracion i
					int eleccion;
					cout << "Escoja un candidato, ingresando el indice" << endl;
					ListarCandidatos(candidatos, false);
					cin >> eleccion;

					if (eleccion < 1 ||
					        eleccion == elecciones[0] ||
					        eleccion == elecciones[1] ||
					        eleccion == elecciones[2] ||
					        eleccion == elecciones[3] ||
					        eleccion == elecciones[4]) {
						cout << "Opcion invalida, por favor ingrese un indice valido o un candidato que no haya escogido ya" << endl;
					} else {

						elecciones[i] = eleccion;
						votoCorrecto = true; // se ha ingresado un voto correcto
					}
				}
			}


			// Ahora sumamos los votos

			nodo<Candidato> *iterator = candidatos.ObtPrimero();
			for (int i = 1; i <= candidatos.Contar(); i++) {

				if (i  == elecciones[0] ||
				        i == elecciones[1] ||
				        i == elecciones[2] ||
				        i == elecciones[3] ||
				        i == elecciones[4]) {
					//sumar votos al candidato que coincida

					Candidato c = candidatos.ObtInfo(iterator);
					c.agregarVoto();
					candidatos.AsigInfo(iterator, c);
				}
				iterator = candidatos.ObtProx(iterator);

			}
		}

		cout << "El elector " << currentElector.getNombre() << " ha votado por los siguientes candidatos: " << endl;

		// verificamos que los candidatos tengan sus votos acumulados
		ListarCandidatos(candidatos, true);

		// sacamos el elector actual a una cola separada
		colaVotantes.InsertarNodoCola(currentElector);

		// pasamos al siguiente elector
		currentNode = electores.ObtProxPrioridad(currentNode);
	}
	return true;
}


void Votantes::MostrarMenuReportes() {
	int opcionMenu;
	do {
		cout<<"\n Menu de reportes para los votantes.\n"<<endl;
		cout<<"\t 1. Reporte de votantes por prioridad."<<endl;
		cout<<"\t 2. Reporte de votantes por status."<<endl;
		cout<<"\t 0. Salir."<<endl;
		cin>>opcionMenu;
		switch(opcionMenu) {
			case 0: {
				cout<<"\t Volviendo al menu anterior."<<endl;
				break;
			}
			case 1: {
				ReportePorPrioridad();
				break;
			}
			case 2: {
				ReportePorStatus();
				break;
			}
			default: {
				cout<<"\t Opcion invalida, volviendo al menu de reportes"<<endl;
				break;
			}

		}
	} while(opcionMenu != 0);

}

void Votantes::ReportePorPrioridad() {
	nodoPrioridad<Elector> *actual = electores.ObtPrimeroPrioridad();
	int prioridadSeleccionada;
	int prioridadActual ;
	bool priodadVacia = true;

	if (!actual) {
		cout << "No hay electores inscritos en la cola." << endl;
		return;
	}

	do {
		cout<<"Indique la prioridad que desea ver (1.- Tercera edad 2.- Embarazadas 3.- Normal): "<<endl;
		cin>>prioridadSeleccionada;

		if(prioridadActual > 3 || prioridadActual == 0) {
			cout<<" Opcion Invalidad"<<endl;
		}

	} while(prioridadSeleccionada < 1 || prioridadSeleccionada > 3);

	while (actual) {
		Elector electorActual = electores.ObtInfoPrioridad(actual);
		prioridadActual = electores.ObtPrioridad(actual);

		switch(prioridadActual) {
			case 1: {
				cout<<"3era Edad:\n"<<endl;
				break;
			}
			case 2: {
				cout<<"Embarazadas: \n"<<endl;
				break;
			}
			case 3: {
				cout<<"Normal: \n"<<endl;
				break;
			}
		}


		if(prioridadSeleccionada == prioridadActual) {

			cout<<"\t Nombre del elector:"<<" "<<electorActual.getNombre()<<" "<<electorActual.getApellido()<<endl;
			cout<<"\t Cedula del elector:"<<" "<<electorActual.getCedula()<<" \n"<<endl;
			priodadVacia = false;
		}

		prioridadActual = electores.ObtPrioridad(actual);
		actual = electores.ObtProxPrioridad(actual);
	}

	if(priodadVacia) {
		cout<<" Esta Prioridad no tiene votantes inscritos"<<endl;
	}
}


void Votantes::ReportePorStatus() {
	int statusSeleccionado;
	int prioridadActual = 0;
	int prioridadAuxMensaje = 0;
	nodoPrioridad<Elector> *actual;
	Elector electorActual;

	do {
		cout<<" Indique el status por el que desea ver el reporte (1-Procesados, 2- NO procesados): "<<endl;
		cin>>statusSeleccionado;

		if(statusSeleccionado > 2 || statusSeleccionado == 0) {
			cout<<" Opcion Invalidad"<<endl;
		}

	} while(statusSeleccionado < 1 || statusSeleccionado > 2);

	if(statusSeleccionado == 1) {
		actual = colaVotantes.ObtPrimeroPrioridad();
	} else {
		actual = colaNoVotantes.ObtPrimeroPrioridad();
	}


	if (!actual) {
		if(statusSeleccionado == 1) {
			cout << "No hay electores Procesados en la cola." << endl;

		} else {
			cout << "No hay electores NO Procesados en la cola." << endl;
		}
		return;
	}

	while (actual) {

		if(statusSeleccionado == 1) {
			electorActual = colaVotantes.ObtInfoPrioridad(actual);
			prioridadActual = colaVotantes.ObtPrioridad(actual);
		} else {
			electorActual = colaNoVotantes.ObtInfoPrioridad(actual);
			prioridadActual = colaNoVotantes.ObtPrioridad(actual);
		}


		if(prioridadActual != prioridadAuxMensaje) {
			switch(prioridadActual) {
				case 1: {
					cout<<"3era Edad:\n"<<endl;
					break;
				}
				case 2: {
					cout<<"Embarazadas: \n"<<endl;
					break;
				}
				case 3: {
					cout<<"Normal: \n"<<endl;
					break;
				}
			}
		}

		cout<<"\t Nombre del elector:"<<" "<<electorActual.getNombre()<<" "<<electorActual.getApellido()<<endl;
		cout<<"\t Cedula del elector:"<<" "<<electorActual.getCedula()<<" \n"<<endl;


		if(statusSeleccionado == 1) {
			prioridadAuxMensaje = colaVotantes.ObtPrioridad(actual);
			actual = colaVotantes.ObtProxPrioridad(actual);
		} else {
			prioridadAuxMensaje = colaNoVotantes.ObtPrioridad(actual);
			actual = colaNoVotantes.ObtProxPrioridad(actual);
		}
	}

}


