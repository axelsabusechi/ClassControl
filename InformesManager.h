#pragma once
#include "AlumnoArchivo.h"
#include "CursoArchivo.h"
#include "InscripcionArchivo.h"
#include "NotaArchivo.h"
#include "ClaseDadaArchivo.h"
#include "UnidadDidacticaArchivo.h"
#include "TemaArchivo.h"

class InformesManager
{
public:
    void cantidadAlumnosPorGrado();
    void promedioNotasPorAlumno();
    void cantidadClasesSuspendidasPorCurso();
    void historialRendimientoPorCurso();
    void avanceCurricularPorCurso();
private:
    AlumnoArchivo _alumnoArchivo;
    CursoArchivo _cursoArchivo;
    InscripcionArchivo _inscripcionArchivo;
    NotaArchivo _notaArchivo;
    ClaseDadaArchivo _claseDadaArchivo;
    UnidadDidacticaArchivo _unidadDidacticaArchivo;
    TemaArchivo _temaArchivo;
};
