#include <iostream>
#include "NotaManager.h"
#include "utils.h"
#include "rlutil.h"

NotaManager::NotaManager()
{
}

void NotaManager::registrarNota()
{
    if(_notaArchivo.guardar(crearNota()) == ArchivoError::OK)
    {
        std::cout << "Nota registrada..." << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_notaArchivo.getLastError());
    }
    system("pause");
    rlutil::cls();
}

void NotaManager::modificarNota()
{
    rlutil::cls();

    int cantReg = _notaArchivo.getCantRegActivos();

    if(!cantReg)
    {
        if(mostrarErrorArchivo(_notaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay notas registradas para modificar..." << std::endl;
        system("pause");
        return;
    }

    mostrarNotasActivas();

    int id = pedirEntero("Id de la nota a modificar: ");
    int index = _notaArchivo.buscarById(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_notaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "La nota con Id " << id << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    Nota reg = _notaArchivo.leer(index);

    if(reg.getIdNota() == -1)
    {
        mostrarErrorArchivo(_notaArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "La nota esta dada de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarNota(reg);

    if(!menuModificarNota(reg))
    {
        std::cout << "Operacion cancelada..." << std::endl;
        system("pause");
        return;
    }

    if(_notaArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "La nota se modifico exitosamente!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_notaArchivo.getLastError());
    }

    system("pause");
}

void NotaManager::eliminarNota()
{
    rlutil::cls();

    int cantReg = _notaArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_notaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay notas registradas para dar de baja..." << std::endl;
        std::cout << std::endl;
        system("pause");
        return;
    }

    mostrarNotasActivas();

    int id = pedirEntero("Id de la nota a dar de baja: ");
    int index = _notaArchivo.buscarById(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_notaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "La nota con Id " << id  << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    Nota reg = _notaArchivo.leer(index);

    if(reg.getIdNota() == -1)
    {
        mostrarErrorArchivo(_notaArchivo.getLastError());
        std::cout << std::endl;
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "La nota esta dada de baja." << std::endl;
        std::cout << std::endl;
        system("pause");
        return;
    }

    mostrarNota(reg);
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
        std::cout << std::endl;
    }
    while(true);


    if(eliminar)
    {
        reg.setEliminado(true);

        if(_notaArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "La nota se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_notaArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "Operacion cancelada..." << std::endl;
    }

    std::cout << std::endl;
    system("pause");

}

void NotaManager::listarNotas()
{
    rlutil::cls();

    std::cout << "-------------LISTADO DE NOTAS--------------" << std::endl;
    int cantReg = _notaArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay notas registradas..." << std::endl;
        std::cout << std::endl;
    }
    else
    {
        Nota *vNotas = new Nota[cantReg];
        _notaArchivo.leerTodos(vNotas, cantReg);

        for(int i=0; i<cantReg; i++)
        {
            if(!vNotas[i].getEliminado())
            {
                std::cout << "ID: " << vNotas[i].getIdNota() << std::endl;
                std::cout << "Legajo: " << vNotas[i].getLegajo() << std::endl;
                std::cout << "Periodo: " << periodoToString(vNotas[i].getPeriodo()) << std::endl;
                std::cout << "Nota: " << vNotas[i].getNota() << std::endl;
                std::cout << "Fecha de carga: " << vNotas[i].getFechaCarga().toString() << std::endl;
                std::cout << "Descripcion: " << vNotas[i].getDescripcion() << std::endl;
                std::cout << "--------------------------------------------" << std::endl;
            }
        }

        delete []vNotas;
    }
    system("pause");
    rlutil::cls();

}

Nota NotaManager::crearNota()
{
    int idNota, legajo, nota;
    Periodo periodo;
    std::string descripcion;
    Fecha fechaCarga;

    idNota = _notaArchivo.getNewId();

    rlutil::cls();

    std::cout << "------CARGAR NOTA-------" << std::endl;
    std::cout << "Id " << idNota << std::endl;

    legajo = seleccionarAlumno();
    periodo = pedirPeriodo();
    fechaCarga.cargarFechaActual();
    descripcion = pedirTexto("Descripcion: ");
    nota = pedirNota();

    return Nota(idNota,
                legajo,
                periodo,
                nota,
                fechaCarga,
                descripcion);
}


void NotaManager::mostrarNota(const Nota &reg)
{
    std::cout << "ID: " << reg.getIdNota() << std::endl;
    std::cout << "Legajo: " << reg.getLegajo() << std::endl;
    std::cout << "Periodo: " << periodoToString(reg.getPeriodo()) << std::endl;
    std::cout << "Nota: " << reg.getNota() << std::endl;
    std::cout << "Fecha de carga: " << reg.getFechaCarga().toString() << std::endl;
    std::cout << "Descripcion: " << reg.getDescripcion() << std::endl;
}

void NotaManager::mostrarNotasActivas()
{
    Nota reg;

    int cantReg = _notaArchivo.getCantReg();

    std::cout << "----- NOTAS ACTIVAS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _notaArchivo.leer(i);

        if(reg.getIdNota() == -1)
        {
            mostrarErrorArchivo(_notaArchivo.getLastError());
            std::cout << std::endl;
            system("pause");
            return;
        }

        if(!reg.getEliminado())
        {
            mostrarNota(reg);
            std::cout << "----------------------------------" << std::endl;
        }
    }

}

void NotaManager::listarAlumnos()
{
    int cantReg;

    cantReg = _alumnoArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "No hay alumnos registrados..." << std::endl;
        system("pause");
        return;
    }

    Alumno *vAlumnos;

    vAlumnos = new Alumno[cantReg];

    _alumnoArchivo.leerTodos(vAlumnos, cantReg);

    std::cout << "----- ALUMNOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vAlumnos[i].getEliminado())
        {
            std::cout << "Legajo: " << vAlumnos[i].getLegajo() << " - " << vAlumnos[i].getNombre() << " " << vAlumnos[i].getApellido() << std::endl;
        }
    }

    delete[] vAlumnos;
}

int NotaManager::seleccionarAlumno()
{
    listarAlumnos();

    int legajo;
    bool existe = false;

    do
    {
        legajo = pedirEntero("Legajo alumno: ");
        existe = _alumnoArchivo.existeAlumno(legajo);

        if(!existe)
        {
            std::cout << "ERROR: El alumno no existe..." << std::endl;
        }
    }
    while(!existe);

    return legajo;
}

bool NotaManager::menuModificarNota(Nota &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "----- DATOS ACTUALES DE LA NOTA -----" << std::endl;
        mostrarNota(reg);

        std::cout << "\n----- MODIFICAR NOTA -----" << std::endl;
        std::cout << "1 - Legajo" << std::endl;
        std::cout << "2 - Periodo" << std::endl;
        std::cout << "3 - Nota" << std::endl;
        std::cout << "4 - Descripcion" << std::endl;
        std::cout << "5 - Todos los campos" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "6 - Cancelar y salir " << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;

        opcion = pedirEntero("Opcion: ");

        switch(opcion)
        {
        case 1:
            modificarLegajo(reg);
            break;

        case 2:
            modificarPeriodo(reg);
            break;

        case 3:
            modificarNota(reg);
            break;

        case 4:
            modificarDescripcion(reg);
            break;

        case 5:
            modificarTodos(reg);
            break;

        case 6:
            return false;

        case 0:
            return true;

        default:
            std::cout << "ERROR. Opcion invalida." << std::endl;
        }

        if(opcion >= 1 && opcion <= 5)
        {
            std::cout << "Campo modificado..." << std::endl;
            system("pause");
        }
    }
    while(true);

    return false;
}

void NotaManager::modificarLegajo(Nota &reg)
{
    int nuevoLegajo;

    nuevoLegajo = seleccionarAlumno();

    if(nuevoLegajo == reg.getLegajo())
    {
        std::cout << "Debe seleccionar un alumno distinto al actual..." << std::endl;
        return;
    }

    reg.setLegajo(nuevoLegajo);
}

void NotaManager::modificarPeriodo(Nota &reg)
{
    Periodo nuevoPeriodo;

    nuevoPeriodo = pedirPeriodo();

    if(nuevoPeriodo == reg.getPeriodo())
    {
        std::cout << "Debe seleccionar un periodo distinto al actual..." << std::endl;
        return;
    }

    reg.setPeriodo(nuevoPeriodo);
}

void NotaManager::modificarNota(Nota &reg)
{
    int nuevaNota;

    nuevaNota = pedirNota();

    if(nuevaNota == reg.getNota())
    {
        std::cout << "Debe ingresar una nota distinta a la actual..." << std::endl;
        return;
    }

    reg.setNota(nuevaNota);

}

void NotaManager::modificarDescripcion(Nota &reg)
{
    std::string descripcion;

    descripcion = pedirTexto("Descripcion: ");

    if(descripcion == reg.getDescripcion())
    {
        std::cout << "Debe ingresar una descripcion distinta a la actual..." << std::endl;
        return;
    }

    reg.setDescripcion(descripcion);
}

void NotaManager::modificarTodos(Nota &reg)
{
    modificarLegajo(reg);
    modificarPeriodo(reg);
    modificarDescripcion(reg);
    modificarNota(reg);
}





