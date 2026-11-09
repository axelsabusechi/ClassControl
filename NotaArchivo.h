#pragma once
#include <string>
#include "Nota.h"
#include "ArchivoError.h"

class NotaArchivo
{
public:
    NotaArchivo(std::string fileName="Notas.dat");
    ArchivoError guardar(Nota reg);
    ArchivoError guardar(int index, Nota reg);
    ArchivoError leerTodos(Nota reg[], int cant);
    Nota leer(int index);
    int getCantReg();
    int getNewID();
    int buscarById(int id);
    std::string getLastError();

private:
    Nota _nota;
    std::string _fileName;
    std::string _errorMessage;
};
