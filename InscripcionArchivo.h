#pragma once
#include <string>
#include "Inscripcion.h"
#include "ArchivoError.h"

class InscripcionArchivo
{
public:
    InscripcionArchivo(const std::string &fileName = "Inscripciones.dat");
    ArchivoError guardar(const Inscripcion &reg);
    ArchivoError guardar(int index, const Inscripcion &reg);
    ArchivoError leerTodos(Inscripcion reg[], int cant);
    Inscripcion leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByID(int id);
    bool existeInscripcion(int legajo, int idCurso);
    int getCantRegActivos();
    std::string getLastError()const;

private:
    std::string _fileName;
    std::string _errorMessage;
};
