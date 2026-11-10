#include <iostream>
#include "DocenteManager.h"
#include "utils.h"
#include "rlutil.h"

DocenteManager::DocenteManager()
{
}

void DocenteManager::registrarDocente()
{
    if(_docenteArchivo.guardar(crearDocente()) == ArchivoError::OK)
    {
        std::cout << "Docente registrado..." << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_docenteArchivo.getLastError());
    }
    system("pause");
    rlutil::cls();
}

void DocenteManager::modificarDocente()
{
    rlutil::cls();
    int index, idDocente, cantReg;
    Docente reg;

    cantReg = _docenteArchivo.getCantRegActivos();

    if(!cantReg)
    {
        if(mostrarErrorArchivo(_docenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay docentes registrados para modificar..." << std::endl;
        system("pause");
        return;
    }

    mostrarDocentesActivos();

    idDocente = pedirEntero("ID del Docente a modificar: ");

    index = _docenteArchivo.buscarByID(idDocente);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_docenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "El Docente con ID " << idDocente << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    reg = _docenteArchivo.leer(index);

    if(reg.getIdDocente() == -1)
    {
        mostrarErrorArchivo(_docenteArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "El docente esta dado de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarDocente(reg);

    if(!menuModificarDocente(reg))
    {
        std::cout << "Operacion cancelada..." << std::endl;
        system("pause");
        return;
    }

    if(_docenteArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "El docente se modifico exitosamente!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_docenteArchivo.getLastError());
    }

    system("pause");
}

void DocenteManager::eliminarDocente()
{
    rlutil::cls();
    int index, idDocente, cantReg;
    Docente reg;

    cantReg = _docenteArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_docenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay docentes registrados para dar de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarDocentesActivos();

    idDocente = pedirEntero("ID del Docente a dar de baja: ");

    index = _docenteArchivo.buscarByID(idDocente);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_docenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "El docente con ID " << idDocente << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    reg = _docenteArchivo.leer(index);

    if(reg.getIdDocente() == -1)
    {
        mostrarErrorArchivo(_docenteArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "El docente esta dado de baja." << std::endl;
        system("pause");
        return;
    }

    mostrarDocente(reg);
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

        if(_docenteArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "El docente con ID " << idDocente << " se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_docenteArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "Operacion cancelada..." << std::endl;
    }

    system("pause");
}

void DocenteManager::listarDocentes()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------LISTADO DE DOCENTES--------------" << std::endl;
    cantReg = _docenteArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay docentes registrados..." << std::endl;
    }
    else
    {
        Docente *vDocentes = new Docente[cantReg];
        _docenteArchivo.leerTodos(vDocentes,cantReg);

        for(int i=0; i<cantReg; i++)
        {
            if(!vDocentes[i].getEliminado())
            {
                mostrarDocente(vDocentes[i]);
                std::cout << "--------------------------------------------" << std::endl;
            }
        }
        delete []vDocentes;
    }
    system("pause");
    rlutil::cls();
}

Docente DocenteManager::crearDocente()
{
    int idDocente;
    std::string nombre,apellido,dni;

    idDocente = _docenteArchivo.getNewID();

    rlutil::cls();

    std::cout << "-----CARGAR DOCENTE-------" << std::endl;
    std::cout << "ID: " << idDocente << std::endl << std::endl;

    cargarDocente(nombre,
                  apellido,
                  dni);

    return Docente(nombre,
                   apellido,
                   dni,
                   idDocente);
}

void DocenteManager::cargarDocente(std::string &nombre,
                                   std::string &apellido,
                                   std::string &dni)
{
    nombre = pedirNombreApellido("Nombre: ");
    apellido = pedirNombreApellido("Apellido: ");
    dni = pedirDniUnico("DNI: ");
}

void DocenteManager::mostrarDocente(const Docente &reg)
{
    std::cout << "ID: " << reg.getIdDocente() << std::endl;
    std::cout << "Nombre: " << reg.getNombre() << std::endl;
    std::cout << "Apellido: " << reg.getApellido() << std::endl;
    std::cout << "DNI: " << reg.getDni() << std::endl;
}

void DocenteManager::mostrarDocentesActivos()
{
    Docente reg;
    int cantReg;

    cantReg = _docenteArchivo.getCantReg();

    std::cout << "----- DOCENTES ACTIVOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _docenteArchivo.leer(i);

        if(reg.getIdDocente() == -1)
        {
            mostrarErrorArchivo(_docenteArchivo.getLastError());
            system("pause");
            return;
        }

        if(!reg.getEliminado())
        {
            mostrarDocente(reg);
            std::cout << "----------------------------------" << std::endl;
        }
    }
}

std::string DocenteManager::pedirDniUnico(const std::string &mensaje, int idIgnorar)
{
    std::string dni;
    bool existe = false;

    do
    {
        dni = pedirDni(mensaje);
        existe = _docenteArchivo.existeDni(dni,idIgnorar);

        if(existe)
        {
            std::cout << "ERROR: Ya existe un docente con ese DNI..." << std::endl;
        }
    }
    while(existe);
    return dni;
}

bool DocenteManager::menuModificarDocente(Docente &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "----- DATOS ACTUALES DEL DOCENTE -----" << std::endl;
        mostrarDocente(reg);

        std::cout << "\n----- MODIFICAR DOCENTE -----" << std::endl;
        std::cout << "1 - Nombre" << std::endl;
        std::cout << "2 - Apellido" << std::endl;
        std::cout << "3 - DNI" << std::endl;
        std::cout << "4 - Todos los campos" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "5 - Cancelar y salir " << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;

        opcion = pedirEntero("Opcion: ");

        switch(opcion)
        {
        case 1:
            modificarNombre(reg);
            break;

        case 2:
            modificarApellido(reg);
            break;

        case 3:
            modificarDni(reg);
            break;

        case 4:
            modificarTodos(reg);
            break;

        case 5:
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

void DocenteManager::modificarNombre(Docente &reg)
{
    reg.setNombre(pedirNombreApellido("Nuevo nombre: "));
}

void DocenteManager::modificarApellido(Docente &reg)
{
    reg.setApellido(pedirNombreApellido("Nuevo apellido: "));
}

void DocenteManager::modificarDni(Docente &reg)
{
    reg.setDni(pedirDniUnico(("Nuevo DNI: "),reg.getIdDocente()));
}

void DocenteManager::modificarTodos(Docente &reg)
{
    modificarNombre(reg);
    modificarApellido(reg);
    modificarDni(reg);
}
