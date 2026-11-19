#pragma once
#include "Tema.h"
#include "TemaArchivo.h"
#include "UnidadDidacticaArchivo.h"

class TemaManager
{
public:
    TemaManager();

    void registrarTema();
    void modificarTema();
    void eliminarTema();
    void listarTema();
private:
    Tema crearTema();

    int seleccionarUnidadDidactica();

    bool menuModificarTema(Tema &reg);
    void modificarNombre(Tema &reg);
    void modificarOrden(Tema &reg);
    void modificarTodos(Tema &reg);

    void mostrarTema(const Tema &reg);
    void mostrarTemasActivos();
    void listarUnidadesDidacticas();

    TemaArchivo _temaArchivo;
    UnidadDidacticaArchivo _unidadDidacticaArchivo;
};
