#ifndef Inscripcion_H
#define Inscripcion_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <chrono>
#include "Candidato.h"
#include "Libreria/Lista.h"
using namespace std;

class Inscripcion {

	private:
		Lista<Candidato> candidatos;
		int candidatosPorPartido[5] = {0};
		Lista<Candidato> partidos[5];
		string esloganes[10] = {
			"Tecnologizando el cambio.",
			"El futuro nos llama, respondamos juntos!",
			"Codifica tu futuro.",
			"La universidad del mañana, hoy.",
			"Mas que bytes, ideas.",
			"Conectados por la tecnologia, unidos por un mismo sueño.",
			"Tu voz, nuestra tecnologia.",
			"Juntos, haremos historia.",
			"Una comunidad, un futuro.",
			"La tecnologia al servicio de todos."
		};
		

	public:
		// Constructor
		Inscripcion();

		//Verificar si se puede ingresar el candidato
		bool verificarDisponibilidad(Candidato);

		Lista<Candidato>& getCandidatos(); 
		//Registrar un candidato
		void Registrar();

		//Buscar un candidato
		void Buscar(Candidato);

		//Modificar un candidato
		Candidato Modificar(Candidato, string cedula);
		void MostrarCandidatosPorPartido(string buscarPartido);

		//Eliminar un candidato
		void Eliminar(Candidato);

		//Recorre toda la lista de candidatos y realiza acciones sobre el candidato indicado
		void iterarCandidatos(string, int);

		//Muestra en pantalla todos los candidatos
		void MostrarCandidatos();

		// reportes
		void ReporteGeneral();
		void MostrarReporteCompleto();

		//Metodos Auxiliares - Punto 5 - Reporte
		int generarNumeroAleatorio();
		string generarEsloganAletorio();

		//Cargar Candidatos por archivo
		void CargarCandidatos(); 
		
};

#endif
