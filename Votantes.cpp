//
// Created by arnal on 18/11/2024.
//

#include "Votantes.h"
#include <fstream>
#include <iostream>
#include <bits/parse_numbers.h>
#include "Libreria/Validaciones.h"

Votantes::Votantes() {}

void Votantes::RegistrarElector() {
    std::cout << "\t Registro de Elector\n" << std::endl;
    std::string cedula, nombre, apellido;
    int prioridad = 0;

    while (true) {
        std::cout << "Ingrese la cedula: ";
        std::getline(std::cin, cedula);
        if (!Validaciones::validarCedula(cedula)) {
            std::cout << "Cedula no valida. Debe tener entre 6 y 9 digitos y no debe contener espacios." << std::endl;
            cedula.clear(); // Reiniciar la cédula para asegurar que el ciclo continúa
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Ingrese el nombre: ";
        std::getline(std::cin, nombre);
        if (!Validaciones::validarNombre(nombre)) {
            std::cout << "Nombre no valido. Debe tener entre 2 y 20 caracteres y no debe contener numeros, caracteres especiales ni espacios." << std::endl;
            nombre.clear(); // Reiniciar el nombre para asegurar que el ciclo continúa
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Ingrese el apellido: ";
        std::getline(std::cin, apellido);
        if (!Validaciones::validarNombre(apellido)) {
            std::cout << "Apellido no valido. Debe tener entre 2 y 20 caracteres y no debe contener numeros, caracteres especiales ni espacios." << std::endl;
            apellido.clear(); // Reiniciar el apellido para asegurar que el ciclo continúa
        } else {
            break;
        }
    }

    do {
        std::cout << "Prioridades (1.- Tercera edad 2.- Embarazadas 3.- Normal)" << std::endl;
        std::cout << "Selecciona una prioridad: ";
        std::cin >> prioridad;
        std::cin.ignore(); // Limpiar el buffer de entrada
        if (prioridad != 1 && prioridad != 2 && prioridad != 3) {
            std::cout << "Ingrese una prioridad valida (1, 2, 3)" << std::endl;
            prioridad = 0; // Reiniciar la prioridad para asegurar que el ciclo continua
        }
    } while (prioridad != 1 && prioridad != 2 && prioridad != 3);

    // Crear un objeto Elector y agregarlo a la lista
    Elector elector(cedula, nombre, apellido);
    if (electores.InsertarNodoOrdenado(elector, prioridad)) {
        std::cout << "\n Registro Exitoso \n" << std::endl;
    } else {
        std::cout << "\n Fallo al registrar \n" << std::endl;
    }
}


void Votantes::MostrarElectores()
{
	nodoPrioridad<Elector> *actual = electores.ObtPrimeroPrioridad();
	if (!actual)
	{
		cout << "No hay electores inscritos en la cola." << endl;
		return;
	}

	cout << "Electores inscritos: \n"
		 << endl;
	while (actual)
	{
		Elector electorActual = electores.ObtInfoPrioridad(actual);
		electorActual.mostrarInfo(electores.ObtPrioridad(actual));
		actual = electores.ObtProxPrioridad(actual);
	}
}

void Votantes::CargarDatos()
{
	string dato, urlArchivo = "electores.txt";
	fstream archivo;
	archivo.open(urlArchivo.c_str());

	int cont = 0; // Declaramos un contador para llevar el control de la estructura de archivo
	auto *elector = new Elector();
	int electorPrioridad = 3;
	while (archivo >> dato)
	{
		// leemos cada palabra del archivo y la asignamos al dato.
		cont++;
		// dependiendo de la estructura que se lleve, se asigna el dato al atributo
		if (cont % 5 == 1)
		{
			elector->setCedula(dato);
		}
		if (cont % 5 == 2)
		{
			elector->setNombre(dato);
		}
		if (cont % 5 == 3)
		{
			elector->setApellido(dato);
		}
		if (cont % 5 == 4)
		{
			electorPrioridad = stoi(dato);
		}
		if (dato == ";")
		{ // al encontrar un ; en el archivo registra el elector

			electores.InsertarNodoOrdenado(*elector, electorPrioridad);
			elector = new Elector();
			electorPrioridad = 3;
		}
	}
	archivo.close();
	delete elector;
	// cout << "\033[H\033[2J";
	cout << "\nRegistrados " << cont / 5 << " electores." << endl;
}

void Votantes::ListarCandidatos(Lista<Candidato> &cadidatos, bool mostrarVotos)
{
	nodo<Candidato> *actual = cadidatos.ObtPrimero();
	int counter = 1;
	// if (!actual)
	// {
	// 	cout << "No hay candidatos inscritos en la lista." << endl;

	// }
	while (actual)
	{
		Candidato candidatoActual = cadidatos.ObtInfo(actual);
		string info = to_string(counter) + ". " + candidatoActual.getNombre() + " " + candidatoActual.getApellido() + " - " + candidatoActual.getNombrePartido();
		info += mostrarVotos ? "Votos: " + to_string(candidatoActual.getVotos()) : "";
		cout << info << endl;
		actual = cadidatos.ObtProx(actual);
		counter++;
	}
}

bool Votantes::procesarVoto(Lista<Candidato> &candidatos, int posicion)
{
	nodo<Candidato> *actual = candidatos.ObtPrimero();

	for (int i = 1; i < posicion; i++)
	{
		actual = candidatos.ObtProx(actual);
	}

	if (actual)
	{

		Candidato c = candidatos.ObtInfo(actual);
		c.agregarVoto();
		candidatos.AsigInfo(actual, c);
		return true;
	}

	return false;
}


bool Votantes::ProcesarVotantes(Lista<Candidato> &candidatos)

{
	


// validar cuantos votantes faltan
	// si ya no quedan electores devolverse al menu

	if (electores.VaciaPrioridad()) {
		cout << "No quedan electores en la lista por procesar" << endl; 
		return false; 
	}
	
	// Si quedan electores:
	// Iterar sobre los electores
	int cantidad_candidatos = candidatos.Contar();


	if (cantidad_candidatos < 25)
	{
		cout << "Es necesario inscribir 25 candidatos para poder realizar el proceso de votación." << endl;
		return false;
	}

	
	nodoPrioridad<Elector> *currentNode = electores.SacarTope();

	while (currentNode)
	{
		Elector currentElector = electores.ObtInfoPrioridad(currentNode);
		cout << "Procesando a: " << currentElector.getNombre() << endl;
		int votos[5] = {0};

		// procesamos su voto
		bool votando = true;
		int cantidad_votos = 1;

		while (votando)
		{

			int indiceVoto = 0;
			cout << "Los Candidatos: " << endl;
			ListarCandidatos(candidatos, true);
			cout << "Ingrese su voto nro " << cantidad_votos << ": ";
			cin >> indiceVoto;

			// validacion de indice valido
			if ( indiceVoto < 1 || indiceVoto > cantidad_candidatos) 
			{
				cout << "Índice de candidato no válido. Intente de nuevo." << endl;
                continue; 
			}
			// validacion voto repetido
			            bool votoRepetido = false;
            for (int i = 0; i < cantidad_votos; i++)
            {
                if (votos[i] == indiceVoto)
                {
                    votoRepetido = true;
                    break;
                }
            }

            if (votoRepetido)
            {
                cout << "Ya has votado por este candidato. Intenta con otro." << endl;
                continue; // Volver a pedir el voto
            }

			//registrar el voto

			votos[cantidad_votos - 1] = indiceVoto;

			cout << "Voto: " << votos[cantidad_votos - 1] << endl; 

			procesarVoto(candidatos, indiceVoto);

			ListarCandidatos(candidatos, true);

			cantidad_votos++;
	
			if (cantidad_votos <= 5)
            {
                int r; 
                cout << "Deseas votar por otro candidato? Si (1) No (2)" << endl;
                cin >> r;
                votando = (r == 1);
            }
            else
            {
                cout << "Agotaste tus votos" << endl;
                votando = false; // No se puede votar más
            }

			
			
		}

		// colocamos al elector en la lista respectiva
		
		int p = colaVotantes.ObtPrioridad(currentNode); 
		colaVotantes.InsertarNodoColaPrioridad(currentElector, p); 

		MostrarElectores(); 

		// preguntamos si queremos proseguir con otro elector
		int procesarSiguiente; 
		cout << "Desea procesar el siguiente elector: " << electores.ObtInfoPrioridad(electores.ObtProxPrioridad(currentNode)).getNombre() << " Si (1) No (2)" << endl; 
		cin >> procesarSiguiente; 

	// si no se quiere seguir procesando nos vamos al menu anterior
		if (procesarSiguiente != 1) {
			cout << "Saliendo al menu..." << endl; 
			return true; 
		} 
		// pasamos al siguiente elector
		currentNode = electores.SacarTope();
	}
	return true;
}


int Votantes::MenuVotacion(Lista<Candidato> &candidatos) {

	// implementar Menu votantes
// Empezar || Continuar Votacion
// Cerrar Votacion
			int status; 
			int opcion; 
           do {
                // cout << "\033[H\033[2J"; // mantiene el menu en la parte de arriba de la terminal
            cout << "\nVotacion\n" << endl;
            cout << "\t 1. Empezar | Continuar Votacion" << endl;
            cout << "\t 0. Cerrar Votacion" << endl;

            cout << "\t Elegir una opcion "; cin >> opcion;

                switch(opcion) {
                    case 1: {
                        ProcesarVotantes(candidatos); 
						status = 2; 
                        break;
                    }
                    case 0: {
                        opcion = 0; 
						status = 3;
                        break;
                    }
                    default: {
                        cout << "Opcion no valida. Intenta de nuevo." << endl;
                    }
                }

            system("pause");
            } while (opcion != 0);

	return status; 

}


void Votantes::EliminarVotante(string cedulaVotante) {
	nodoPrioridad<Elector> *actual = electores.ObtPrimeroPrioridad();
	Lista<Elector> colaAux;
	Elector electorActual;
	int prioridadActual ;
	bool mostrarMsjVotanteNoExistente = true;
	int preguntaVerificacion;

	if (!actual) {
		cout << "No hay electores en la cola." << endl;
		return;
	}

	do {
		cout<<"\t Esta seguro de eliminar al elector con la cedula: "<<cedulaVotante<<" ? (Si=1 No=2)"<<endl;
		cin>> preguntaVerificacion;
		if(preguntaVerificacion != 1 && preguntaVerificacion != 2) {
			cout<<"\t Opcion invalidad."<<endl;
		}
	} while(preguntaVerificacion != 1 && preguntaVerificacion != 2);

	if(preguntaVerificacion == 2) {
		return;
	}

	//Se recorre la lista "electores" en busqueda del elector que coincida con la cedula que introdujo el usuario.
	while(actual) {
		electorActual = electores.ObtInfoPrioridad(actual);
		prioridadActual = electores.ObtPrioridad(actual);

		//Se verifica en cada iteracion en busqueda de la cedula requerida
		if(cedulaVotante == electorActual.getCedula()) {
			//en caso de encontrarla se inserta el elector en la lista de eliminados
			colaEliminados.InsertarNodoColaPrioridad(electorActual,prioridadActual);
			mostrarMsjVotanteNoExistente = false;
		} else {
			//en caso contrario se inserta en una lista aux
			colaAux.InsertarNodoColaPrioridad(electorActual,prioridadActual);
		}
		// se procede a eliminar al elector de la lista "electores"
		electores.RemoverNodoColaPrioridad(electorActual,prioridadActual);

		actual = electores.ObtProxPrioridad(actual);
	}

	actual = colaAux.ObtPrimeroPrioridad();

	// se recorre la lista aux para insertar a los electores en la lista "electores" SIN el elector eliminado en caso de que lo encuentre.
	while(actual) {
		electorActual = colaAux.ObtInfoPrioridad(actual);
		prioridadActual = colaAux.ObtPrioridad(actual);

		electores.InsertarNodoColaPrioridad(electorActual,prioridadActual);

		actual = colaAux.ObtProxPrioridad(actual);
	}

	if(mostrarMsjVotanteNoExistente) {
		cout<<"No existen un votante con esta cedula: "<<cedulaVotante<<endl;
	} else {
		cout<<"\t el Votante con la cedula: "<<cedulaVotante<<" ha sido eliminado."<<endl;
	}

	//se procede a usar el destructor.
	colaAux.~Lista();
	return;
}


void Votantes::MostrarMenuReportes(Lista<Candidato>& candidatos) {
	int opcionMenu;
	do {
		cout<<"\n Menu de reportes para los votantes.\n"<<endl;
		cout<<"\t 1. Reporte de votantes."<<endl;
		cout<<"\t 2. Reporte de votantes eliminados."<<endl;
		cout<<"\t 3. Reporte de votantes excluidos."<<endl;
		cout<<"\t 4. Reporte de lista de excrutinio."<<endl;
		cout<<"\t 0. Salir."<<endl;
		cin>>opcionMenu;
		switch(opcionMenu) {
			case 0: {
				cout<<"\t Volviendo al menu anterior."<<endl;
				break;
			}
			case 1: {
				ReporteDeVotantes();
				break;
			}
			case 2: {
				ReporteEliminados();
				break;
			}
			case 3:{
				ReporteExcluidos();
				break;
			}
			case 4:{
				ReporteExcrutinio(candidatos);
				break;
			}
			default: {
				cout<<"\t Opcion invalida, volviendo al menu de reportes"<<endl;
				break;
			}

		}
	} while(opcionMenu != 0);

}

void Votantes::ReporteDeVotantes() {
	int prioridadActual;
	int prioridadAnterior = 0;
	Elector electorActual;


	nodoPrioridad<Elector> *actual =colaVotantes.ObtPrimeroPrioridad();

	if (!actual) {
		cout << "No hay electores inscritos en la cola." << endl;
		return;
	}

	while (actual) {
		electorActual = colaVotantes.ObtInfoPrioridad(actual);
		prioridadActual = colaVotantes.ObtPrioridad(actual);

		if(prioridadAnterior != prioridadActual) {
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

		prioridadAnterior = prioridadActual;
		prioridadActual = colaVotantes.ObtPrioridad(actual);
		actual = colaVotantes.ObtProxPrioridad(actual);

	}

}


void Votantes::ReporteEliminados() {
	nodoPrioridad<Elector> *actual = colaEliminados.ObtPrimeroPrioridad();
	Elector electorActual;
	int prioridadActual;

	if (!actual) {
		cout << "No hay electores Procesados en la cola." << endl;
		return;
	}

	while(actual) {
		electorActual = colaEliminados.ObtInfoPrioridad(actual);
		prioridadActual = colaEliminados.ObtPrioridad(actual);

		electorActual.mostrarInfo(prioridadActual);

		prioridadActual = colaEliminados.ObtPrioridad(actual);
		actual = colaEliminados.ObtProxPrioridad(actual);
	}
}

void Votantes::ReporteExcluidos() {
	nodoPrioridad<Elector> *actual = electores.ObtPrimeroPrioridad();
	if (!actual) {
		cout << "No hay electores Excluidos." << endl;
		return;
	}

	cout<<"Electores Excluidos: "<<endl;
	while (actual) {
		Elector electorActual = electores.ObtInfoPrioridad(actual);
		electorActual.mostrarInfo(electores.ObtPrioridad(actual));
		actual = electores.ObtProxPrioridad(actual);
	}
}

void Votantes::ReporteExcrutinio(Lista<Candidato>& candidatos){
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

		cout<<" "<<partidos[i]<<":"<<endl;

		nodo<Candidato> *actualCandidato = candidatos.ObtPrimero();
		while (actualCandidato) {
			Candidato cand = candidatos.ObtInfo(actualCandidato);
			if (i == cand.getIdPartido() - 1) {

				string nombreCompleto = cand.getNombre() + " " + cand.getApellido();
				//cout << " " << cont << ".";
				cout << " " << cont <<"-) "<< nombreCompleto << endl;
				cout << " C.I: " << cand.getCedula() << endl;
				cout << " Numero de votos: "<<cand.getVotos()<<endl;
				cout << "\n";
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

void Votantes::listarGanadores(Lista<Candidato>& candidatos)
{
	Lista<Candidato> ganadores;

	nodo<Candidato> *actual = candidatos.ObtPrimero();

	// ITERAMOS LA LISTA DE CANDIDATOS
	while (actual)
	{
		if (ganadores.Vacia())
		{
			ganadores.InsComienzo(candidatos.ObtInfo(actual));
		}
		else
		{ // VACIAMOS
			nodo<Candidato> *aux1 = ganadores.ObtPrimero();
			auto *aux2 = candidatos.ObtProx(aux1);

			// ITERAMOS LA LISTA DE GANADORES PARA IR VACIANDO LOS CANDIDATOS POR ORDEN DE VOTOS
			while (aux1)
			{
				if (candidatos.ObtInfo(actual).getVotos() >= candidatos.ObtInfo(aux1).getVotos())
				{

					ganadores.InsComienzo(candidatos.ObtInfo(actual));
					break;
				}
				else if (aux2 == NULL || candidatos.ObtInfo(actual).getVotos() >= candidatos.ObtInfo(aux2).getVotos())
				{
					ganadores.InsDespues(aux1, candidatos.ObtInfo(actual));
					break;
				}

				aux1 = aux2;
				aux2 = candidatos.ObtProx(aux1);
			}
		}
		actual = candidatos.ObtProx(actual);
	}

	// MOSTRAMOS LOS GANADORES
	if (!ganadores.Vacia())
	{
		int posicion = 1;

		nodo<Candidato> *ganador = ganadores.ObtPrimero();

		std::cout << "Candidatos electos: \n"
				  << std::endl;
		while (ganador && posicion <= 15)
		{
			Candidato ganadorActual = ganadores.ObtInfo(ganador);

			if (ganadorActual.getStatus() == "ACTIVO")
			{
				cout << "\t\tPosicion: " << posicion;
				cout << " - Votos: " << ganadorActual.getVotos() << "\n"
					 << endl;
				cout << "\t Candidato " << ganadorActual.getNombre();
				cout << " " << ganadorActual.getApellido();
				cout << " - Partido " << ganadorActual.getNombrePartido()
					 << endl;
				cout << "\t------------------------------------------------- \n"
					 << endl;

				posicion++;
			}

			ganador = ganadores.ObtProx(ganador);
		}
	}
}