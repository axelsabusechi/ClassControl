#include <iostream>
#include "AsignacionDocenteManager.h"
#include "utils.h"
#include "rlutil.h"

AsignacionDocenteManager::AsignacionDocenteManager()
{
}

void AsignacionDocenteManager::registrarAsignacionDocente()
{
    rlutil::cls();

    if(_docenteArchivo.getCantRegActivos() == 0)
    {
        if(mostrarErrorArchivo(_docenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "No hay docentes registrados para asignar..." << std::endl;
        system("pause");
        rlutil::cls();
        return;
    }

    if(_cursoArchivo.getCantRegActivos() == 0)
    {
        if(mostrarErrorArchivo(_cursoArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "No hay cursos registrados para asignar..." << std::endl;
        system("pause");
        rlutil::cls();
        return;
    }

    if(_asignacionDocenteArchivo.guardar(crearAsignacionDocente()) == ArchivoError::OK)
    {
        std::cout << "Asignacion del docente registrada..." << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError());
    }
    system("pause");
    rlutil::cls();
}

void AsignacionDocenteManager::modificarAsignacionDocente()
{
    rlutil::cls();

    int cantRegAsignacion = _asignacionDocenteArchivo.getCantRegActivos();

    if(cantRegAsignacion == 0)
    {
        if(mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay asignaciones docentes para modificar..." << std::endl;
        system("pause");
        return;
    }

    mostrarAsignacionesActivas();

    int idAsignacion = pedirEntero("ID de la asignacion del docente a modificar: ");
    int indexAsignacion = _asignacionDocenteArchivo.buscarByID(idAsignacion);

    if(indexAsignacion == -1)
    {
        if(mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "La asignacion del docente no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    AsignacionDocente regAsignacion = _asignacionDocenteArchivo.leer(indexAsignacion);

    if(regAsignacion.getIdAsignacion() == -1)
    {
        mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError());
        system("pause");
        return;
    }

    if(regAsignacion.getEliminado() || !regAsignacion.getActivo())
    {
        std::cout << "La asignacion no se encuentra activa..." << std::endl;
        system("pause");
        return;
    }

    int indexDocente = _docenteArchivo.buscarByID(regAsignacion.getIdDocente());

    if(indexDocente == -1)
    {
        if(mostrarErrorArchivo(_docenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "El Docente con Id " << regAsignacion.getIdDocente() << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    Docente regDocente = _docenteArchivo.leer(indexDocente);

    if(regDocente.getIdDocente() == -1)
    {
        mostrarErrorArchivo(_docenteArchivo.getLastError());
        system("pause");
        return;
    }

    if(regDocente.getEliminado())
    {
        std::cout << "El docente esta dado de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarAsignacionDocente(regAsignacion);

    if(!menuModificarAsignacion(regAsignacion))
    {
        std::cout << "Operacion cancelada..." << std::endl;
        system("pause");
        return;
    }

    rlutil::cls();

    int idNuevoCurso = seleccionarCurso();

    if(idNuevoCurso == regAsignacion.getIdCurso())
    {
        std::cout << "Debe seleccionar un curso distinto al actualmente asignado..." << std::endl;
        system("pause");
        return;
    }

    if(_asignacionDocenteArchivo.existeAsignacion(regAsignacion.getIdDocente(),idNuevoCurso))
    {
        std::cout << "El docente ya tiene una asignacion activa para el curso seleccionado..." << std::endl;
        system("pause");
        return;
    }

    int nuevoIdAsignacion = _asignacionDocenteArchivo.getNewID();
    Fecha fechaAlta;

    fechaAlta.cargarFechaActual();

    AsignacionDocente nuevaAsignacion(nuevoIdAsignacion,
                                      regAsignacion.getIdDocente(),
                                      idNuevoCurso,
                                      fechaAlta,
                                      Fecha(),
                                      true);

    if(_asignacionDocenteArchivo.guardar(nuevaAsignacion) != ArchivoError::OK)
    {
        mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError());
        system("pause");
        return;
    }

    Fecha fechaBaja;
    fechaBaja.cargarFechaActual();
    regAsignacion.setFechaBaja(fechaBaja);
    regAsignacion.setActivo(false);
    regAsignacion.setEliminado(true);

    if(_asignacionDocenteArchivo.guardar(indexAsignacion, regAsignacion) != ArchivoError::OK)
    {
        mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError());
        system("pause");
        return;
    }

    std::cout << "La asignacion docente al nuevo curso se actualizo con exito!" << std::endl;
    system("pause");
}


void AsignacionDocenteManager::eliminarAsignacionDocente()
{
    rlutil::cls();

    int cantReg = _asignacionDocenteArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay asignaciones docentes registradas para dar de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarAsignacionesActivas();

    int id = pedirEntero("Id de la asignacion docente a dar de baja: ");
    int index = _asignacionDocenteArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "La asignacion docente con IdD " << id << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    AsignacionDocente reg = _asignacionDocenteArchivo.leer(index);

    if(reg.getIdAsignacion() == -1)
    {
        mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "La asignacion docente esta dada de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarAsignacionDocente(reg);
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
        Fecha fechaBaja;

        fechaBaja.cargarFechaActual();
        reg.setFechaBaja(fechaBaja);
        reg.setActivo(false);
        reg.setEliminado(true);

        if(_asignacionDocenteArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "La asignacion docente  se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "Operacion cancelada..." << std::endl;
    }

    system("pause");
}

void AsignacionDocenteManager::listarAsignacionesDocentes()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------LISTADO DE ASIGANCIONES DOCENTES--------------" << std::endl;
    cantReg = _asignacionDocenteArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay asignaciones docentes registrados..." << std::endl;
    }
    else
    {
        AsignacionDocente *vAsignacionDocente;

        vAsignacionDocente = new AsignacionDocente[cantReg];
        _asignacionDocenteArchivo.leerTodos(vAsignacionDocente,cantReg);

        for(int i=0; i<cantReg; i++)
        {
            if(!vAsignacionDocente[i].getEliminado())
            {
                mostrarAsignacionDocente(vAsignacionDocente[i]);
                std::cout << "--------------------------------------------" << std::endl;
            }
        }
        delete []vAsignacionDocente;
    }
    system("pause");
    rlutil::cls();
}

AsignacionDocente AsignacionDocenteManager::crearAsignacionDocente()
{
    rlutil::cls();

    int idAsignacion, idDocente, idCurso;
    Fecha fechaAlta, fechaBaja;

    idAsignacion = _asignacionDocenteArchivo.getNewID();
    cargarAsignacionUnica(idDocente, idCurso);
    fechaAlta.cargarFechaActual();
    fechaBaja = Fecha();

    return AsignacionDocente(idAsignacion,
                             idDocente,
                             idCurso,
                             fechaAlta,
                             fechaBaja,
                             true);
}

void AsignacionDocenteManager::mostrarAsignacionDocente(const AsignacionDocente &reg)
{
    int indexDocente;
    int indexCurso;
    Docente docente;
    Curso curso;

    indexDocente = _docenteArchivo.buscarByID(reg.getIdDocente());
    indexCurso = _cursoArchivo.buscarByID(reg.getIdCurso());

    docente = _docenteArchivo.leer(indexDocente);
    curso = _cursoArchivo.leer(indexCurso);

    std::cout << "Id Asignacion: " << reg.getIdAsignacion() << std::endl;
    std::cout << "Docente: " << docente.getNombre() << " " << docente.getApellido() <<std::endl;
    //std::cout << "Id Docente: " << reg.getIdDocente() << std::endl;
    std::cout << "Curso: " << gradoToString(curso.getGrado()) << " " << divisionToString(curso.getDivision()) << std::endl;
    //std::cout << "Id Curso: " << reg.getIdCurso() << std::endl;
    std::cout << "Fecha de alta: " << reg.getFechaAlta().toString() << std::endl;
    std::cout << "Fecha de baja: " << reg.getFechaBaja().toString() << std::endl;
}

void AsignacionDocenteManager::mostrarAsignacionesActivas()
{
    AsignacionDocente reg;
    int cantReg;

    cantReg = _asignacionDocenteArchivo.getCantReg();

    std::cout << "----- ASIGNACIONES DOCENTES ACTIVAS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _asignacionDocenteArchivo.leer(i);

        if(reg.getIdAsignacion() == -1)
        {
            mostrarErrorArchivo(_asignacionDocenteArchivo.getLastError());
            system("pause");
            return;
        }

        if(!reg.getEliminado() && reg.getActivo())
        {
            mostrarAsignacionDocente(reg);
            std::cout << "----------------------------------" << std::endl;
        }
    }
}

bool AsignacionDocenteManager::menuModificarAsignacion(AsignacionDocente &reg)
{
    int opcion;

    do
    {
        rlutil::cls();

        std::cout << "----- DATOS ACTUALES DE LA ASIGNACION DOCENTE -----" << std::endl;

        mostrarAsignacionDocente(reg);
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1 - Modificar el curso asignado al docente" << std::endl;
        std::cout << "0 - Cancelar y salir" << std::endl;


        opcion = pedirEntero("Opcion: ");

        switch(opcion)
        {
        case 1:
            return true;

        case 0:
            return false;

        default:
            std::cout << "ERROR. Opcion invalida." << std::endl;
            system("pause");
        }

    }
    while(true);

    return false;
}

void AsignacionDocenteManager::cargarAsignacionUnica(int &idDocente, int &idCurso)
{
    bool existe = false;

    do
    {
        idDocente = seleccionarDocente();
        idCurso = seleccionarCurso();

        existe = _asignacionDocenteArchivo.existeAsignacion(idDocente,idCurso);

        if(existe)
        {
            std::cout << "ERROR: El docente ya esta asignado a ese curso..." << std::endl;
        }
    }
    while(existe);
}

void AsignacionDocenteManager::listarDocentes()
{
    int cantReg;

    cantReg = _docenteArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "No hay docentes registrados..." << std::endl;
        system("pause");
        return;
    }

    Docente *vDocentes;

    vDocentes = new Docente[cantReg];

    _docenteArchivo.leerTodos(vDocentes, cantReg);

    std::cout << "------------- DOCENTES -------------" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vDocentes[i].getEliminado())
        {
            std::cout << "Id: " << vDocentes[i].getIdDocente() << std::endl;
            std::cout << "Nombre: "<< vDocentes[i].getNombre() << std::endl;
            std::cout << "Apellido: " << vDocentes[i].getApellido() << std::endl;
            std::cout << "DNI: " << vDocentes[i].getDni() << std::endl;
            std::cout << "---------------------------------------" << std::endl;
        }
    }

    delete[] vDocentes;
}

void AsignacionDocenteManager::listarCursos()
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

    std::cout << std::endl;
    std::cout << "------------- CURSOS -------------" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vCursos[i].getEliminado())
        {
            std::cout << "Id: "<< vCursos[i].getIdCurso() << std::endl;
            std::cout << "Grado: " << gradoToString(vCursos[i].getGrado()) << std::endl;
            std::cout << "Division: " << divisionToString(vCursos[i].getDivision()) << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
        }
    }

    delete[] vCursos;
}

int AsignacionDocenteManager::seleccionarDocente()
{
    listarDocentes();

    int idDocente;
    bool existe = false;

    do
    {
        std::cout << std::endl;
        idDocente = pedirEntero("Id docente: ");
        existe = _docenteArchivo.existeDocente(idDocente);

        if(!existe)
        {
            std::cout << "ERROR: El docente no existe..." << std::endl;
        }
    }
    while(!existe);

    return idDocente;
}

int AsignacionDocenteManager::seleccionarCurso()
{
    listarCursos();

    int idCurso;
    bool existe = false;

    do
    {
        std::cout << std::endl;
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









