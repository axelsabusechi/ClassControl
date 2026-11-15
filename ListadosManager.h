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
    AlumnoArchivo _alumnoArchivo;
    CursoArchivo _cursoArchivo;
    InscripcionArchivo _inscripcionArchivo;
    DocenteArchivo _docenteArchivo;
    AsignacionDocenteArchivo _asignacionDocenteArchivo;
    TemaArchivo _temaArchivo;
    ClaseDadaArchivo _claseDadaArchivo;
};
