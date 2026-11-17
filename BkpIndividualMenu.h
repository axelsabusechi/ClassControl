#pragma once
#include "Menu.h"
#include "MantenimientoManager.h"

class BkpIndividualMenu:public Menu
{
public:
    BkpIndividualMenu();
    void runBkpIndividualMenu();

private:
    MantenimientoManager _mantenimientoManager;
};
