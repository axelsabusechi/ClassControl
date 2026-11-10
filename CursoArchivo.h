#pragma once
#include <string>
#include "Curso.h"
#include "ArchivoError.h"

class CursoArchivo
{
public:
    CursoArchivo(const std::string &fileName = "Cursos.dat");
    ArchivoError guardar(const Curso &reg);
    ArchivoError guardar(int index, const Curso &reg);
    ArchivoError leerTodos(Curso reg[], int cant);
    Curso leer(int index);
    int getCantReg();
    int getNewID();
    int buscarByID(int id);
    bool existeCurso(int id);
    int getCantRegActivos();
    std::string getLastError();

private:
    std::string _fileName;
    std::string _errorMessage;
};
