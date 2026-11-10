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
    void eliminarAsignacionDocente();
    void listarAsignacionesDocentes();

private:
    AsignacionDocente crearAsignacionDocente();
    void mostrarAsignacionDocente(const AsignacionDocente &reg);
    void mostrarAsignacionesActivas();
    void pedirAsignacionUnica(int &idDocente, int &idCurso);
    void listarDocentes();
    void listarCursos();
    int seleccionarDocente();
    int seleccionarCurso();

    AsignacionDocenteArchivo _asignacionDocenteArchivo;
    DocenteArchivo _docenteArchivo;
    CursoArchivo _cursoArchivo;
};
