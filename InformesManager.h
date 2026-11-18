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
    void mostrarPromedioAlumno(const Alumno &reg, float promedio)const;
    void mostrarCantAlumnosGrado(int primero,
                                 int segundo,
                                 int tercero,
                                 int cuarto,
                                 int quinto,
                                 int sexto) const;
    bool mostrarHistorialRendimientoPorCurso(int idCurso);

    float calcularPromedioAlumno(int legajo);
    void acumularAlumnosPorGrado(int &primero,
                                 int &segundo,
                                 int &tercero,
                                 int &cuarto,
                                 int &quinto,
                                 int &sexto);
    int contarClasesSuspendidas(int idCurso);
    void calcularAvanceCurso(int idCurso, int &totalTemas, int &temasVistos);

    bool temaVisto(int idTema);

    AlumnoArchivo _alumnoArchivo;
    CursoArchivo _cursoArchivo;
    InscripcionArchivo _inscripcionArchivo;
    NotaArchivo _notaArchivo;
    ClaseDadaArchivo _claseDadaArchivo;
    UnidadDidacticaArchivo _unidadDidacticaArchivo;
    TemaArchivo _temaArchivo;
};
