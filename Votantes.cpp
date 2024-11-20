//
// Created by arnal on 18/11/2024.
//

#include "Votantes.h"

#include <fstream>
#include <iostream>
#include <bits/parse_numbers.h>

Votantes::Votantes() {}

void Votantes::RegistrarElector()
{
	cout << "\t Registro de Elector\n" << endl;
	string cedula, nombre, apellido;
	int prioridad = 0;

		while (cedula.empty()) {
			cout << "Ingrese la cedula: "; cin >> cedula; cin.ignore();
			if (cedula.empty()) { cout << "La cedula no puede estar vacia" << endl; }
		}

		while (nombre.empty()) {
			cout << "Ingrese el nombre: "; cin >> nombre; cin.ignore();
			if (nombre.empty()) { cout << "el nombre no puede estar vacio" << endl; }
		}

		while (apellido.empty()) {
			cout << "Ingrese el apellido: "; cin >> apellido; cin.ignore();
			if (apellido.empty()) { cout << "el apellido no puede estar vacio" << endl; }
		}

		do {
			cout << "Prioridades (1.- Normal 2.- Embarazadas 3.- Tercera Edad)" << endl;
			cout << "Selecciona una prioridad: "; cin >> prioridad; cin.ignore();
			if (prioridad != 1 && prioridad != 2 && prioridad != 3)
			{
				cout << "Ingrese una prioridad valida (1, 2, 3)" << endl;
				prioridad = 0; // Reiniciar la prioridad para asegurar que el ciclo continua
			}
		} while (prioridad != 1 && prioridad != 2 && prioridad != 3);

		// Crear un objeto Elector y agregarlo a la lista
		Elector elector(cedula, nombre, apellido, prioridad);
		insertarElector(elector);
};

void Votantes::insertarElector(Elector elector)
{
	Elector marca;
	marca.setCedula("$$$$$$");

	// si es el primer elector a registrar o si la prioridad es normal, insertamos al final
	if (electores.Vacia() || elector.getPrioridad() == 1) {
		electores.InsFinal(elector);
		cout << "Elector registrado" << endl;
	}
	else
	{
		Elector elecAux;
		bool realizado = false;

		electores.InsertarNodoCola(marca);

		while (true)
		{

			electores.RemoverNodoCola(elecAux);

			if (elecAux.getCedula() == marca.getCedula()) { break; }

			// CODIGO QUE SE EJECUTA PARA CADA ITERACION DE ELECTOR
			// ⬇️⬇️⬇️⬇️⬇️⬇️⬇️

			// buscamos el primer elector de la prioridad siguiente para registrar antes el nuevo elector
			if (elecAux.getPrioridad() < elector.getPrioridad() && realizado == false) {
				electores.InsFinal(elector);
				realizado = true;
				cout << "Elector registrado" << endl;
			}

			// ⬆️⬆️⬆️⬆️⬆️⬆️⬆️
			// FIN DEL CODIGO QUE SE EJECUTA PARA CADA ITERACION DE ELECTOR

			electores.InsertarNodoCola(elecAux);
		}

		if (!realizado)
		{
			cout << "No se ha registrado el elector." << std::endl;
		}
	}
}

void Votantes::MostrarElectores()
{
	nodo<Elector> *actual = electores.ObtPrimero();
	if (!actual) { cout << "No hay electores inscritos en la cola." << endl; return; }

	cout << "Electores inscritos: \n" << endl;
	while (actual)
	{
		Elector electorActual = electores.ObtInfo(actual);
		electorActual.mostrarInfo();
		actual = electores.ObtProx(actual);
	}
}

void Votantes::CargarDatos() {
	string dato, urlArchivo  = "electores.txt";
	fstream archivo; archivo.open(urlArchivo.c_str());

	int cont = 0; // Declaramos un contador para llevar el control de la estructura de archivo
	auto *elector = new Elector();
	while (archivo >> dato) { // leemos cada palabra del archivo y la asignamos al dato.
		cont ++;
		// dependiendo de la estructura que se lleve, se asigna el dato al atributo
		if (cont % 5 == 1) { elector->setCedula(dato); }
		if (cont % 5 == 2) { elector->setNombre(dato); }
		if (cont % 5 == 3) { elector->setApellido(dato); }
		if (cont % 5 == 4) { elector->setPrioridad(stoi(dato)); }
		if (dato == ";") { // al encontrar un ; en el archivo registra el elector
			insertarElector(*elector);
			elector->mostrarInfo();
			elector = new Elector();
		}
	}
	archivo.close();
	delete elector;
}




