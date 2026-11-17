#pragma once
#include "UnidadDidactica.h"
#include "UnidadDidacticaArchivo.h"
#include "CursoArchivo.h"

class UnidadDidacticaManager
{
public:
    void registrarUnidadDidactica();
    void modificarUnidadDidactica();
    void eliminarUnidadDidactica();
    void listarUnidadDidactica();
private:
    UnidadDidactica crearUnidadDidactica();
    int seleccionarCurso();
    void listarCursos();
    void mostrarUnidadesDidacticasActivas();
    void mostrarUnidadDidactica(const UnidadDidactica &reg);
    bool menuModificarUnidadDidactica(const UnidadDidactica &reg);
    void modificarNombre(UnidadDidactica reg);
    void modificarOrden(UnidadDidactica reg);
    void modificarTodos(UnidadDidactica reg);



    UnidadDidacticaArchivo _unidadDidacticaArchivo;
    CursoArchivo _cursoArchivo;

};
