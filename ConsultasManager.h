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
    int seleccionarAlumno();
    void mostrarAlumno(const Alumno &reg)const;
    void mostrarAlumnoResumido(const Alumno &reg)const;
    void listarAlumnos();
    std::string seleccionarDocente();
    void mostrarDocente(const Docente &reg)const;
    void listarDocentes();
    bool mostrarNotasAlumno(int legajo);
    void mostrarNota(const Nota &reg)const;
    void mostrarDesempenioAcademico(int cantNotas,
                                    int aprobadas,
                                    int desaprobadas,
                                    int aplazos,
                                    float promedio)const;
    float calcularDesempenioAcademico(int legajo,
                                      int &cantNotas,
                                      int &aprobadas,
                                      int &desaprobadas,
                                      int &aplazos);

    AlumnoArchivo _alumnoArchivo;
    DocenteArchivo _docenteArchivo;
    CursoArchivo _cursoArchivo;
    InscripcionArchivo _inscripcionArchivo;
    AsignacionDocenteArchivo _asignacionDocenteArchivo;
    NotaArchivo _notaArchivo;
};
