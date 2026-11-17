#pragma once
#include "Menu.h"
#include "MantenimientoManager.h"
#include "BkpIndividualMenu.h"
#include "RestoreIndividualMenu.h"

class MantenimientoMenu:public Menu
{
public:
    MantenimientoMenu();
    void runMantenimiento();
private:
    BkpIndividualMenu _bkpIndividualMenu;
    RestoreIndividualMenu _restoreIndividualMenu;
    MantenimientoManager _mantenimientoManager;
};
