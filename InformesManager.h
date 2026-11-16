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
    float calcularpromedioAlumno(int legajo);
    void mostrarPromedioAlumno(const Alumno &reg, float promedio)const;
    int seleccionarCurso();
    void listarCursos();
    void mostrarEncabezadoCurso(const Curso &reg, const std::string &titulo)const;
    void mostrarCantAlumnosGrado(int primero,
                                 int segundo,
                                 int tercero,
                                 int cuarto,
                                 int quinto,
                                 int sexto)const;
    void acumularAlumnosPorGrado(int &primero,
                                 int &segundo,
                                 int &tercero,
                                 int &cuarto,
                                 int &quinto,
                                 int &sexto);
    float calcularPromedioAlumno(int legajo);
    bool mostrarHistorialRendimientoPorCurso(int idCurso);


    AlumnoArchivo _alumnoArchivo;
    CursoArchivo _cursoArchivo;
    InscripcionArchivo _inscripcionArchivo;
    NotaArchivo _notaArchivo;
    ClaseDadaArchivo _claseDadaArchivo;
    UnidadDidacticaArchivo _unidadDidacticaArchivo;
    TemaArchivo _temaArchivo;
};
