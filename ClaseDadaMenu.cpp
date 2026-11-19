#include "ClaseDadaMenu.h"

ClaseDadaMenu::ClaseDadaMenu()
    : Menu(4)
{
    setOpciones(1, "            Registrar clase dada            ");
    setOpciones(2, "            Modificar clase dada            ");
    setOpciones(3, "          Dar de baja una clase dada        ");
    setOpciones(4, "                Listar clase dada           ");
    setTituloMenu("   Clases dadas    ");
    setOpCero("           Volver al menu principal         ");
}

void ClaseDadaMenu::runClaseDada()
{
    bool salir = false;

    do
    {
        int opcion = runMenu();
        switch(opcion)
        {
        case 0: _claseDadaManager.registrarClaseDada(); break;
        case 1: _claseDadaManager.modificarClaseDada(); break;
        case 2: _claseDadaManager.eliminarClaseDada(); break;
        case 3: _claseDadaManager.listarClaseDada(); break;
        case 4: salir = true;
        }
    }while(!salir);
}
