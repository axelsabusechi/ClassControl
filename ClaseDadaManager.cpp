#include <iostream>
#include "ClaseDadaManager.h"
#include "utils.h"
#include "rlutil.h"

ClaseDadaManager::ClaseDadaManager()
{
}

void ClaseDadaManager::registrarClaseDada()
{
    if(_claseDadaArchivo.guardar(crearClaseDada()) == ArchivoError::OK)
    {
        std::cout << "Clase dada registrado..." << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_claseDadaArchivo.getLastError());
    }
    system("pause");
    rlutil::cls();
}

void ClaseDadaManager::modificarClaseDada()
{
    rlutil::cls();

    int cantReg = _claseDadaArchivo.getCantRegActivos();

    if(!cantReg)
    {
        if(mostrarErrorArchivo(_claseDadaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No se registran clases dadas para modificar..." << std::endl;
        system("pause");
        return;
    }

    mostrarClasesDadasActivas();

    int id = pedirEntero("Id de la clase dada a modificar: ");
    int index = _claseDadaArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_claseDadaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "La clase dada con " << id << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    ClaseDada reg = _claseDadaArchivo.leer(index);

    if(reg.getIdClase() == -1)
    {
        mostrarErrorArchivo(_claseDadaArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "La clase esta dada de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarClaseDada(reg);

    if(!menuModificarClaseDada(reg))
    {
        std::cout << "Operacion cancelada..." << std::endl;
        system("pause");
        return;
    }

    if(_claseDadaArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "La clase dada se modifico exitosamente!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_claseDadaArchivo.getLastError());
    }

    system("pause");

}

void ClaseDadaManager::eliminarClaseDada()
{
    rlutil::cls();

    int cantReg = _claseDadaArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_claseDadaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay clases dadas registrados para dar de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarClasesDadasActivas();

    int id = pedirEntero("Id de las clases a dar de baja: ");
    int index = _claseDadaArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_claseDadaArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "La clase dada con id " << id << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    ClaseDada reg = _claseDadaArchivo.leer(index);

    if(reg.getIdClase() == -1)
    {
        mostrarErrorArchivo(_claseDadaArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "La clase esta dada de baja." << std::endl;
        system("pause");
        return;
    }

    mostrarClaseDada(reg);
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

        if(_claseDadaArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "La clase con id " << id << " se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_claseDadaArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "Operacion cancelada..." << std::endl;
    }

    system("pause");
}

void ClaseDadaManager::listarClaseDada()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------LISTADO DE CLASES DADAS--------------" << std::endl;
    cantReg = _claseDadaArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay clases dadas registrados..." << std::endl;
    }
    else
    {
        ClaseDada *vClasesDadas = new ClaseDada[cantReg];
        _claseDadaArchivo.leerTodos(vClasesDadas, cantReg);

        for(int i=0; i<cantReg; i++)
        {
            if(!vClasesDadas[i].getEliminado())
            {
                mostrarClaseDada(vClasesDadas[i]);
                std::cout << "--------------------------------------------" << std::endl;
            }
        }
        delete []vClasesDadas;
    }
    system("pause");
    rlutil::cls();
}

ClaseDada ClaseDadaManager::crearClaseDada()
{
    rlutil::cls();

    int idClase, idCurso, idTema;
    Fecha fecha;
    std::string observaciones;
    bool claseDada;

    idClase = _claseDadaArchivo.getNewID();
    idCurso = seleccionarCurso();
    idTema = seleccionarTema();
    observaciones = pedirTexto("Observaciones: ");
    fecha = pedirFecha("Fecha de clase dada: ");
    claseDada = seleccionarEstadoClase();

    return ClaseDada(idClase,
                     idCurso,
                     idTema,
                     fecha,
                     observaciones,
                     claseDada);
}

int ClaseDadaManager::seleccionarCurso()
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

int ClaseDadaManager::seleccionarTema()
{
    listarTemas();

    int idTema;
    bool existe = false;

    do
    {
        idTema = pedirEntero("Id tema: ");
        existe = _temaArchivo.existeTema(idTema);

        if(!existe)
        {
            std::cout << "ERROR: El tema no existe..." << std::endl;
        }
    }
    while(!existe);

    return idTema;
}

bool ClaseDadaManager::seleccionarEstadoClase()
{
    int opcion;

    do
    {
        opcion = pedirEntero("La clase fue dada? (1. Si / 0. No): ");

        if(opcion != 0 && opcion != 1)
        {
            std::cout << "ERROR. Ingrese 1 para Si o 0 para No." << std::endl;
        }

    }
    while(opcion != 0 && opcion != 1);

    return opcion == 1;
}

void ClaseDadaManager::listarCursos()
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

void ClaseDadaManager::listarTemas()
{
    int cantReg;
    cantReg = _temaArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "No hay temas registrados..." << std::endl;
        return;
    }

    Tema *vTemas;

    vTemas = new Tema[cantReg];
    _temaArchivo.leerTodos(vTemas, cantReg);

    std::cout << "----- TEMAS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vTemas[i].getEliminado())
        {
            std::cout << "Id: "<< vTemas[i].getIdTema() << std::endl;
            std::cout << "Nombre: " << vTemas[i].getNombre() << std::endl;
            std::cout << "Orden: " << vTemas[i].getOrden() << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
        }
    }

    delete[] vTemas;
}

void ClaseDadaManager::mostrarClaseDada(const ClaseDada &reg)
{
    int indexCurso = _cursoArchivo.buscarByID(reg.getIdCurso());
    int indexTema = _temaArchivo.buscarById(reg.getIdTema());

    Curso regCurso;
    Tema regTema;

     if(indexCurso != -1)
    {
        regCurso = _cursoArchivo.leer(indexCurso);
    }

     if(indexTema != -1)
    {
        regTema = _temaArchivo.leer(indexTema);
    }

    std::cout << "Id: " << reg.getIdClase() << std::endl;

    if(indexCurso != -1)
    {
        std::cout << "Curso: "
                  << gradoToString(regCurso.getGrado())
                  << " "
                  << divisionToString(regCurso.getDivision())
                  << std::endl;
    }

    if(indexTema != -1)
    {
        std::cout << "Tema: "
                  << regTema.getNombre()
                  << std::endl;
    }

    std::cout << "Fecha: " << reg.getFecha().toString() << std::endl;
    std::cout << "Observaciones: " << reg.getObservaciones() << std::endl;
    std::cout << "Clase dada: " << (reg.getClaseDada() ? "Si" : "No") << std::endl;
}

void ClaseDadaManager::mostrarClasesDadasActivas()
{
    ClaseDada reg;
    int cantReg;

    cantReg = _claseDadaArchivo.getCantReg();

    std::cout << "----- CLASES DADAS ACTIVAS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _claseDadaArchivo.leer(i);

        if(reg.getIdClase() == -1)
        {
            mostrarErrorArchivo(_claseDadaArchivo.getLastError());
            system("pause");
            return;
        }

        if(!reg.getEliminado())
        {
            mostrarClaseDada(reg);
            std::cout << "----------------------------------" << std::endl;
        }
    }
}

bool ClaseDadaManager::menuModificarClaseDada(ClaseDada &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "----- DATOS ACTUALES DE LA CLASE DADA -----" << std::endl;
        mostrarClaseDada(reg);

        std::cout << "\n----- MODIFICAR CLASE DADA -----" << std::endl;
        std::cout << "1 - Fecha" << std::endl;
        std::cout << "2 - Observaciones" << std::endl;
        std::cout << "3 - Clase dada" << std::endl;
        std::cout << "4 - Todos los campos" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "5 - Cancelar y salir " << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;

        opcion = pedirEntero("Opcion: ");

        switch(opcion)
        {
        case 1:
            modificarFecha(reg);
            break;

        case 2:
            modificarObservaciones(reg);
            break;

        case 3:
            modificarClaseDada(reg);
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

        if(opcion >= 1 && opcion <= 5)
        {
            std::cout << "Campo modificado..." << std::endl;
            system("pause");
        }
    }
    while(true);

    return false;
}

void ClaseDadaManager::modificarFecha(ClaseDada &reg)
{
    reg.setFecha(pedirFecha("Nueva fecha de clase dada: "));
}

void ClaseDadaManager::modificarObservaciones(ClaseDada &reg)
{
    reg.setObservaciones(pedirTexto("nuevas observaciones: "));
}

void ClaseDadaManager::modificarClaseDada(ClaseDada &reg)
{
    reg.setClaseDada(seleccionarEstadoClase());
}

void ClaseDadaManager::modificarTodos(ClaseDada &reg)
{
    modificarFecha(reg);
    modificarObservaciones(reg);
    modificarClaseDada(reg);
}

