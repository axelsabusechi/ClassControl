#include "InformesMenu.h"

InformesMenu::InformesMenu()
    :Menu(5)
{
    setOpciones(1, "        Cantidad de alumnos por grado       ");
    setOpciones(2, "        Promedio de notas por alumno        ");
    setOpciones(3, "   Cantidad de clases suspendidas por curso ");
    setOpciones(4, "        Rendimiento academico por curso     ");
    setOpciones(5, "             Avance curricular por curso    ");
    setTituloMenu("     Informes      ");
    setOpCero("           Volver al menu principal         ");
}

void InformesMenu::runInformes()
{
    bool salir = false;

    do
    {
        int opcion = runMenu();
        switch(opcion)
        {
        case 0: _informesManager.cantidadAlumnosPorGrado(); break;
        case 1: _informesManager.promedioNotasPorAlumno(); break;
        case 2: _informesManager.cantidadClasesSuspendidasPorCurso(); break;
        case 3: _informesManager.historialRendimientoPorCurso(); break;
        case 4: _informesManager.avanceCurricularPorCurso(); break;
        case 5: salir = true;
        }
    }while(!salir);
}
