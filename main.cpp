#include "Candidato.h"
#include "Inscripcion.h"
#include "Libreria/Validaciones.h"
#include <iostream>
#include <string>

#include "Votantes.h"

using namespace std;

int main() {
	Inscripcion inscripcion;
	Votantes votantes;

	int opcionInicial, statusVotacion = 0;
	;

	do {
		// Menu inicial
		cout << "\033[H\033[2J"; // mantiene el menu en la parte de arriba de la terminal
		cout << "\nBienvenido al sistema de gestion de elecciones." << endl;
		cout << "1. Entrar al sistema de gestion de candidatos" << endl;
		cout << "2. Entrar al modulo votantes" << endl;
		cout << "3. Salir" << endl;
		cout << "Elige una opcion:";
		cin >> opcionInicial;
		cin.ignore(); // Limpiar el buffer de entrada

		if (opcionInicial == 1 && statusVotacion != 3) {
			int opcion;
			do {
				cout << "\033[H\033[2J"; // mantiene el menu en la parte de arriba de la terminal

				cout << "\n--- Menu de gestion de candidatos ---" << endl;
				cout << "1. Registrar candidato" << endl;
				cout << "2. Mostrar candidatos" << endl;
				cout << "3. Buscar candidato" << endl;
				cout << "4. Modificar candidato" << endl;
				cout << "5. Eliminar candidato" << endl;
				cout << "6. Resumen Inscripcion" << endl;
				cout << "7. Mostrar Candidatos por Partido" << endl;
				cout << "8. Salir" << endl;
				cout << "9. Cargar Candidatos" << endl;
				cout << "Elige una opcion: ";
				cin >> opcion;
				cin.ignore(); // Limpiar el buffer de entrada

				switch (opcion) {
					case 1: {
						inscripcion.Registrar();
						break;
					}

					case 2: {

						inscripcion.MostrarCandidatos();
						break;
					}

					case 3: {
						std::string cedBuscar;
						while (true) {
							std::cout << "\tIngrese la cedula del candidato: ";
							std::cin >> cedBuscar;
							std::cin.ignore(); // Limpiar el buffer de entrada
							if (!Validaciones::validarCedula(cedBuscar)) {
								cedBuscar.clear(); // Reiniciar la cédula para asegurar que el ciclo continúa
							} else {
								break;
							}
						}
						inscripcion.iterarCandidatos(cedBuscar, 1);
						break;
					}

					case 4: {
						std::string cedulaModificar;
						while (true) {
							std::cout << "\tIngrese la cedula del candidato a modificar: ";
							std::cin >> cedulaModificar;
							std::cin.ignore(); // Limpiar el buffer de entrada
							if (!Validaciones::validarCedula(cedulaModificar)) {
								cedulaModificar.clear(); // Reiniciar la cédula para asegurar que el ciclo continúa
							} else {
								break;
							}
						}
						inscripcion.iterarCandidatos(cedulaModificar, 2);
						break;
					}

					case 5: {
						std::string cedEliminar;
						while (true) {
							std::cout << "\tIngrese la cedula del candidato a eliminar: ";
							std::cin >> cedEliminar;
							std::cin.ignore(); // Limpiar el buffer de entrada
							if (!Validaciones::validarCedula(cedEliminar)) {
								cedEliminar.clear(); // Reiniciar la cédula para asegurar que el ciclo continúa
							} else {
								break;
							}
						}
						inscripcion.iterarCandidatos(cedEliminar, 3);
						break;
					}
					case 6: {
						// inscripcion.ReporteGeneral();
						inscripcion.MostrarReporteCompleto(); // hecho por el equipo del Punto 5 - Reporte
						break;
					}

					case 7: {
						string partido;
						cout << "Ingresa el nombre del partido: ";
						cin >> partido;
						cin.ignore(); // Limpiar el buffer de entrada

						inscripcion.iterarCandidatos(partido, 4);
						// inscripcion.MostrarCandidatosPorPartido(partido);
						break;
					}

					case 8:
						cout << "Saliendo del sistema de gestion de candidatos." << endl;
						opcionInicial = 0;
						break;

					case 9: {
						inscripcion.CargarCandidatos();
						break;
					}

					default:
						cout << "Opcion no valida. Intenta de nuevo." << endl;
				}
				system("pause");
			} while (opcion != 8);
		}

		else if (opcionInicial == 2) {
			int opcion;
			do {
				cout << "\033[H\033[2J"; // mantiene el menu en la parte de arriba de la terminal
				cout << "\nModulo votantes seleccionado\n"
				     << endl;
				cout << "\t 1. Registrar Votante" << endl;
				cout << "\t 2. Cargar Votantes desde archivo" << endl;
				cout << "\t 3. Mostrar Electores inscritos" << endl;
				cout << "\t 4. Eliminar Elector" << endl;
				cout << "\t 5. Procesar Votantes" << endl;
				cout << "\t 6. Listar Ganadores" << endl;
				cout << "\t 7. Reportes" << endl;

				cout << "\t 0. Salir" << endl;

				cout << "\t Elegir una opcion: ";
				cin >> opcion;

				switch (opcion) {
					case 0: {
						cout << "\nSaliendo del Modulo votantes\n"
						     << endl;
						opcionInicial = 0;
						break;
					}
					case 1: {
						if (statusVotacion == 3) {
							cout << "Ya la votacion termino" << endl;
						} else {
							votantes.RegistrarElector();
						}
						break;
					}
					case 2: {
						if (statusVotacion == 3) {
							cout << "Ya la votacion termino" << endl;
						} else {
							cout << "\t Cargando datos desde archivo \n" << endl;
							votantes.CargarDatos();
						}
						break;
					}

					case 3: {
						if (statusVotacion == 3) {
							cout << "Ya la votacion termino" << endl;
						} else {
							votantes.MostrarElectores();
						}
						break;
					}
					case 4: {
						if (statusVotacion == 3) {
							cout << "Ya la votacion termino" << endl;
						} else {
							string cedulaAEliminar;
							cout<<"\t Ingrese la Cedula del votante a eliminar: \n"<<endl;
							cin>>cedulaAEliminar;
							votantes.EliminarVotante(cedulaAEliminar);
						}

						break;
					}
					case 5: {
						if (statusVotacion == 3) {
							cout << "Ya la votacion termino" << endl;
						} else {

							statusVotacion = votantes.MenuVotacion(inscripcion.getCandidatos());
						}
						break;
					}
					case 6: {
						votantes.listarGanadores(inscripcion.getCandidatos());
						break;
					}
					case 7: {
						votantes.MostrarMenuReportes(inscripcion.getCandidatos());
						break;
					}
					default: {
						cout << "Opcion no valida. Intenta de nuevo." << endl;
					}
				}

				system("pause");
			} while (opcion != 0);
		} else if(opcionInicial == 1 && statusVotacion == 3){
			cout << "Ya la votacion termino" << endl;
			opcionInicial = 0;
		}

	} while (opcionInicial == 1 || opcionInicial == 2 || opcionInicial == 0);

	if (opcionInicial == 3) {
		cout << "Saliendo del programa." << endl;
	}

	else {
		cout << "Opcion no valida. Terminando el programa." << endl;
	}

	system("pause");
	return 0;
}
// prueba de permisos 2
