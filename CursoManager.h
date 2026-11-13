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
    void modificarCurso();
    void eliminarCurso();
    void listarCursos();

private:
    Curso crearCurso();
    void mostrarCurso(const Curso &reg);
    void mostrarCursosActivos();
    bool menuModificarCurso(Curso &reg);
    void modificarGrado(Curso &reg);
    void modificarDivision(Curso &reg);
    void modificarTodos(Curso &reg);
    void pedirCursoUnico(Grado &grado, Division &division);


    CursoArchivo _cursoArchivo;
};
