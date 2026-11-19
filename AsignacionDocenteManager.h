#pragma once
#include "AsignacionDocente.h"
#include "AsignacionDocenteArchivo.h"
#include "DocenteArchivo.h"
#include "CursoArchivo.h"
#include "ArchivoError.h"

class AsignacionDocenteManager
{
public:
    AsignacionDocenteManager();

    void registrarAsignacionDocente();
    void modificarAsignacionDocente();
    void eliminarAsignacionDocente();
    void listarAsignacionesDocentes();

private:
    AsignacionDocente crearAsignacionDocente();
    void cargarAsignacionUnica(int &idDocente, int &idCurso);

    int seleccionarDocente();
    int seleccionarCurso();

    bool menuModificarAsignacion(AsignacionDocente &reg);
    void mostrarAsignacionDocente(const AsignacionDocente &reg);
    void mostrarAsignacionesActivas();
    void listarDocentes();
    void listarCursos();

    AsignacionDocenteArchivo _asignacionDocenteArchivo;
    DocenteArchivo _docenteArchivo;
    CursoArchivo _cursoArchivo;
};
