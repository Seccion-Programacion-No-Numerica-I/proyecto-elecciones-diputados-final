#include "Validaciones.h"
#include <sstream>
#include <cctype>
#include <iostream>

bool Validaciones::validarEntero(const std::string& input, int& output) {
    std::istringstream iss(input);
    iss >> output;
    if (iss.fail() || !iss.eof()) {
        std::cout << "Entrada no valida. Debe ser un numero entero." << std::endl;
        return false;
    }
    return true;
}

bool Validaciones::validarDouble(const std::string& input, double& output) {
    std::istringstream iss(input);
    iss >> output;
    if (iss.fail() || !iss.eof()) {
        std::cout << "Entrada no valida. Debe ser un numero real." << std::endl;
        return false;
    }
    return true;
}

bool Validaciones::validarString(const std::string& input) {
    for (char c : input) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            std::cout << "Entrada no valida. Solo se permiten letras y espacios." << std::endl;
            return false;
        }
    }
    return true;
}

bool Validaciones::validarNombre(const std::string& input) {
    for (char c : input) {
        if (!std::isalpha(c)) {
            std::cout << "Nombre no valido. No debe contener numeros, caracteres especiales ni espacios." << std::endl;
            return false;
        }
    }
    return true;
}

bool Validaciones::validarCedula(const std::string& input) {
    if (input.length() < 6 || input.length() > 9) {
        std::cout << "Cedula no valida. Debe tener entre 6 y 9 digitos." << std::endl;
        return false;
    }
    for (char c : input) {
        if (!std::isdigit(c) || std::isspace(c)) {
            std::cout << "Cedula no valida. Solo se permiten numeros y no debe contener espacios." << std::endl;
            return false;
        }
    }
    return true;
}