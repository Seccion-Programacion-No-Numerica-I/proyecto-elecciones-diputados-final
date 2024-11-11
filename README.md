# eleccion-diputados-definitivo

Para compilar con cmake (instalarlo antes en su sistema operativo):

Se van a la carpeta build en la terminal:
	cd build 

Ejecutan los siguientes comandos:
	cmake .. (este para cargar la configuracion que tiene el CMakeLists.txt)

    cmake --build .

Y luego dentro de la misma carpeta ejecutan el ejecutable


Para usar mingw o g++ directamente

g++ Libreria/Lista.cpp Candidato.cpp Inscripcion.cpp main.cpp -o app

y luego ejecutan el ejecutable
