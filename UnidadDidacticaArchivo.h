#pragma once
#include <string>
#include "UnidadDidactica.h"
#include "ArchivoError.h"

class UnidadDidacticaArchivo
{
public:
    UnidadDidacticaArchivo(const std::string &fileName = "UnidadesDidacticas.dat");
    ArchivoError guardar(const UnidadDidactica &reg);
    ArchivoError guardar(int index, const UnidadDidactica &reg);
    ArchivoError leerTodos(UnidadDidactica reg[], int cant);
    UnidadDidactica leer(int index);
    int getCantReg();
    int getCantRegActivos();
    int getNewID();
    int buscarByID(int id);
    std::string getLastError()const;

private:
    std::string _fileName;
    std::string _errorMessage;
};

