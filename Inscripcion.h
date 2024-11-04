
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

    void mensaje();

    Candidato CrearMarca();

    //Verificar si se puede ingresar el candidato
    bool verificarDisponibilidad(Candidato);

    // Metodo para registrar un candidato
    void RegistrarCandidato(Candidato);

    //Método para eliminar un candidato
    void EliminarCandidato(string);

    void MostrarCandidatos();
    
    Candidato BuscarCandidato(string cedula);

    // reportes
    void ReporteGeneral();


};

#endif
