#include "TemaMenu.h"

TemaMenu::TemaMenu()
    : Menu(4)
{
    setOpciones(1, "               Registrar tema               ");
    setOpciones(2, "               Modificar tema               ");
    setOpciones(3, "             Dar de baja un tema            ");
    setOpciones(4, "                Listar temas                ");
    setTituloMenu("      Temas        ");
    setOpCero("           Volver al menu principal         ");
}

void TemaMenu::runTema()
{
    bool salir = false;

    do
    {
        int opcion = runMenu();
        switch(opcion)
        {
            case 0: _temaManager.registrarTema(); break;
            case 1: _temaManager.modificarTema(); break;
            case 2: _temaManager.eliminarTema(); break;
            case 3: _temaManager.listarTema(); break;
            case 4: salir = true;
        }
    }while(!salir);
}
