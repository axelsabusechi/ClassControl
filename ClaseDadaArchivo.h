#pragma once
#include <string>
#include "ClaseDada.h"
#include "ArchivoError.h"

class ClaseDadaArchivo
{
public:
    ClaseDadaArchivo(const std::string &fileName = "ClasesDadas.dat");
    ArchivoError guardar(const ClaseDada reg);
    ArchivoError guardar(int index, const ClaseDada reg);
    ArchivoError leerTodos(ClaseDada reg[], int cant);
    ClaseDada leer(int index);
    int getCantReg();
    int getCantRegActivos();
    int getNewID();
    int buscarByID(int id);
    std::string getLastError()const;
private:
    std::string _fileName;
    std::string _errorMessage;
};
