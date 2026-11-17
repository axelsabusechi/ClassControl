#include "UnidadDidacticaMenu.h"

UnidadDidacticaMenu::UnidadDidacticaMenu()
    : Menu(4)
{
    setOpciones(1, "          Registrar unidad didactica        ");
    setOpciones(2, "          Modificar unidad didactica        ");
    setOpciones(3, "       Dar de baja una unidad didactica     ");
    setOpciones(4, "          Listar unidades didacticas        ");
    setTituloMenu("Unidades Didacticas");
    setOpCero("           Volver al menu principal         ");
}

void UnidadDidacticaMenu::runUnidadDidactica()
{
    bool salir = false;

    do
    {
        int opcion = runMenu();
        switch(opcion)
        {
            case 0: _unidadDidacticaManager.registrarUnidadDidactica(); break;
            case 1: _unidadDidacticaManager.modificarUnidadDidactica(); break;
            case 2: _unidadDidacticaManager.eliminarUnidadDidactica(); break;
            case 3: _unidadDidacticaManager.listarUnidadDidactica(); break;
            case 4: salir = true;
        }
    }while(!salir);
}
