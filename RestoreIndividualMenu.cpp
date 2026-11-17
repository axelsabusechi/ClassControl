#include "RestoreIndividualMenu.h"

RestoreIndividualMenu::RestoreIndividualMenu()
    :Menu(9)
{
    setOpciones(1, "               Restore Alumnos              ");
    setOpciones(2, "               Restore Docentes             ");
    setOpciones(3, "               Restore Cursos               ");
    setOpciones(4, "           Restore Inscripciones            ");
    setOpciones(5, "            Restore Asignaciones            ");
    setOpciones(6, "           Restore Clases Dadas             ");
    setOpciones(7, "         Restore Unidades Didacticas        ");
    setOpciones(8, "               Restore Temas                ");
    setOpciones(9, "               Restore Notas                ");
    setTituloMenu("    Menu Restore   ");
    setOpCero("       Volver al menu Mantenimiento         ");
}

void RestoreIndividualMenu::runRestoreIndividualMenu()
{
    bool salir = false;

    do
    {
        int opcion = runMenu();
        switch(opcion)
        {
        case 0: _mantenimientoManager.restoreAlumnos(); break;
        case 1: _mantenimientoManager.restoreDocentes(); break;
        case 2: _mantenimientoManager.restoreCursos(); break;
        case 3: _mantenimientoManager.restoreInscripciones(); break;
        case 4: _mantenimientoManager.restoreAsignaciones(); break;
        case 5: _mantenimientoManager.restoreClasesDadas(); break;
        case 6: _mantenimientoManager.restoreUnidadesDidacticas(); break;
        case 7: _mantenimientoManager.restoreTemas(); break;
        case 8: _mantenimientoManager.restoreNotas(); break;
        case 9: salir = true;
        }
    }
    while(!salir);

}
