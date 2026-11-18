#include <iostream>
#include "UnidadDidacticaManager.h"
#include "utils.h"
#include "rlutil.h"

void UnidadDidacticaManager::registrarUnidadDidactica()
{
    if(_unidadDidacticaArchivo.guardar(crearUnidadDidactica()) == ArchivoError::OK)
    {
        std::cout << "Unidad didactica registrada..." << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError());
    }
    system("pause");
    rlutil::cls();
}

void UnidadDidacticaManager::modificarUnidadDidactica()
{
    rlutil::cls();

    int cantReg = _unidadDidacticaArchivo.getCantRegActivos();

    if(!cantReg)
    {
        if(mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No se registran unidades didacticas para modificar..." << std::endl;
        system("pause");
        return;
    }

    mostrarUnidadesDidacticasActivas();

    int id = pedirEntero("Id de la unidad didactica a modificar: ");
    int index = _unidadDidacticaArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "La unidad didactica con " << id << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    UnidadDidactica reg = _unidadDidacticaArchivo.leer(index);

    if(reg.getIdUnidad() == -1)
    {
        mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "La unidad didactica esta dada de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarUnidadDidactica(reg);

    if(!menuModificarUnidadDidactica(reg))
    {
        std::cout << "Operacion cancelada..." << std::endl;
        system("pause");
        return;
    }

    if(_unidadDidacticaArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "La unidad didactica se modifico exitosamente!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError());
    }

    system("pause");
}

void UnidadDidacticaManager::eliminarUnidadDidactica()
{
    rlutil::cls();

    int cantReg = _unidadDidacticaArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay unidades didacticas registrados para dar de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarUnidadesDidacticasActivas();

    int id = pedirEntero("Id de la unidad didactica a dar de baja: ");
    int index = _unidadDidacticaArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "La unidad didactica con id " << id << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    UnidadDidactica reg = _unidadDidacticaArchivo.leer(index);

    if(reg.getIdUnidad() == -1)
    {
        mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "La unidad didactica esta dada de baja." << std::endl;
        system("pause");
        return;
    }

    mostrarUnidadDidactica(reg);

    bool eliminar = false;

    do
    {
        int opcion = pedirEntero("Ingrese 1 para dar de baja, 0 para cancelar: ");

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

        if(_unidadDidacticaArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "La unidad didactica con id " << id << " se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "Operacion cancelada..." << std::endl;
    }

    system("pause");
}

void UnidadDidacticaManager::listarUnidadDidactica()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------LISTADO UNIDADES DIDACTICAS--------------" << std::endl;
    cantReg = _unidadDidacticaArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay unidades didacticas registradas..." << std::endl;
    }
    else
    {
        UnidadDidactica *vUnidadesDidacticas = new UnidadDidactica[cantReg];
        _unidadDidacticaArchivo.leerTodos(vUnidadesDidacticas, cantReg);

        for(int i=0; i<cantReg; i++)
        {
            if(!vUnidadesDidacticas[i].getEliminado())
            {
                mostrarUnidadDidactica(vUnidadesDidacticas[i]);
                std::cout << "--------------------------------------------" << std::endl;
            }
        }
        delete []vUnidadesDidacticas;
    }
    system("pause");
    rlutil::cls();
}

UnidadDidactica UnidadDidacticaManager::crearUnidadDidactica()
{
    rlutil::cls();

    int idUnidad, idCurso, orden;
    std::string nombre;

    idUnidad = _unidadDidacticaArchivo.getNewID();
    idCurso = seleccionarCurso();
    nombre = pedirTexto("Nombre: ");
    orden = pedirEntero("Orden: ");

    return UnidadDidactica(idUnidad,
                           idCurso,
                           nombre,
                           orden);
}

int UnidadDidacticaManager::seleccionarCurso()
{
    listarCursos();

    int idCurso;
    bool existe = false;

    do
    {
        idCurso = pedirEntero("Id curso: ");
        existe = _cursoArchivo.existeCurso(idCurso);

        if(!existe)
        {
            std::cout << "ERROR: El curso no existe..." << std::endl;
        }
    }
    while(!existe);

    return idCurso;
}

void UnidadDidacticaManager::listarCursos()
{
    int cantReg;
    cantReg = _cursoArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "No hay cursos registrados..." << std::endl;
        return;
    }

    Curso *vCursos;

    vCursos = new Curso[cantReg];
    _cursoArchivo.leerTodos(vCursos, cantReg);

    std::cout << "----- CURSOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vCursos[i].getEliminado())
        {
            std::cout << "Id: "<< vCursos[i].getIdCurso() << std::endl;
            std::cout << "Grado: " << gradoToString(vCursos[i].getGrado()) << std::endl;
            std::cout << "Division: " << divisionToString(vCursos[i].getDivision()) << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
        }
    }

    delete[] vCursos;
}

void UnidadDidacticaManager::mostrarUnidadesDidacticasActivas()
{
    UnidadDidactica reg;
    int cantReg;

    cantReg = _unidadDidacticaArchivo.getCantReg();

    std::cout << "----- UNIDADES DIDACTICAS ACTIVAS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _unidadDidacticaArchivo.leer(i);

        if(reg.getIdUnidad() == -1)
        {
            mostrarErrorArchivo(_unidadDidacticaArchivo.getLastError());
            system("pause");
            return;
        }

        if(!reg.getEliminado())
        {
            mostrarUnidadDidactica(reg);
            std::cout << "----------------------------------" << std::endl;
        }
    }
}

void UnidadDidacticaManager::mostrarUnidadDidactica(const UnidadDidactica &reg)
{
    int indexCurso = _cursoArchivo.buscarByID(reg.getIdCurso());

    Curso regCurso;

    if(indexCurso != -1)
    {
        regCurso = _cursoArchivo.leer(indexCurso);
    }

    std::cout << "Id: " << reg.getIdUnidad() << std::endl;

    if(indexCurso != -1)
    {
        std::cout << "Curso: "
                  << gradoToString(regCurso.getGrado())
                  << " "
                  << divisionToString(regCurso.getDivision())
                  << std::endl;
    }

    std::cout << "Nombre: " << reg.getNombre() << std::endl;
    std::cout << "Orden: " << reg.getOrden() << std::endl;
}

bool UnidadDidacticaManager::menuModificarUnidadDidactica(UnidadDidactica &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "----- DATOS ACTUALES DE LA UNIDAD DIDACTICA -----" << std::endl;
        mostrarUnidadDidactica(reg);

        std::cout << "\n----- MODIFICAR UNIDAD DIDACTICA -----" << std::endl;
        std::cout << "1 - Nombre" << std::endl;
        std::cout << "2 - Orden" << std::endl;
        std::cout << "3 - Todos los campos" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "4 - Cancelar y salir " << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;

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
        }

        if(opcion >= 1 && opcion <= 4)
        {
            std::cout << "Campo modificado..." << std::endl;
            system("pause");
        }
    }
    while(true);

    return false;
}

void UnidadDidacticaManager::modificarNombre(UnidadDidactica &reg)
{
    reg.setNombre(pedirTexto("Nuevo nombre: "));
}

void UnidadDidacticaManager::modificarOrden(UnidadDidactica &reg)
{
    reg.setOrden(pedirEntero("Nuevo orden: "));
}

void UnidadDidacticaManager::modificarTodos(UnidadDidactica &reg)
{
    modificarNombre(reg);
    modificarOrden(reg);
}





