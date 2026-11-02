#pragma once
#include "ClaseDada.h"
#include "ArchivoError.h"

class ClaseDadaArchivo
{
public:
    ClaseDadaArchivo(std::string fileName="ClasesDadas.dat");
    ArchivoError guardar(ClaseDada reg);
    ArchivoError guardar(int index, ClaseDada reg);
    ArchivoError leerTodos(ClaseDada reg[], int cant);
    ClaseDada leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByID(int id);
    std::string getLastError();
private:
    ClaseDada _claseDada;
    std::string _fileName;
    std::string _errorMessage;
};
