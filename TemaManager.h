#pragma once
#include "Tema.h"
#include "TemaArchivo.h"
#include "UnidadDidacticaArchivo.h"

class TemaManager
{
public:
    void registrarTema();
    void modificarTema();
    void eliminarTema();
    void listarTema();
private:
    Tema crearTema();
    int seleccionarUnidadDidactica();
    void listarUnidadesDidacticas();
    void mostrarTemasActivos();
    void mostrarTema(const Tema &reg);
    bool menuModificarTema(Tema &reg);
    void modificarNombre(Tema &reg);
    void modificarOrden(Tema &reg);
    void modificarTodos(Tema &reg);

    TemaArchivo _temaArchivo;
    UnidadDidacticaArchivo _unidadDidacticaArchivo;
};
