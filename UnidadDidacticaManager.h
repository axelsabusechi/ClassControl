#pragma once
#include "UnidadDidactica.h"
#include "UnidadDidacticaArchivo.h"
#include "CursoArchivo.h"

class UnidadDidacticaManager
{
public:
    UnidadDidacticaManager();

    void registrarUnidadDidactica();
    void modificarUnidadDidactica();
    void eliminarUnidadDidactica();
    void listarUnidadDidactica();
private:
    UnidadDidactica crearUnidadDidactica();

    int seleccionarCurso();

    bool menuModificarUnidadDidactica(UnidadDidactica &reg);
    void modificarNombre(UnidadDidactica &reg);
    void modificarOrden(UnidadDidactica &reg);
    void modificarTodos(UnidadDidactica &reg);

    void mostrarUnidadDidactica(const UnidadDidactica &reg);
    void mostrarUnidadesDidacticasActivas();

    void listarCursos();

    UnidadDidacticaArchivo _unidadDidacticaArchivo;
    CursoArchivo _cursoArchivo;
};
