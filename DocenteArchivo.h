#pragma once
#include <string>
#include "Docente.h"
#include "ArchivoError.h"

class DocenteArchivo
{
public:
    DocenteArchivo(const std::string &fileName = "Docentes.dat");
    ArchivoError guardar(const Docente &reg);
    ArchivoError guardar(int index, const Docente &reg);
    ArchivoError leerTodos(Docente reg[], int cant);
    Docente leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByID(int id);
    bool existeDocente(int id);
    int getCantRegActivos();
    bool existeDni(const std::string &dni, int iDIgnorar = -1);
    std::string getLastError()const;

private:
    std::string _fileName;
    std::string _errorMessage;
};
