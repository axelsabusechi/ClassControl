#include <iostream>
#include "InscripcionManager.h"
#include "utils.h"
#include "rlutil.h"

InscripcionManager::InscripcionManager()
{
}

void InscripcionManager::registrarInscripcion()
{
    rlutil::cls();

    if(_alumnoArchivo.getCantRegActivos() == 0)
    {
        if(mostrarErrorArchivo(_inscripcionArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "No hay alumnos registrados para inscribir..." << std::endl;
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
        std::cout << "No hay cursos registrados al cual inscribir..." << std::endl;
        system("pause");
        rlutil::cls();
        return;
    }

    if(_inscripcionArchivo.guardar(crearInscripcion()) == ArchivoError::OK)
    {
        std::cout << "Inscripcion registrada..." << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_inscripcionArchivo.getLastError());
    }
    system("pause");
    rlutil::cls();
}

void InscripcionManager::eliminarInscripcion()
{
    rlutil::cls();
    int index, id, cantReg;
    Inscripcion reg;

    cantReg = _inscripcionArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_inscripcionArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "No hay inscripciones registradas para dar de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarInscripcionesActivas();

    id = pedirEntero("Id de la inscripcion a dar de baja: ");

    index = _inscripcionArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_inscripcionArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "La inscripcion con Id " << id << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    reg = _inscripcionArchivo.leer(index);

    if(reg.getIdInscripcion() == -1)
    {
        mostrarErrorArchivo(_inscripcionArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "La inscripcion esta dada de baja..." << std::endl;
        system("pause");
        return;
    }

    mostrarInscripcion(reg);
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

        if(_inscripcionArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "La inscripcion se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_inscripcionArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "Operacion cancelada..." << std::endl;
    }

    system("pause");
}

void InscripcionManager::listarInscripcion()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------LISTADO DE INSCRIPCIONES--------------" << std::endl;
    cantReg = _inscripcionArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay inscripciones registradas..." << std::endl;
    }
    else
    {
        Inscripcion *vInscripcion;

        vInscripcion = new Inscripcion[cantReg];
        _inscripcionArchivo.leerTodos(vInscripcion,cantReg);

        for(int i=0; i<cantReg; i++)
        {
            if(!vInscripcion[i].getEliminado())
            {
                mostrarInscripcion(vInscripcion[i]);
                std::cout << "--------------------------------------------" << std::endl;
            }
        }
        delete []vInscripcion;
    }
    system("pause");
    rlutil::cls();
}

Inscripcion InscripcionManager::crearInscripcion()
{
    rlutil::cls();

    int idInscripcion, legajo, idCurso;
    Fecha fechaAlta, fechaBaja;

    idInscripcion = _inscripcionArchivo.getNewID();
    pedirInscripcionUnica(legajo, idCurso);
    fechaAlta.cargarFechaActual();
    fechaBaja = Fecha();

    return Inscripcion(idInscripcion,
                       legajo,
                       idCurso,
                       fechaAlta,
                       fechaBaja,
                       true);
}

void InscripcionManager::mostrarInscripcion(const Inscripcion &reg)
{
    int indexAlumno;
    int indexCurso;
    Alumno alumno;
    Curso curso;

    indexAlumno = _alumnoArchivo.buscarByLegajo(reg.getLegajo());
    indexCurso = _cursoArchivo.buscarByID(reg.getIdCurso());

    alumno = _alumnoArchivo.leer(indexAlumno);
    curso = _cursoArchivo.leer(indexCurso);

    std::cout << "Id Inscripcion: " << reg.getIdInscripcion() << std::endl;
    std::cout << "Alumno: " << alumno.getNombre() << " " << alumno.getApellido() <<std::endl;
    std::cout << "Legajo: " << reg.getLegajo() << std::endl;
    std::cout << "Curso: " << gradoToString(curso.getGrado()) << " " << divisionToString(curso.getDivision()) << std::endl;
    std::cout << "Id Curso: " << reg.getIdCurso() << std::endl;
    std::cout << "Fecha de alta: " << reg.getFechaAlta().toString() << std::endl;
    std::cout << "Fecha de baja: " << reg.getFechaBaja().toString() << std::endl;
}

void InscripcionManager::mostrarInscripcionesActivas()
{
    Inscripcion reg;
    int cantReg;

    cantReg = _inscripcionArchivo.getCantReg();

    std::cout << "----- INSCRIPCIONES ACTIVAS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _inscripcionArchivo.leer(i);

        if(reg.getIdInscripcion() == -1)
        {
            mostrarErrorArchivo(_inscripcionArchivo.getLastError());
            system("pause");
            return;
        }

        if(!reg.getEliminado())
        {
            mostrarInscripcion(reg);
            std::cout << "----------------------------------" << std::endl;
        }
    }
}

void InscripcionManager::pedirInscripcionUnica(int &legajo, int &idCurso)
{
    bool existe = false;

    do
    {
        legajo = seleccionarAlumno();
        idCurso = seleccionarCurso();

        existe = _inscripcionArchivo.existeInscripcion(legajo, idCurso);

        if(existe)
        {
            std::cout << "ERROR: El alumno ya esta inscripto en ese curso..." << std::endl;
        }
    }
    while(existe);
}

void InscripcionManager::listarAlumnos()
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

void InscripcionManager::listarCursos()
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

int InscripcionManager::seleccionarAlumno()
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

int InscripcionManager::seleccionarCurso()
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
