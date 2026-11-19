#include <iostream>
#include "ClaseDadaManager.h"
#include "utils.h"
#include "rlutil.h"

ClaseDadaManager::ClaseDadaManager()
{
}

void ClaseDadaManager::registrarClaseDada()
{
    rlutil::cls();
    std::cout << "===== REGISTRAR CLASE DADA =====" << std::endl;

    if(_cursoArchivo.getCantRegActivos() == 0)
    {
        if(mostrarErrorArchivo(_cursoArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "\nNo hay cursos registrados..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        rlutil::cls();
        return;
    }

    if(_temaArchivo.getCantRegActivos() == 0)
    {
        if(mostrarErrorArchivo(_temaArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "\nNo hay temas registrados..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        rlutil::cls();
        return;
    }

    if(_claseDadaArchivo.guardar(crearClaseDada()) == ArchivoError::OK)
    {
        std::cout << "\nClase dada registrada con exito!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_claseDadaArchivo.getLastError());
    }
    std::cout << "----------------------------------------" << std::endl;
    system("pause");
    rlutil::cls();
}

void ClaseDadaManager::modificarClaseDada()
{

    rlutil::cls();
    std::cout << "===== MODIFICAR CLASE DADA =====" << std::endl;

    int cantReg = _claseDadaArchivo.getCantRegActivos();

    if(!cantReg)
    {
        if(mostrarErrorArchivo(_claseDadaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo se registran clases dadas para modificar..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    std::cout << std::endl;
    mostrarClasesDadasActivas();

    int id = pedirEntero("\nID de la clase dada a modificar: ");
    int index = _claseDadaArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_claseDadaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nLa clase dada con ID " << id << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
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
        std::cout << "\nLa clase dada esta dada de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    if(!menuModificarClaseDada(reg))
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    if(_claseDadaArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "\nLa clase dada se modifico exitosamente!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_claseDadaArchivo.getLastError());
    }

    std::cout << "----------------------------------------" << std::endl;
    system("pause");

}

void ClaseDadaManager::eliminarClaseDada()
{
    rlutil::cls();
    std::cout << "===== DAR DE BAJA CLASE DADA =====" << std::endl;

    int cantReg = _claseDadaArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_claseDadaArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo hay clases dadas registradas para dar de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    std::cout << std::endl;
    mostrarClasesDadasActivas();

    int id = pedirEntero("\nID de las clases a dar de baja: ");
    int index = _claseDadaArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_claseDadaArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "\nLa clase dada con ID " << id
                  << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
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
        std::cout << "\nLa clase dada ya esta dada de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    rlutil::cls();
    std::cout << "===== DAR DE BAJA CLASE DADA =====" << std::endl;
    std::cout << "\n----- CLASE DADA SELECCIONADA -----" << std::endl;
    mostrarClaseDada(reg);
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

        if(_claseDadaArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "\nLa clase con id " << id << " se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_claseDadaArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
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
    int idClase, idCurso, idTema;
    Fecha fecha;
    std::string observaciones;
    bool claseDada;

    idClase = _claseDadaArchivo.getNewID();

    rlutil::cls();
    std::cout << "===== REGISTRAR CLASE DADA =====" << std::endl;
    std::cout << "ID Clase: " << idClase << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    idCurso = seleccionarCurso();
    idTema = seleccionarTema();
    std::cout << std::endl;
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
        idCurso = pedirEntero("\nID curso: ");
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
        idTema = pedirEntero("\nID tema: ");
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

bool ClaseDadaManager::menuModificarClaseDada(ClaseDada &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "===== MODIFICAR CLASE DADA =====" << std::endl;
        std::cout << "\n----- DATOS ACTUALES -----" << std::endl;
        mostrarClaseDada(reg);
        std::cout << "----------------------------------------" << std::endl;

        std::cout << "\n----- CAMPOS A MODIFICAR -----" << std::endl;
        std::cout << "1 - Fecha" << std::endl;
        std::cout << "2 - Observaciones" << std::endl;
        std::cout << "3 - Clase dada" << std::endl;
        std::cout << "4 - Todos los campos" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "5 - Cancelar y salir" << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

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
            system("pause");
        }

        if(opcion >= 1 && opcion <= 5)
        {
            std::cout << "\nCampo modificado..." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            system("pause");
        }
    }
    while(true);

    return false;
}

void ClaseDadaManager::modificarFecha(ClaseDada &reg)
{
    std::cout << std::endl;
    reg.setFecha(pedirFecha("Nueva fecha de clase dada: "));
}

void ClaseDadaManager::modificarObservaciones(ClaseDada &reg)
{
    std::cout << std::endl;
    reg.setObservaciones(pedirTexto("nuevas observaciones: "));
}

void ClaseDadaManager::modificarClaseDada(ClaseDada &reg)
{
    std::cout << std::endl;
    reg.setClaseDada(seleccionarEstadoClase());
}

void ClaseDadaManager::modificarTodos(ClaseDada &reg)
{
    modificarFecha(reg);
    modificarObservaciones(reg);
    modificarClaseDada(reg);
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

    std::cout << "ID: " << reg.getIdClase() << std::endl;

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
            std::cout << "----------------------------------------" << std::endl;
        }
    }
}

void ClaseDadaManager::listarCursos()
{
    int cantReg;
    cantReg = _cursoArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "\nNo hay cursos registrados..." << std::endl;
        return;
    }

    Curso *vCursos;

    vCursos = new Curso[cantReg];
    _cursoArchivo.leerTodos(vCursos, cantReg);

    std::cout << "\n----- CURSOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vCursos[i].getEliminado())
        {
            std::cout << "Id: "<< vCursos[i].getIdCurso() << std::endl;
            std::cout << "Grado: " << gradoToString(vCursos[i].getGrado()) << std::endl;
            std::cout << "Division: " << divisionToString(vCursos[i].getDivision()) << std::endl;
            std::cout << "----------------------------------------" << std::endl;
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
        std::cout << "\nNo hay temas registrados..." << std::endl;
        return;
    }

    Tema *vTemas;

    vTemas = new Tema[cantReg];
    _temaArchivo.leerTodos(vTemas, cantReg);

    std::cout << "\n----- TEMAS -----" << std::endl;

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


