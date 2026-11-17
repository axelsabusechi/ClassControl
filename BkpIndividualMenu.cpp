#include "BkpIndividualMenu.h"

BkpIndividualMenu::BkpIndividualMenu()
    :Menu(9)
{
    setOpciones(1, "               Back up Alumnos              ");
    setOpciones(2, "               Back up Docentes             ");
    setOpciones(3, "               Back up Cursos               ");
    setOpciones(4, "           Back up Inscripciones            ");
    setOpciones(5, "            Back up Asignaciones            ");
    setOpciones(6, "           Back up Clases Dadas             ");
    setOpciones(7, "         Back up Unidades Didacticas        ");
    setOpciones(8, "               Back up Temas                ");
    setOpciones(9, "               Back up Notas                ");
    setTituloMenu("    Menu Back up   ");
    setOpCero("        Volver al menu mantenimiento        ");
}

void BkpIndividualMenu::runBkpIndividualMenu()
{
    bool salir = false;

    do
    {
        int opcion = runMenu();
        switch(opcion)
        {
        case 0: _mantenimientoManager.backupAlumnos(); break;
        case 1: _mantenimientoManager.backupDocentes(); break;
        case 2: _mantenimientoManager.backupCursos(); break;
        case 3: _mantenimientoManager.backupInscripciones(); break;
        case 4: _mantenimientoManager.backupAsignaciones(); break;
        case 5: _mantenimientoManager.backupClasesDadas(); break;
        case 6: _mantenimientoManager.backupUnidadesDidacticas(); break;
        case 7: _mantenimientoManager.backupTemas(); break;
        case 8: _mantenimientoManager.backupNotas(); break;
        case 9: salir = true;
        }
    }
    while(!salir);

}
