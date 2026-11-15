#pragma once
#include <string>
#include "UnidadDidactica.h"
#include "ArchivoError.h"

class UnidadDidacticaArchivo
{
public:
    UnidadDidacticaArchivo(std::string fileName="UnidadesDidacticas.dat");
    ArchivoError guardar(UnidadDidactica reg);
    ArchivoError guardar(int index, UnidadDidactica reg);
    ArchivoError leerTodos(UnidadDidactica reg[], int cant);
    UnidadDidactica leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByID(int id);
    std::string getLastError();

private:
    std::string _fileName;
    std::string _errorMessage;
};

