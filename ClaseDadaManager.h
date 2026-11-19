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
    bool seleccionarEstadoClase();

    bool menuModificarClaseDada(ClaseDada &reg);
    void modificarFecha(ClaseDada &reg);
    void modificarObservaciones(ClaseDada &reg);
    void modificarClaseDada(ClaseDada &reg);
    void modificarTodos(ClaseDada &reg);

    void mostrarClaseDada(const ClaseDada &reg);
    void mostrarClasesDadasActivas();
    void listarCursos();
    void listarTemas();

    ClaseDadaArchivo _claseDadaArchivo;
    CursoArchivo _cursoArchivo;
    TemaArchivo _temaArchivo;
};
