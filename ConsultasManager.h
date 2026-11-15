#pragma once
#include "AlumnoArchivo.h"
#include "DocenteArchivo.h"
#include "CursoArchivo.h"
#include "InscripcionArchivo.h"
#include "AsignacionDocenteArchivo.h"
#include "NotaArchivo.h"

class ConsultasManager
{
public:
    void consultarAlumnoPorLegajo();
    void consultarDocentePorDni();
    void consultarNotasPorAlumno();
    void consultarCurricularPorDocente();
    void consultarDesempenioAcademicoPorAlumno();
private:
    AlumnoArchivo _alumnoArchivo;
    DocenteArchivo _docenteArchivo;
    CursoArchivo _cursoArchivo;
    InscripcionArchivo _inscripcionArchivo;
    AsignacionDocenteArchivo _asignacionDocenteArchivo;
    NotaArchivo _notaArchivo;
};
