#pragma once
#include <string>
#include "Alumno.h"
#include "ArchivoError.h"

class AlumnoArchivo
{
public:
    AlumnoArchivo(const std::string &fileName = "Alumnos.dat");
    ArchivoError guardar(const Alumno &reg);
    ArchivoError guardar(int index, const Alumno &reg);
    ArchivoError leerTodos(Alumno reg[], int cant);
    Alumno leer(int index);
    int getCantReg();
    int getNewLegajo();
    int buscarByLegajo(int legajo);
    int getCantRegActivos();
    bool existeAlumno(int legajo);
    bool existeDni(const std::string &dni, int legajoIgnorar = -1);
    std::string getLastError()const;

private:
    std::string _fileName;
    std::string _errorMessage;
};
