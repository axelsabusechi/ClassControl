#pragma once
#include "Nota.h"
#include "NotaArchivo.h"
#include "AlumnoArchivo.h"
#include "Fecha.h"
#include "Periodo.h"

class NotaManager
{
public:
    NotaManager();

    void registrarNota();
    void modificarNota();
    void eliminarNota();
    void listarNotas();

private:
    Nota crearNota();

    int seleccionarAlumno();

    bool menuModificarNota(Nota &reg);
    void modificarLegajo(Nota &reg);
    void modificarPeriodo(Nota &reg);
    void modificarNota(Nota &reg);
    void modificarDescripcion(Nota &reg);
    void modificarTodos(Nota &reg);

    void mostrarNota(const Nota &reg)const;
    void mostrarNotasActivas();
    void listarAlumnos();

    NotaArchivo _notaArchivo;
    AlumnoArchivo _alumnoArchivo;
};
