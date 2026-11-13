#pragma once
#include "Inscripcion.h"
#include "InscripcionArchivo.h"
#include "AlumnoArchivo.h"
#include "CursoArchivo.h"
#include "ArchivoError.h"

class InscripcionManager
{
public:
    InscripcionManager();

    void registrarInscripcion();
    void eliminarInscripcion();
    void listarInscripcion();
private:
    Inscripcion crearInscripcion();
    void mostrarInscripcion(const Inscripcion &reg);
    void mostrarInscripcionesActivas();
    void pedirInscripcionUnica(int &legajo, int &idCurso);
    void listarAlumnos();
    void listarCursos();
    int seleccionarAlumno();
    int seleccionarCurso();

    InscripcionArchivo _inscripcionArchivo;
    AlumnoArchivo _alumnoArchivo;
    CursoArchivo _cursoArchivo;

};
