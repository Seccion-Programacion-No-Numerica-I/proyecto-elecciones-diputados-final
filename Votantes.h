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
		Lista<Elector> colaEliminados;

	public:
		Votantes(); //Constructor

    //Votacion
    void ListarCandidatos(Lista<Candidato>& candidatos, bool mostrarVotos);
    bool ProcesarVotantes(Lista<Candidato>& candidatos); 
    bool procesarVoto(Lista<Candidato>& candidatos, int posicion); 
    int MenuVotacion(Lista<Candidato>& candidatos); 

		//Votacion
		void ListarCandidatos(Lista<Candidato>& candidatos, bool mostrarVotos);
		bool ProcesarVotantes(Lista<Candidato>& candidatos);

		//Metodo donde Se elimina el votante de la lista de electores y se pasa a la cola de Eliminados
		void EliminarVotante(string cedulaVotante);

		//Mostrar los electores registrados
		void MostrarElectores();

		void CargarDatos();

		//Mostrar el menu para los reportes
		void MostrarMenuReportes(Lista<Candidato>& candidatos);
		//Reporte de votantes
		void ReporteDeVotantes();
		//Reporte de Eliminados
		void ReporteEliminados();
		//Reporte de Exluidos
		void ReporteExcluidos();
		//Reporte de la lista de excrutinio
		void ReporteExcrutinio(Lista<Candidato>& candidatos);
    // LISTA LOS GANADORES DESPUES DE LAS ELECCIONES
    void listarGanadores(Lista<Candidato>& candidatos);
};

#endif //VOTANTES_H
