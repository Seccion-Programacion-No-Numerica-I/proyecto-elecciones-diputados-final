#include "Candidato.h"
#include "Inscripcion.h"
#include <iostream>

#include "Votantes.h"

using namespace std;

// bubblesort
// Lo qye esta dando peos, segun el debugger:
// terminate called after throwing an instance of 'std::bad_alloc'
//  what():  std::bad_alloc

//Program received signal SIGABRT, Aborted.
//__pthread_kill_implementation (threadid=<optimized out>, signo=signo@entry=6, no_tid=no_tid@entry=0)
//    at ./nptl/pthread_kill.c:44
//44      ./nptl/pthread_kill.c: No such file or directory.
Lista<Candidato> ordenarLista(Lista<Candidato> candidatos)
{   
    nodo<Candidato>* cabecera = candidatos.ObtPrimero();
    nodo<Candidato> *nodoActual = cabecera; 
    int tamanio = candidatos.Contar();
    int itr = 0;
    bool intercambiado;

    while (itr < tamanio)
    {
    nodo<Candidato> *nodoRecorrido = cabecera;
    nodo<Candidato> *nodoPrevio = cabecera;
    intercambiado = false; 

        while (candidatos.ObtProx(nodoRecorrido))
        {
            // Puntero temporal para guardar el siguiente nodo de nodoRecorrido
            nodo<Candidato> *ptr = candidatos.ObtProx(nodoRecorrido);
            // Extraemos los votos para hacer la comparacion
            Candidato c1 = candidatos.ObtInfo(nodoRecorrido);
            Candidato c2 = candidatos.ObtInfo(ptr);
            

            cout << "Comparando " << c1.getVotos() << " votos contra " << c2.getVotos() << " votos" << endl; 

            if (c1.getVotos() < c2.getVotos())
            {
                cout << "intercambiando..." << endl ;
                intercambiado = true;

                // Si el nodo que se esta observando es la cabecera, se hace el swapping y se actualiza la cabecera
                if (nodoRecorrido == candidatos.ObtPrimero())
                {
                    candidatos.AsigProx(nodoRecorrido, candidatos.ObtProx(ptr));
                    candidatos.AsigProx(ptr, nodoRecorrido);
                    nodoPrevio = ptr;
                    cabecera = nodoPrevio;
                }
                else
                {
                    candidatos.AsigProx(nodoRecorrido, candidatos.ObtProx(ptr));
                    candidatos.AsigProx(ptr, nodoRecorrido);
                    candidatos.AsigProx(nodoPrevio, ptr);
                    nodoPrevio = ptr;
                }
                continue;
            }
            nodoPrevio = nodoRecorrido;
            nodoRecorrido = candidatos.ObtProx(nodoRecorrido);
        }
        if (!intercambiado) {
            cout << "No se intercambian" << endl;
            break;
        }
        ++itr; 
    }

    return candidatos; 
}

int main()
{
    Inscripcion inscripcion;
    Votantes votantes;

    int opcionInicial;
    ;

    do
    {
        // Menu inicial
        // cout << "\033[H\033[2J"; // mantiene el menu en la parte de arriba de la terminal
        cout << "\nBienvenido al sistema de gestion de elecciones." << endl;
        cout << "1. Entrar al sistema de gestion de candidatos" << endl;
        cout << "2. Entrar al modulo votantes" << endl;
        cout << "3. Salir" << endl;
        cout << "Elige una opcion:";
        cin >> opcionInicial;
        cin.ignore(); // Limpiar el buffer de entrada

        if (opcionInicial == 1)
        {
            int opcion;
            do
            {
                // cout << "\033[H\033[2J"; // mantiene el menu en la parte de arriba de la terminal

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
                cout << "Elige una opcion:";
                cin >> opcion;
                cin.ignore(); // Limpiar el buffer de entrada

                switch (opcion)
                {
                case 1:
                {
                    inscripcion.Registrar();
                    break;
                }

                case 2:
                {

                    inscripcion.MostrarCandidatos();
                    break;
                }

                case 3:
                {

                    string cedBuscar;
                    cout << "\tIngrese la cedula del candidato:";
                    cin >> cedBuscar;
                    cin.ignore(); // Limpiar el buffer de entrada

                    inscripcion.iterarCandidatos(cedBuscar, 1);
                    break;
                }

                case 4:
                {

                    string cedulaModificar;
                    cout << "\tIngrese la cedula del candidato a modificar:";
                    cin >> cedulaModificar;
                    cin.ignore(); // Limpiar el buffer de entrada

                    inscripcion.iterarCandidatos(cedulaModificar, 2);
                    break;
                }

                case 5:
                {

                    string cedEliminar;
                    cout << "\tIngrese la cedula del candidato a eliminar:";
                    cin >> cedEliminar;
                    cin.ignore(); // Limpiar el buffer de entrada

                    inscripcion.iterarCandidatos(cedEliminar, 3);
                    break;
                }

                case 6:
                {
                    // inscripcion.ReporteGeneral();
                    inscripcion.MostrarReporteCompleto(); // hecho por el equipo del Punto 5 - Reporte
                    break;
                }

                case 7:
                {
                    string partido;
                    cout << "Ingresa el nombre del partido:";
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

                case 9:
                {
                    inscripcion.CargarCandidatos();
                    break;
                }

                default:
                    cout << "Opcion no valida. Intenta de nuevo." << endl;
                }
                system("pause");
            } while (opcion != 8);
        }

        else if (opcionInicial == 2)
        {
            int opcion;
            do
            {
                // cout << "\033[H\033[2J"; // mantiene el menu en la parte de arriba de la terminal
                cout << "\nModulo votantes seleccionado\n"
                     << endl;
                cout << "\t 1. Registrar Votante" << endl;
                cout << "\t 2. Cargar Votantes desde archivo" << endl;
                cout << "\t 3. Mostrar Electores inscritos" << endl;
                cout << "\t 4. Procesar Votantes" << endl;
                cout << "\t 5. Reportes" << endl;
                cout << "\t 6. Resultados" << endl;
                cout << "\t 0. Salir" << endl;

                cout << "\t Elegir una opcion ";
                cin >> opcion;

                switch (opcion)
                {
                case 0:
                {
                    cout << "\nSaliendo del Modulo votantes\n"
                         << endl;
                    opcionInicial = 0;
                    break;
                }
                case 1:
                {
                    votantes.RegistrarElector();
                    break;
                }
                case 2:
                {
                    cout << "\t Cargando datos desde archivo \n"
                         << endl;
                    votantes.CargarDatos();
                    break;
                }

                case 3:
                {
                    votantes.MostrarElectores();
                    break;
                }
                case 4:
                {

                    votantes.ProcesarVotantes(inscripcion.getCandidatos());
                    break;
                }
                case 5:
                {
                    votantes.MostrarMenuReportes();
                    break;
                }
                case 6:
                {   

                    Lista<Candidato> candidatos_ordenados = ordenarLista(inscripcion.getCandidatos()); 
                    nodo<Candidato>* nodoActual = candidatos_ordenados.ObtPrimero(); 
                    while (nodoActual) {
                        Candidato c = candidatos_ordenados.ObtInfo(nodoActual); 
                        cout << c.getNombre() << " " << c.getApellido() << " votos: " << c.getVotos() << endl; 
                        nodoActual = candidatos_ordenados.ObtProx(nodoActual); 
                    }
                    break;
                }
                default:
                {
                    cout << "Opcion no valida. Intenta de nuevo." << endl;
                }
                }

                system("pause");
            } while (opcion != 0);
        }

    } while (opcionInicial == 1 || opcionInicial == 2 || opcionInicial == 0);

    if (opcionInicial == 3)
    {
        cout << "Saliendo del programa." << endl;
    }

    else
    {
        cout << "Opcion no valida. Terminando el programa." << endl;
    }

    system("pause");
    return 0;
}
// prueba de permisos 2
