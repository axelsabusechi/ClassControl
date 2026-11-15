#include "AsignacionDocenteMenu.h"

AsignacionDocenteMenu::AsignacionDocenteMenu()
:Menu(4)
{
    setOpciones(1, "               Asignar docente              ");
    setOpciones(2, "             Dar de baja asignacion         ");
    setOpciones(3, "              Modificar asignacion          ");
    setOpciones(4, "         Listar asignaciones docentes       ");
    setTituloMenu("    Asignaciones   ");
    setOpCero("           Volver al menu principal         ");
}

void AsignacionDocenteMenu::runAsignacionDocente()
{
    bool salir = false;

    do
    {
        int opcion = runMenu();
        switch(opcion)
        {
            case 0: _asignacionDocenteManager.registrarAsignacionDocente(); break;
            case 1: _asignacionDocenteManager.eliminarAsignacionDocente(); break;
            case 2: _asignacionDocenteManager.modificarAsignacionDocente(); break;
            case 3: _asignacionDocenteManager.listarAsignacionesDocentes(); break;
            case 4: salir = true;
        }
    }while(!salir);
}
