#ifndef Inscripcion_H
#define Inscripcion_H
#include <string>
#include "Candidato.h"
#include "Libreria/Lista.h"
using namespace std;

class Inscripcion {

   private:
   	Lista<Candidato> candidatos;
    int candidatosPorPartido[5] = {0};
    Lista<Candidato> partidos[5];

   public:
    // Constructor
    Inscripcion();

    //Verificar si se puede ingresar el candidato
    bool verificarDisponibilidad(Candidato);

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
};

#endif
