#pragma once
#include "Menu.h"
#include "MantenimientoManager.h"

class RestoreIndividualMenu:public Menu
{
public:
    RestoreIndividualMenu();
    void runRestoreIndividualMenu();

private:
    MantenimientoManager _mantenimientoManager;
};
