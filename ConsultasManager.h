#pragma once
#include "AlumnoArchivo.h"
#include "DocenteArchivo.h"
#include "CursoArchivo.h"
#include "InscripcionArchivo.h"
#include "AsignacionDocenteArchivo.h"
#include "NotaArchivo.h"
#include "UnidadDidacticaArchivo.h"
#include "TemaArchivo.h"
#include "ClaseDadaArchivo.h"

class ConsultasManager
{
public:
    ConsultasManager();

    void consultarAlumnoPorLegajo();
    void consultarDocentePorDni();
    void consultarNotasPorAlumno();
    void consultarCurriculaPorDocente();
    void consultarDesempenioAcademicoPorAlumno();

private:
    int seleccionarAlumno();
    std::string seleccionarDocente();

    void listarAlumnos();
    void mostrarAlumno(const Alumno &reg)const;
    void mostrarAlumnoResumido(const Alumno &reg)const;

    void listarDocentes();
    void mostrarDocente(const Docente &reg)const;
    void mostrarDocenteResumido(const Docente &reg)const;

    bool mostrarNotasAlumno(int legajo);
    void mostrarNota(const Nota &reg)const;
    void mostrarDesempenioAcademico(int cantNotas,
                                    int aprobadas,
                                    int desaprobadas,
                                    int aplazos,
                                    float promedio)const;

    bool mostrarCurriculaDocente(int idDocente);
    bool mostrarUnidadesCurso(int idCurso);
    bool mostrarTemasUnidad(int idUnidad);

    float calcularDesempenioAcademico(int legajo,
                                      int &cantNotas,
                                      int &aprobadas,
                                      int &desaprobadas,
                                      int &aplazos);
    bool hayAlumnosActivos();
    bool hayDocentesActivos();
    bool temaVisto(int idTema);

    AlumnoArchivo _alumnoArchivo;
    DocenteArchivo _docenteArchivo;
    CursoArchivo _cursoArchivo;
    InscripcionArchivo _inscripcionArchivo;
    AsignacionDocenteArchivo _asignacionDocenteArchivo;
    NotaArchivo _notaArchivo;
    UnidadDidacticaArchivo _unidadDidacticaArchivo;
    TemaArchivo _temaArchivo;
    ClaseDadaArchivo _claseDadaArchivo;
};
