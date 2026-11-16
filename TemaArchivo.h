#pragma once
#include <string>
#include "Tema.h"
#include "ArchivoError.h"

class TemaArchivo
{
public:
    TemaArchivo(const std::string &fileName = "Temas.dat");
    ArchivoError guardar(const Tema &reg);
    ArchivoError guardar(int index, const Tema &reg);
    ArchivoError leerTodos(Tema reg[], int cant);
    Tema leer(int index);
    int getCantReg();
    int getNewId();
    int buscarById(int id);
    bool existeTema(int id);
    std::string getLastError()const;

public:
    std::string _fileName;
    std::string _errorMessage;
};
