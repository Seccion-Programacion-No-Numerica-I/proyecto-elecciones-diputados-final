#include "Candidato.h"
#include "Inscripcion.h"
#include <iostream>

using namespace std;

int main() {
    Inscripcion inscripcion;
    //inscripcion.mensaje();
    int opcionInicial;
    string cedEliminar;

    // Menu inicial
    cout << "Bienvenido al sistema de gestion de elecciones." << endl;
    cout << "1. Entrar al sistema de gestion de candidatos" << endl;
    cout << "2. Salir" << endl;
    cout << "Elige una opcion: ";
    cin >> opcionInicial;
    cin.ignore(); // Limpiar el buffer de entrada

    if (opcionInicial == 1) {
        int opcion;
        do {
            cout << "\n--- Menu de gestion de candidatos ---" << endl;
            cout << "1. Registrar candidato" << endl;
            cout << "2. Mostrar candidatos" << endl;
            cout << "3. Buscar candidato" << endl;
            cout << "4. Modificar candidato" << endl;
            cout << "5. Eliminar candidato" << endl;
            cout << "6. Resumen Inscripcion" << endl;
            cout << "7. Salir" << endl;
            cout << "Elige una opcion: ";
            cin >> opcion;
            cin.ignore(); // Limpiar el buffer de entrada

            switch(opcion) {
                case 1: {
                    string cedula, nombre, apellido;
                    int idPartido;

                    cout << "Cedula del candidato: ";
                    getline(cin, cedula);
                    cout << "Nombre del candidato: ";
                    getline(cin, nombre);
                    cout << "Apellido del candidato: ";
                    getline(cin, apellido);
                    cout << "ID del Partido del candidato: ";
                    cin >> idPartido;


                    Candidato candidato(cedula, nombre, apellido, idPartido);
                    cout << "Registrando candidato: " << candidato.getCedula() << ", " << candidato.getNombre() << ", " << candidato.getApellido() << ", " << candidato.getNombrePartido()<< endl;


                    if(inscripcion.verificarDisponibilidad(candidato)){
                        inscripcion.RegistrarCandidato(candidato);
                        cout << "Candidato registrado exitosamente." << endl; // Mensaje de depuración
                        break;
                    } else {
                        cout << "No se registro el candidato" << endl; // Mensaje de depuración
                        break;
                    }

                }
                case 2:
                    inscripcion.MostrarCandidatos();
                    break;
                case 3: {

                    string cedulaCandidato;
                    cout << "Ingrese la cedula del candidato" << endl;
                    //cin.ignore();
                    getline(cin, cedulaCandidato);

                    Candidato candi = inscripcion.BuscarCandidato(cedulaCandidato);
                    if (!candi.getNombre().empty())
                    {
                        cout << "Candidato encontrado: " << endl;
                        cout << " Cedula: " << candi.getCedula();
                        cout << " Nombre Completo: " << candi.getNombre() << " " << candi.getApellido();
                        cout << " Partido: " << candi.getNombrePartido();
                        cout << " Status: " << candi.getStatus();
                    }
                    break;

                }
                case 4: {
                	string cedulaModificar;
                	cout<<"Ingrese la cedula del candidato a modificar: "; cin>>cedulaModificar;
                	inscripcion.ModificarCandidato(cedulaModificar);
					break;
                }

                case 5:
                    cout << "Ingrese la cedula del candidato a eliminar: ";
                    cin >> cedEliminar;
                    cin.ignore(); // Limpiar el buffer de entrada
                    inscripcion.EliminarCandidato(cedEliminar);
                    break;

                case 6:
                    inscripcion.ReporteGeneral();
                    break;

                case 7:
                    cout << "Saliendo del sistema de gestion de candidatos." << endl;
                    break;

                default:
                    cout << "Opcion no valida. Intenta de nuevo." << endl;
            }
        } while (opcion != 7);
    } else if (opcionInicial == 2) {
        cout << "Saliendo del programa." << endl;
    } else {
        cout << "Opcion no valida. Terminando el programa." << endl;
    }

    system("pause");
    return 0;
}
