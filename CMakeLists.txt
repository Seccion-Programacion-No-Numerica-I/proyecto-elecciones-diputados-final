cmake_minimum_required(VERSION 3.16)
project(proyecto_elecciones_diputados)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Libreria)

add_executable(proyecto_elecciones_diputados
    Libreria/Lista.cpp
    Libreria/Lista.h
    Libreria/Pila.h
    Candidato.cpp
    Candidato.h
    Inscripcion.cpp
    Inscripcion.h
    main.cpp
    Partido.cpp
    Partido.h
        Elector.h
        Elector.cpp
        Votantes.cpp
        Votantes.h
)
