#ifndef PARTIDO_H
#define PARTIDO_H
#include <iostream>
#include <string>

using namespace std;
class Partido
{
	private:
		int id;
		string nombre;
	public:
		Partido();
		Partido(int identifier,string& nombre);
		
		void setId(int identifier);
		int getId();
		
		void setNombre(string nomb);
		string getNombre();
		
		void mostrarInformacion();

	// Operador de igualdad
    bool operator==(const Partido& other) const;
};

#endif