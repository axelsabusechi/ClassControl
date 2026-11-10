#pragma once
#include <string>
#include "AsignacionDocente.h"
#include "ArchivoError.h"

class AsignacionDocenteArchivo
{
public:
    AsignacionDocenteArchivo(const std::string &fileName = "AsignacionesDocentes.dat");
    ArchivoError guardar(const AsignacionDocente &reg);
    ArchivoError guardar(int index, const AsignacionDocente &reg);
    ArchivoError leerTodos(AsignacionDocente reg[], int cant);
    AsignacionDocente leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByID(int id);
    bool existeAsignacion(int idDocente, int idCurso);
    int getCantRegActivos();
    std::string getLastError()const;

private:
    std::string _fileName;
    std::string _errorMessage;
};
