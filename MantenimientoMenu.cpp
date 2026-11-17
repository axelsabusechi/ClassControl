#include "MantenimientoMenu.h"

MantenimientoMenu::MantenimientoMenu()
    :Menu(4)
{
    setOpciones(1, "               Back up individual           ");
    setOpciones(2, "               Restore individual           ");
    setOpciones(3, "                 Back up general            ");
    setOpciones(4, "                 Restore general            ");
    setTituloMenu("    Mantenimiento  ");
    setOpCero("           Volver al menu principal         ");
}

void MantenimientoMenu::runMantenimiento()
{
    bool salir = false;

    do
    {
        int opcion = runMenu();
        switch(opcion)
        {
        case 0: _bkpIndividualMenu.runBkpIndividualMenu(); break;
        case 1: _restoreIndividualMenu.runRestoreIndividualMenu(); break;
        case 2: _mantenimientoManager.backupGeneral(); break;
        case 3: _mantenimientoManager.restoreGeneral(); break;
        case 4: salir = true;
        }
    }
    while(!salir);

}
