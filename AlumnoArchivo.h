#pragma once
#include <string>
#include "Alumno.h"
#include "ArchivoError.h"

class AlumnoArchivo
{
public:
    AlumnoArchivo(std::string fileName="Alumnos.dat");
    ArchivoError guardar(Alumno reg);
    ArchivoError guardar(int index, Alumno reg);
    ArchivoError leerTodos(Alumno reg[], int cant);
    Alumno leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByLegajo(int legajo);
    std::string getLastError();
private:
    Alumno _alumno;
    std::string _fileName;
    std::string _errorMessage;
};
