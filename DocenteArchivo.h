#pragma once
#include <string>
#include "Docente.h"
#include "ArchivoError.h"

class DocenteArchivo
{
public:
    DocenteArchivo(std::string fileName="Docentes.dat");
    ArchivoError guardar(Docente reg);
    ArchivoError guardar(int index, Docente reg);
    ArchivoError leerTodos(Docente reg[], int cant);
    Docente leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByID(int id);
    std::string getLastError();
private:
    Docente _docente;
    std::string _fileName;
    std::string _errorMessage;
};
