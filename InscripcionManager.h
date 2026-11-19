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
    void modificarInscripcion();
    void eliminarInscripcion();
    void listarInscripcion();
private:
    Inscripcion crearInscripcion();
    void cargarInscripcionUnica(int &legajo, int &idCurso);

    int seleccionarAlumno();
    int seleccionarCurso();

    bool menuModificarInscripcion(Inscripcion &reg);

    void mostrarInscripcion(const Inscripcion &reg);
    void mostrarInscripcionesActivas();
    void listarAlumnos();
    void listarCursos();

    InscripcionArchivo _inscripcionArchivo;
    AlumnoArchivo _alumnoArchivo;
    CursoArchivo _cursoArchivo;
};
