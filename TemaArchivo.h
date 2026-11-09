#pragma once
#include <string>
#include "Tema.h"
#include "ArchivoError.h"

class TemaArchivo
{
public:
    TemaArchivo(std::string fileName="Temas.dat");
    ArchivoError guardar(Tema reg);
    ArchivoError guardar(int index, Tema reg);
    ArchivoError leerTodos(Tema reg[], int cant);
    Tema leer(int index);
    int getCantReg();
    int getNewId();
    int buscarById(int id);
    std::string getLastError();

public:
    Tema _tema;
    std::string _fileName;
    std::string _errorMessage;
};
