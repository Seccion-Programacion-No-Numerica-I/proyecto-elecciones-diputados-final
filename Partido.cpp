#include "Partido.h"

Partido::Partido(){
}
Partido::Partido(int identifier,string& nom):id(identifier),nombre(nom)
{
}


void Partido::setId(int identifier){
	id = identifier;
}

int Partido::getId(){
	return id;
}

void Partido::setNombre(string nomb){
	nombre = nomb;
}

string Partido::getNombre(){
	return nombre;
}

void Partido::mostrarInformacion(){
	cout<<"--------------------------------";
	cout<<"\n Id del partido: "<<id<<endl;
	cout<<"\n Nombre del partido: "<<nombre<<endl;
	cout<<"--------------------------------"<<endl;;
}

bool Partido::operator==(const Partido& other) const {
    return id == other.id &&
           nombre == other.nombre;
}