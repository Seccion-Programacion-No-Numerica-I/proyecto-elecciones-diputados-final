#include "Inscripcion.h"
#include <iostream>
#include <fstream>
#include "Validaciones.h"
#include <iostream>
#include <string>

Inscripcion::Inscripcion() {}

bool Inscripcion::verificarDisponibilidad(Candidato cand)
{

	// falta verificar que el candidato no este inscrito

	if (cand.getIdPartido() < 0 || cand.getIdPartido() > 5)
	{
		std::cout << "ID de partido no valido." << std::endl;
		return false;
	}
	if (candidatosPorPartido[cand.getIdPartido() - 1] >= 5)
	{
		std::cout << "El partido ya tiene 5 candidatos inscritos." << std::endl;
		return false;
	}
	return true;
}

void Inscripcion::CargarCandidatos()
{
	string dato, urlArchivo = "candidatos.txt";
	fstream archivo;
	archivo.open(urlArchivo.c_str());

	int cont = 0; // Declaramos un contador para llevar el control de la estructura de archivo
	auto *candidato = new Candidato();
	// int partido = 1;
	while (archivo >> dato)
	{
		// leemos cada palabra del archivo y la asignamos al dato.
		cont++;
		// dependiendo de la estructura que se lleve, se asigna el dato al atributo
		if (cont % 6 == 1)
		{
			candidato->setCedula(dato);
		}
		if (cont % 6 == 2)
		{
			candidato->setNombre(dato);
		}
		if (cont % 6 == 3)
		{
			candidato->setApellido(dato);
		}
		if (cont % 6 == 4)
		{
			int partido = std::stoi(dato);
			candidato->setIdPartido(partido);
		}
		if (cont % 6 == 5)
		{
			int votos = std::stoi(dato);
			candidato->setVotos(votos);
		}
		if (dato == ";")
		{ // al encontrar un ; en el archivo registra el candidato

			candidato->setStatus("ACTIVO");	 // el candidato esta activo
			candidato->mostrarInformacion(); // muestra la informacion del candidato
			candidatos.InsertarNodoCola(*candidato);
			// candidatosPorPartido[partido - 1]++;
			// insertamos el candidato en la cola
			candidato = new Candidato();
		}
	}
	archivo.close();
	delete candidato;
	std::cout << "\033[H\033[2J";
	std::cout << "\nRegistrados " << cont / 6 << " candidatos." << endl;
}

void Inscripcion::Registrar() {
    int cantidadCandidatos;
    std::cout << "Registro de Candidatos" << std::endl;
    std::cout << "Ingrese la cantidad de candidatos a registrar: ";
    std::cin >> cantidadCandidatos;
    std::cin.ignore(); // Limpiar el buffer

    for (int i = 0; i < cantidadCandidatos; i++) {
        std::string cedula, nombre, apellido;
        int partido = 0;

        std::cout << "\nRegistro del Candidato " << i + 1 << std::endl;

        while (true) {
            std::cout << "Ingrese la cedula: ";
            std::cin >> cedula;
            std::cin.ignore();
            if (!Validaciones::validarCedula(cedula)) {
                cedula.clear(); // Reiniciar la cédula para asegurar que el ciclo continúa
            } else {
                std::cout << "Cedula: " << cedula << " guardada" << std::endl;
                break;
            }
        }

        while (true) {
            std::cout << "Ingrese el nombre: ";
            std::cin >> nombre;
            std::cin.ignore();
            if (!Validaciones::validarNombre(nombre)) {
                nombre.clear(); // Reiniciar el nombre para asegurar que el ciclo continúa
            } else {
                std::cout << "Nombre: " << nombre << " guardado" << std::endl;
                break;
            }
        }

        while (true) {
            std::cout << "Ingrese el apellido: ";
            std::cin >> apellido;
            std::cin.ignore();
            if (!Validaciones::validarNombre(apellido)) {
                apellido.clear(); // Reiniciar el apellido para asegurar que el ciclo continúa
            } else {
                std::cout << "Apellido: " << apellido << " guardado" << std::endl;
                break;
            }
        }

        while (partido < 1 || partido > 5) {
            std::cout << "Ingrese el partido politico: ";
            std::cin >> partido;
            if (std::cin.fail() || partido < 1 || partido > 5) {
                std::cout << "Ingrese un partido valido (1, 2, 3, 4, 5)" << std::endl;
                std::cin.clear(); // Limpiar el estado de error de cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer
                partido = 0; // Reiniciar el partido para asegurar que el ciclo continúa
            }
        }

        // Crear un objeto Candidato y agregarlo a la lista
        Candidato candidato(cedula, nombre, apellido, partido);
        if (verificarDisponibilidad(candidato)) {
            candidato.setStatus("ACTIVO");
            candidatos.InsFinal(candidato);
        }
        // Mostrar la lista de candidatos registrados
        std::cout << "\nLista de Candidatos Registrados:" << std::endl;
        nodo<Candidato> *p = candidatos.ObtPrimero();
        while (p != nullptr) {
            candidatos.ObtInfo(p).mostrarInformacion();
            std::cout << std::endl;
            p = candidatos.ObtProx(p); // Aquí se corrigió el nombre del metodo
        }
        std::cout << "Pulse enter para continuar...";
        std::cin.ignore();
        std::cin.get();
    }
}
void Inscripcion::Eliminar(Candidato cand)
{
	std::cout << "\n\nCandidato Eliminado:\n";
	cand.mostrarInformacion();
	candidatosPorPartido[cand.getIdPartido() - 1]--; // Actualizamos el contador de candidatos por partido

	cout << "Pulse enter para continuar...";
	cin.get();
}

void Inscripcion::Buscar(Candidato cand)
{
	std::cout << "\n\nCandidato Mostrado: \n";
	cand.mostrarInformacion();

	cout << "Pulse enter para continuar...";
	cin.get();
}

Candidato Inscripcion::Modificar(Candidato cand, std::string cedula) {
    Candidato nuevo;
    std::string nuevoNombre, nuevoApellido;
    int idNuevoPartido, opcionEstatus;

    std::cout << "\n\nCandidato encontrado\n" << std::endl;
    cand.mostrarInformacion();

    std::cout << "\tIngrese los nuevos datos para el candidato con cedula " << cand.getCedula() << " \n\n";
    nuevo.setCedula(cedula);

    while (true) {
        std::cout << "Nombre: ";
        std::getline(std::cin, nuevoNombre);
        if (!Validaciones::validarNombre(nuevoNombre)) {
            nuevoNombre.clear(); // Reiniciar el nombre para asegurar que el ciclo continúa
        } else {
            nuevo.setNombre(nuevoNombre);
            break;
        }
    }

    while (true) {
        std::cout << "Apellido: ";
        std::getline(std::cin, nuevoApellido);
        if (!Validaciones::validarNombre(nuevoApellido)) {
            nuevoApellido.clear(); // Reiniciar el apellido para asegurar que el ciclo continúa
        } else {
            nuevo.setApellido(nuevoApellido);
            break;
        }
    }

    while (true) {
        std::string idPartidoStr;
        std::cout << "ID del partido: ";
        std::cin >> idPartidoStr;
        std::cin.ignore(); // Limpiar el buffer de entrada
        if (!Validaciones::validarEntero(idPartidoStr, idNuevoPartido)) {
            std::cout << "ID del partido no valido. Debe ser un número entero." << std::endl;
        } else {
            nuevo.setIdPartido(idNuevoPartido);
            break;
        }
    }

    do {
        std::cout << "Nuevo estatus del candidato: \n\n1.- Activo\n2.-Inactivo\n";
        std::cin >> opcionEstatus;
        switch (opcionEstatus) {
            case 1:
                nuevo.setStatus("ACTIVO");
                break;
            case 2:
                nuevo.setStatus("INACTIVO");
                break;
            default:
                std::cout << "Opcion invalida" << std::endl;
                break;
        }
    } while (opcionEstatus < 1 || opcionEstatus > 2);

    if (verificarDisponibilidad(nuevo)) {
        std::cout << "\nCandidato modificado exitosamente:\n";
        nuevo.mostrarInformacion();

        std::cout << "Pulse enter para continuar...";
        std::cin.ignore();
        std::cin.get();

        return nuevo;
    }
    std::cout << "\nCandidato no modificado\n";

    std::cout << "Pulse enter para continuar...";
    std::cin.get();

    return cand;
}

void Inscripcion::iterarCandidatos(string busqueda, int opcion)
{

	Candidato marca;
	marca.setCedula("$$$$$$");

	if (candidatos.Vacia())
		cout << "No hay candidatos inscritos." << endl;
	else
	{
		Candidato candAux;
		bool encontrado = false;

		candidatos.InsertarNodoCola(marca);

		while (true)
		{

			candidatos.RemoverNodoCola(candAux);

			if (candAux.getCedula() == marca.getCedula())
			{
				break;
			}

			// CODIGO QUE SE EJECUTA PARA CADA ITERACION DE CANDIDATO
			// ⬇️⬇️⬇️⬇️⬇️⬇️⬇️

			if (opcion == 4)
			{
				// mostrar todos los candidatos por partido
				if (candAux.getNombrePartido() == busqueda)
				{
					encontrado = true;
					cout << "Candidato: " << candAux.getNombre() << " " << candAux.getApellido() << endl;
				}
			}

			else if (candAux.getCedula() == busqueda)
			{
				encontrado = true;

				if (opcion == 1)
				{
					Buscar(candAux); // Buscar candidato individual
				}
				if (opcion == 2)
				{
					candAux = Modificar(candAux, busqueda); // Modificar candidato individual
				}
				if (opcion == 3)
				{
					Eliminar(candAux); // Eliminar candidato individual
					continue;
				}
			}

			// ⬆️⬆️⬆️⬆️⬆️⬆️⬆️
			// FIN DEL CODIGO QUE SE EJECUTA PARA CADA ITERACION DE CANDIDATO

			candidatos.InsertarNodoCola(candAux);
		}

		if (!encontrado)
		{
			std::cout << "No se han encontrado un candidato." << std::endl;
		}
	}
}

void Inscripcion::MostrarCandidatos()
{

	nodo<Candidato> *actual = candidatos.ObtPrimero();
	if (!actual)
	{
		std::cout << "No hay candidatos inscritos en la cola." << std::endl;

		cout << "Pulse enter para continuar...";
		cin.get();

		return;
	}

	std::cout << "Candidatos inscritos: \n"
			  << std::endl;
	while (actual)
	{
		Candidato candidatoActual = candidatos.ObtInfo(actual);
		candidatoActual.mostrarInformacion();
		actual = candidatos.ObtProx(actual);
	}

	cout << "Pulse enter para continuar...";
	cin.get();
}

void Inscripcion::ReporteGeneral()
{
	// hay que mostrar a los candidatos por partido
	string partidos[5] = {"A", "B", "C", "D", "E"};

	for (int i = 0; i < 5; i++)
	{
		cout << "Partido :" << partidos[i] << endl;
		cout << "========================" << endl;

		if (candidatos.Vacia())
		{
			cout << "Lista vacía" << endl;
			break; // Termina el metodo si la lista está vacía
		}

		Candidato marca;
		marca.setCedula("$$$");
		candidatos.InsFinal(marca);

		int contador = 0;

		auto it = candidatos.ObtPrimero();

		while (candidatos.ObtInfo(it).getCedula() != marca.getCedula())
		{
			Candidato actual = candidatos.ObtInfo(it);

			if (actual.getNombrePartido() == partidos[i])
			{
				cout << "Candidato: " << actual.getNombre() << " " << actual.getApellido() << endl;
				contador++;
			}

			candidatos.InsFinal(actual);
			it = candidatos.ObtProx(it);
		}

		Candidato primero = candidatos.ObtInfo(it);
		if (primero.getCedula() == marca.getCedula())
		{
			candidatos.EliComienzo(marca);
		}

		if (contador == 0)
		{
			cout << "No hay candidatos que pertenezcan al partido " << partidos[i] << "." << endl;
		}
		cout << "========================" << endl;
	}
	cout << "Pulse enter para continuar...";
	cin.get();
}

void Inscripcion::MostrarReporteCompleto()
{
	int cont = 1;
	// variable auxiliar que utilizamos para almacenar si hay candidatos en algun partido y posteriormente mostar un mensaje.
	bool AuxHayCandidatos = false;
	string partidos[5] = {"A", "B", "C", "D", "E"};

	if (candidatos.Vacia())
	{
		cout << "\n No hay Candidatos inscritos. \n"
			 << endl;

		cout << "Pulse enter para continuar...";
		cin.get();

		return;
	}

	for (int i = 0; i < 5; i++)
	{
		AuxHayCandidatos = false;
		cout << "\n Candidatos Por el partido: " << endl;

		cout << partidos[i] << endl;
		cout << generarEsloganAletorio() << endl;

		nodo<Candidato> *actualCandidato = candidatos.ObtPrimero();
		while (actualCandidato)
		{
			Candidato cand = candidatos.ObtInfo(actualCandidato);
			if (i == cand.getIdPartido() - 1)
			{

				string nombreCompleto = cand.getNombre() + " " + cand.getApellido();
				cout << " " << cont << ".";
				cout << "\n " << nombreCompleto << endl;
				cout << " C.I: " << cand.getCedula() << endl;
				cont++;
				AuxHayCandidatos = true;
			}
			actualCandidato = candidatos.ObtProx(actualCandidato);
		}
		if (!AuxHayCandidatos)
		{
			cout << " No Hay Candidatos Inscritos por el partido " << "\"" << partidos[i] << "\". \n"
				 << endl;
		}
		cont = 1;
	}
	cout << "Pulse enter para continuar...";
	cin.get();
	return;
}

int Inscripcion::generarNumeroAleatorio()
{
	srand(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	// generar numero aleatorio desde el 0 hasta el 9
	int numeroAleatorio = rand() % 10;
	return numeroAleatorio;
}

string Inscripcion::generarEsloganAletorio()
{
	return esloganes[generarNumeroAleatorio()];
}

Lista<Candidato> &Inscripcion::getCandidatos()
{
	return candidatos;
}