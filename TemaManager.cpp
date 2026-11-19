#include <iostream>
#include "TemaManager.h"
#include "utils.h"
#include "rlutil.h"

TemaManager::TemaManager()
{
}

void TemaManager::registrarTema()
{

    rlutil::cls();
    std::cout << "===== REGISTRAR TEMA =====" << std::endl;

    if(_unidadDidacticaArchivo.getCantRegActivos() == 0)
    {
        if(mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo hay unidades didacticas registradas para asociar temas..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        rlutil::cls();
        return;
    }

    if(_temaArchivo.guardar(crearTema()) == ArchivoError::OK)
    {
        std::cout << "\nTema registrado con exito!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_temaArchivo.getLastError());
    }
    std::cout << "----------------------------------------" << std::endl;
    system("pause");
    rlutil::cls();
}

void TemaManager::modificarTema()
{
    rlutil::cls();
    std::cout << "===== MODIFICAR TEMA =====" << std::endl;

    int cantReg = _temaArchivo.getCantRegActivos();

    if(!cantReg)
    {
        if(mostrarErrorArchivo(_temaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo se registran temas para modificar..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    std::cout << std::endl;
    mostrarTemasActivos();

    int id = pedirEntero("\nId del tema a modificar: ");
    int index = _temaArchivo.buscarById(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_temaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nEl tema con ID " << id
                  << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Tema reg = _temaArchivo.leer(index);

    if(reg.getIdTema() == -1)
    {
        mostrarErrorArchivo(_temaArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "\nEl tema esta dado de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    if(!menuModificarTema(reg))
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    if(_temaArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "\nEl tema se modifico exitosamente!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_temaArchivo.getLastError());
    }
    std::cout << "----------------------------------------" << std::endl;
    system("pause");
}

void TemaManager::eliminarTema()
{
    rlutil::cls();
    std::cout << "===== DAR DE BAJA TEMA =====" << std::endl;

    int cantReg = _temaArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_temaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo hay temas registrados para dar de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    std::cout << std::endl;
    mostrarTemasActivos();

    int id = pedirEntero("\nId del tema a dar de baja: ");
    int index = _temaArchivo.buscarById(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_temaArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "\nEl tema con ID " << id
                  << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Tema reg = _temaArchivo.leer(index);

    if(reg.getIdTema() == -1)
    {
        mostrarErrorArchivo(_temaArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "\nEl tema ya esta dado de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    rlutil::cls();
    std::cout << "===== DAR DE BAJA TEMA =====" << std::endl;
    std::cout << "\n----- TEMA SELECCIONADO -----" << std::endl;
    mostrarTema(reg);
    std::cout << "----------------------------------------" << std::endl;

    bool eliminar = false;

    do
    {
        int opcion = pedirEntero("\nIngrese 1 para dar de baja, 0 para cancelar: ");

        if(opcion == 0 || opcion == 1)
        {
            eliminar = opcion;
            break;
        }

        std::cout << "ERROR. Ingrese 0 o 1." << std::endl;
    }
    while(true);


    if(eliminar)
    {
        reg.setEliminado(true);

        if(_temaArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "\nEl tema con ID " << id
                      << " se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_temaArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    system("pause");
}

void TemaManager::listarTema()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------LISTADO DE TEMAS--------------" << std::endl;
    cantReg = _temaArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No temas registrados..." << std::endl;
    }
    else
    {
        Tema *vTemas = new Tema[cantReg];
        _temaArchivo.leerTodos(vTemas, cantReg);

        for(int i=0; i<cantReg; i++)
        {
            if(!vTemas[i].getEliminado())
            {
                mostrarTema(vTemas[i]);
                std::cout << "--------------------------------------------" << std::endl;
            }
        }
        delete []vTemas;
    }
    system("pause");
    rlutil::cls();
}

Tema TemaManager::crearTema()
{
    int idTema, idUnidad, orden;
    std::string nombre;

    idTema = _temaArchivo.getNewId();

    rlutil::cls();
    std::cout << "===== REGISTRAR TEMA =====" << std::endl;
    std::cout << "ID Tema: " << idTema << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    idUnidad = seleccionarUnidadDidactica();
    std::cout << std::endl;
    nombre = pedirTexto("Nombre: ");
    std::cout << std::endl;
    orden = pedirEntero("Orden: ");

    return Tema(idTema,
                idUnidad,
                nombre,
                orden);
}

int TemaManager::seleccionarUnidadDidactica()
{
    listarUnidadesDidacticas();

    int idUnidad;
    bool existe = false;

    do
    {
        idUnidad = pedirEntero("\nId unidad didactica: ");
        existe = _unidadDidacticaArchivo.existeUnidad(idUnidad);

        if(!existe)
        {
            std::cout << "ERROR: El curso no existe..." << std::endl;
        }
    }
    while(!existe);

    return idUnidad;
}

bool TemaManager::menuModificarTema(Tema &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "===== MODIFICAR TEMA =====" << std::endl;
        std::cout << "\n----- DATOS ACTUALES -----" << std::endl;
        mostrarTema(reg);
        std::cout << "----------------------------------------" << std::endl;

        std::cout << "\n----- CAMPOS A MODIFICAR -----" << std::endl;
        std::cout << "1 - Nombre" << std::endl;
        std::cout << "2 - Orden" << std::endl;
        std::cout << "3 - Todos los campos" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "4 - Cancelar y salir" << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        opcion = pedirEntero("Opcion: ");

        switch(opcion)
        {
        case 1:
            modificarNombre(reg);
            break;

        case 2:
            modificarOrden(reg);
            break;

        case 3:
            modificarTodos(reg);
            break;

        case 4:
            return false;

        case 0:
            return true;

        default:
            std::cout << "ERROR. Opcion invalida." << std::endl;
            system("pause");
        }

        if(opcion >= 1 && opcion <= 3)
        {
            std::cout << "\nCampo modificado..." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            system("pause");
        }
    }
    while(true);

    return false;
}

void TemaManager::modificarNombre(Tema &reg)
{
    std::cout << std::endl;
    reg.setNombre(pedirTexto("Nuevo nombre: "));
}

void TemaManager::modificarOrden(Tema &reg)
{
    std::cout << std::endl;
    reg.setOrden(pedirEntero("Nuevo orden: "));
}

void TemaManager::modificarTodos(Tema &reg)
{
    modificarNombre(reg);
    modificarOrden(reg);
}

void TemaManager::mostrarTema(const Tema &reg)
{
    int indexUnidad = _unidadDidacticaArchivo.buscarByID(reg.getIdUnidad());

    UnidadDidactica regUnidad;

    if(indexUnidad != -1)
    {
        regUnidad = _unidadDidacticaArchivo.leer(indexUnidad);
    }

    std::cout << "Id: " << reg.getIdTema() << std::endl;

    if(indexUnidad != -1)
    {
        std::cout << "Unidad didactica: "
                  << regUnidad.getNombre()
                  << " "
                  << regUnidad.getOrden()
                  << std::endl;
    }

    std::cout << "Nombre: " << reg.getNombre() << std::endl;
    std::cout << "Orden: " << reg.getOrden() << std::endl;
}

void TemaManager::mostrarTemasActivos()
{
    Tema reg;
    int cantReg;

    cantReg = _temaArchivo.getCantReg();

    std::cout << "----- TEMAS ACTIVOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _temaArchivo.leer(i);

        if(reg.getIdTema() == -1)
        {
            mostrarErrorArchivo(_temaArchivo.getLastError());
            system("pause");
            return;
        }

        if(!reg.getEliminado())
        {
            mostrarTema(reg);
            std::cout << "----------------------------------------" << std::endl;
        }
    }
}

void TemaManager::listarUnidadesDidacticas()
{
    int cantReg = _unidadDidacticaArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "\nNo hay unidades didacticas registradas..." << std::endl;
        return;
    }

    UnidadDidactica *vUnidadesDidacticas = new UnidadDidactica[cantReg];
    _unidadDidacticaArchivo.leerTodos(vUnidadesDidacticas, cantReg);

    std::cout << "\n----- UNIDADES DIDACTICAS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vUnidadesDidacticas[i].getEliminado())
        {
            std::cout << "Id: "<< vUnidadesDidacticas[i].getIdUnidad() << std::endl;
            std::cout << "Nombre: " << vUnidadesDidacticas[i].getNombre() << std::endl;
            std::cout << "Orden: " << vUnidadesDidacticas[i].getOrden() << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
        }
    }

    delete[] vUnidadesDidacticas;
}



