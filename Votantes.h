//
// Created by arnal on 18/11/2024.
//

#ifndef VOTANTES_H
#define VOTANTES_H

#include "Libreria/Lista.h"
#include "Elector.h"
#include "Candidato.h"
#include <string>
using namespace std;

class Votantes {
    private:
    Lista<Elector> electores;
    Lista<Elector> colaVotantes; 
    Lista<Elector> colaNoVotantes; 
    public:
    Votantes(); //Constructor

    //Registrar un elector
    //void insertarElector(Elector elector, int prioridad);
    void RegistrarElector();

    //Votacion
    void ListarCandidatos(Lista<Candidato>& candidatos, bool mostrarVotos);
    bool ProcesarVotantes(Lista<Candidato>& candidatos); 

    //Mostrar los electores registrados
    void MostrarElectores();

    void CargarDatos();
    
     //Mostrar el menu para los reportes
    void MostrarMenuReportes();
    //Reporte por prioridad
    void ReportePorPrioridad();
    // Reporte por status ( si voto o no)
    void ReportePorStatus();

    // LISTA LOS GANADORES DESPUES DE LAS ELECCIONES
    void listarGanadores(Lista<Candidato>& candidatos);
};

#endif //VOTANTES_H
