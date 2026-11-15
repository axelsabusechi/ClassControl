#pragma once
#include <string>
#include "Nota.h"
#include "ArchivoError.h"

class NotaArchivo
{
public:
    NotaArchivo(const std::string &fileName = "Notas.dat");
    ArchivoError guardar(const Nota &reg);
    ArchivoError guardar(int index, const Nota &reg);
    ArchivoError leerTodos(Nota reg[], int cant);
    Nota leer(int index);
    int getCantReg();
    int getNewId();
    int buscarById(int id);
    int getCantRegActivos();
    std::string getLastError();

private:
    std::string _fileName;
    std::string _errorMessage;
};
