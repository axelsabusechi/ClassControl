#pragma once
#include "AlumnoArchivo.h"
#include "CursoArchivo.h"
#include "InscripcionArchivo.h"
#include "DocenteArchivo.h"
#include "AsignacionDocenteArchivo.h"
#include "TemaArchivo.h"
#include "ClaseDadaArchivo.h"

class ListadosManager
{
public:
    void listarAlumnosPorCurso();
    void listarDocentesPorCurso();
    void listarTemasPorEstado();

private:
    int seleccionarCurso();
    void listarCursos();
    void mostrarEncabezadoCurso(const Curso &reg, const std::string &titulo)const;
    bool mostrarAlumnosCurso(int idCurso);
    void mostrarAlumno(const Alumno &reg)const;
    bool mostrarDocentesCurso(int idCurso);
    void mostrarDocente(const Docente &reg)const;

    AlumnoArchivo _alumnoArchivo;
    CursoArchivo _cursoArchivo;
    InscripcionArchivo _inscripcionArchivo;
    DocenteArchivo _docenteArchivo;
    AsignacionDocenteArchivo _asignacionDocenteArchivo;
    TemaArchivo _temaArchivo;
    ClaseDadaArchivo _claseDadaArchivo;
};
