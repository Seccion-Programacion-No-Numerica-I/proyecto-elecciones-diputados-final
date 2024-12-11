#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    static bool validarEntero(const std::string& input, int& output);
    static bool validarDouble(const std::string& input, double& output);
    static bool validarString(const std::string& input);
    static bool validarNombre(const std::string& input);
    static bool validarCedula(const std::string& input);
    static bool validarPartidoPolitico(const std::string& input);
};

#endif // VALIDACIONES_H