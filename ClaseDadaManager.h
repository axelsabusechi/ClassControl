#pragma once
#include "ClaseDada.h"
#include "ClaseDadaArchivo.h"
#include "CursoArchivo.h"
#include "TemaArchivo.h"
#include "Fecha.h"

class ClaseDadaManager
{
public:
    ClaseDadaManager();

    void registrarClaseDada();
    void modificarClaseDada();
    void eliminarClaseDada();
    void listarClaseDada();

private:
    ClaseDada crearClaseDada();
    int seleccionarCurso();
    int seleccionarTema();
    void listarCursos();
    void listarTemas();
    void mostrarClaseDada(const ClaseDada &reg);
    void mostrarClasesDadasActivas();

    ClaseDadaArchivo _claseDadaArchivo;
    CursoArchivo _cursoArchivo;
    TemaArchivo _temaArchivo;
};
