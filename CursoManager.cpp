#include <iostream>
#include "CursoManager.h"
#include "utils.h"
#include "rlutil.h"

CursoManager::CursoManager()
{
}

void CursoManager::registrarCurso()
{
    if(_cursoArchivo.guardar(crearCurso()) == ArchivoError::OK)
    {
        std::cout << "\nCurso registrado con exito!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_cursoArchivo.getLastError());
    }
    std::cout << "----------------------------------------" << std::endl;
    system("pause");
    rlutil::cls();
}

void CursoManager::modificarCurso()
{
    rlutil::cls();
    std::cout << "===== MODIFICAR CURSO =====" << std::endl;

    int cantReg = _cursoArchivo.getCantRegActivos();

    if(!cantReg)
    {
        if(mostrarErrorArchivo(_cursoArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo hay cursos registrados para modificar..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    std::cout << std::endl;
    mostrarCursosActivos();

    int id = pedirEntero("ID del curso a modificar: ");
    int index = _cursoArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_cursoArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nEl curso con ID " << id
                  << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Curso reg = _cursoArchivo.leer(index);

    if(reg.getIdCurso() == -1)
    {
        mostrarErrorArchivo(_cursoArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "\nEl curso esta dado de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
        system("pause");
        return;
    }

    Grado gradoOriginal = reg.getGrado();
    Division divisionOriginal = reg.getDivision();

    if(!menuModificarCurso(reg))
    {
        std::cout << "Operacion cancelada..." << std::endl;
        std::cout << std::endl;
        system("pause");
        return;
    }

    bool cambioCurso = (reg.getGrado() != gradoOriginal ||
                        reg.getDivision() != divisionOriginal);

    if(cambioCurso && _cursoArchivo.existeCurso(reg.getGrado(), reg.getDivision()))
    {
        std::cout << "\nERROR: Ya existe un curso activo con ese grado y division..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    if(_cursoArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "\nEl curso se modifico exitosamente!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_cursoArchivo.getLastError());
    }

    std::cout << "----------------------------------------" << std::endl;
    system("pause");
}

void CursoManager::eliminarCurso()
{
    rlutil::cls();
    std::cout << "===== DAR DE BAJA CURSO =====" << std::endl;

    int cantReg = _cursoArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_cursoArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo hay cursos registrados para dar de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
        system("pause");
        return;
    }

    std::cout << std::endl;
    mostrarCursosActivos();

    int id = pedirEntero("\nID del curso a dar de baja: ");
    int index = _cursoArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_cursoArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nEl curso con ID " << id
                  << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Curso reg = _cursoArchivo.leer(index);

    if(reg.getIdCurso() == -1)
    {
        mostrarErrorArchivo(_cursoArchivo.getLastError());
        std::cout << std::endl;
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "\nEl curso ya esta dado de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

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

        if(_cursoArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "\nEl curso " << gradoToString(reg.getGrado())
                      << " " << divisionToString(reg.getDivision())
                      << " se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_cursoArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    system("pause");

}

void CursoManager::listarCursos()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------LISTADO DE CURSOS--------------" << std::endl;
    cantReg = _cursoArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay cursos registrados..." << std::endl;
        std::cout << std::endl;
    }
    else
    {
        Curso *vCursos = new Curso[cantReg];
        _cursoArchivo.leerTodos(vCursos,cantReg);

        for(int i=0; i<cantReg; i++)
        {
            if(!vCursos[i].getEliminado())
            {
                std::cout << "Id: "<< vCursos[i].getIdCurso() << std::endl;
                std::cout << "Grado: " << gradoToString(vCursos[i].getGrado()) << std::endl;
                std::cout << "Division: " << divisionToString(vCursos[i].getDivision()) << std::endl;
                std::cout << "--------------------------------------------" << std::endl;
            }
        }
        delete []vCursos;
    }
    system("pause");
    rlutil::cls();
}

Curso CursoManager::crearCurso()
{
    int idCurso;
    Grado grado;
    Division division;

    idCurso = _cursoArchivo.getNewID();

    rlutil::cls();

    std::cout << "===== REGISTRAR CURSO =====" << std::endl;
    std::cout << "ID " << idCurso << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    cargarCursoUnico(grado, division);

    return Curso(idCurso, grado, division);
}

void CursoManager::cargarCursoUnico(Grado &grado, Division &division)
{
    bool existe;

    do
    {
        std::cout << std::endl;
        grado = pedirGrado();
        division = pedirDivision();

        existe = _cursoArchivo.existeCurso(grado, division);

        if(existe)
        {
            std::cout << "\nERROR: El curso ya existe..." << std::endl;
        }

    }
    while(existe);
}

bool CursoManager::menuModificarCurso(Curso &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "===== MODIFICAR CURSO =====" << std::endl;
        std::cout << "\n----- DATOS ACTUALES -----" << std::endl;
        mostrarCurso(reg);
        std::cout << "----------------------------------------" << std::endl;

        std::cout << "\n----- CAMPOS A MODIFICAR -----" << std::endl;
        std::cout << "1 - Grado" << std::endl;
        std::cout << "2 - Division" << std::endl;
        std::cout << "3 - Todos los campos" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "4 - Cancelar y salir" << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        opcion = pedirEntero("Opcion: ");

        switch(opcion)
        {
        case 1:
            modificarGrado(reg);
            break;

        case 2:
            modificarDivision(reg);
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

void CursoManager::modificarGrado(Curso &reg)
{
    std::cout << std::endl;
    reg.setGrado(pedirGrado());
}

void CursoManager::modificarDivision(Curso &reg)
{
    std::cout << std::endl;
    reg.setDivision(pedirDivision());
}

void CursoManager::modificarTodos(Curso &reg)
{
    modificarGrado(reg);
    modificarDivision(reg);
}

void CursoManager::mostrarCurso(const Curso &reg)const
{
    std::cout << "ID: " << reg.getIdCurso() << std::endl;
    std::cout << "Grado: " << gradoToString(reg.getGrado()) << std::endl;
    std::cout << "Division: " << divisionToString(reg.getDivision()) << std::endl;
}

void CursoManager::mostrarCursosActivos()
{
    Curso reg;

    int cantReg = _cursoArchivo.getCantReg();

    std::cout << "----- CURSOS ACTIVOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _cursoArchivo.leer(i);

        if(reg.getIdCurso() == -1)
        {
            mostrarErrorArchivo(_cursoArchivo.getLastError());
            system("pause");
            return;
        }

        if(!reg.getEliminado())
        {
            mostrarCurso(reg);
            std::cout << "----------------------------------------" << std::endl;
        }
    }
}










