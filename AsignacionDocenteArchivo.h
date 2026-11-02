#pragma once
#include <string>
#include "AsignacionDocente.h"
#include "ArchivoError.h"

class AsignacionDocenteArchivo
{
public:
    AsignacionDocenteArchivo(std::string fileName="AsignacionDocente.dat");
    ArchivoError guardar(AsignacionDocente reg);
    ArchivoError guardar(int index, AsignacionDocente reg);
    ArchivoError leerTodos(AsignacionDocente reg[], int cant);
    AsignacionDocente leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByID(int id);
    std::string getLastError();

private:
    AsignacionDocente _asignacionDocente;
    std::string _fileName;
    std::string _errorMessage;
};
