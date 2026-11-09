#pragma once
#include <string>
#include "Alumno.h"
#include "ArchivoError.h"

class AlumnoArchivo
{
public:
    AlumnoArchivo(const std::string &fileName="Alumnos.dat");
    ArchivoError guardar(const Alumno &reg);
    ArchivoError guardar(int index, const Alumno &reg);
    ArchivoError leerTodos(Alumno reg[], int cant);
    Alumno leer(int index);
    int getCantReg()const;
    int getNewLegajo()const;
    int buscarByLegajo(int legajo);
    std::string getLastError()const;
    bool existeDni(const std::string &dni, int legajoIgnorar=-1);

private:
    //Alumno _alumno;
    std::string _fileName;
    std::string _errorMessage;
};
