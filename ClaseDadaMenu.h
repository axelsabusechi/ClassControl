#pragma once
#include "Menu.h"
#include "ClaseDadaManager.h"

class ClaseDadaMenu:public Menu
{
public:
    ClaseDadaMenu();
    void runClaseDada();
private:
    ClaseDadaManager _claseDadaManager;
};
