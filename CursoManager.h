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
    void cargarCursoUnico(Grado &grado, Division &division);

    bool menuModificarCurso(Curso &reg);
    void modificarGrado(Curso &reg);
    void modificarDivision(Curso &reg);
    void modificarTodos(Curso &reg);

    void mostrarCurso(const Curso &reg)const;
    void mostrarCursosActivos();

    CursoArchivo _cursoArchivo;
};
