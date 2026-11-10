#pragma once
#include "Curso.h"
#include "CursoArchivo.h"
#include "Division.h"
#include "Grado.h"

class CursoManager
{
public:
    CursoManager();

    void registrarCurso();
    void listarCursos();
    void modificarCurso();
    void eliminarCurso();

private:
    Curso crearCurso();
    void cargarCurso(int &gr, int &div);
    void mostrarCurso(const Curso &reg);

    CursoArchivo _cursoArchivo;
};
