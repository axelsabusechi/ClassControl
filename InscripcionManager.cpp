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
    std::cout << "===== REGISTRAR INSCRIPCION =====" << std::endl;

    if(_alumnoArchivo.getCantRegActivos() == 0)
    {
        if(mostrarErrorArchivo(_inscripcionArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo hay alumnos registrados para inscribir..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
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
        std::cout << "\nNo hay cursos registrados al cual inscribir alumnos..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        rlutil::cls();
        return;
    }

    if(_inscripcionArchivo.guardar(crearInscripcion()) == ArchivoError::OK)
    {
        std::cout << "\nInscripcion del alumno registrada con exito!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_inscripcionArchivo.getLastError());
    }
    std::cout << "----------------------------------------" << std::endl;
    system("pause");
    rlutil::cls();
}

void InscripcionManager::modificarInscripcion()
{
    rlutil::cls();
    std::cout << "===== MODIFICAR INSCRIPCION =====" << std::endl;

    int cantRegInscripcion = _inscripcionArchivo.getCantRegActivos();

    if(cantRegInscripcion == 0)
    {
        if(mostrarErrorArchivo(_inscripcionArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "\nNo hay inscripciones de alumnos para modificar..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    std::cout << std::endl;
    mostrarInscripcionesActivas();

    int idInscripcion = pedirEntero("\nId de la inscripcion del alumno a modificar: ");
    int indexInscripcion = _inscripcionArchivo.buscarByID(idInscripcion);

    if(indexInscripcion == -1)
    {
        if(mostrarErrorArchivo(_inscripcionArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nLa inscripcion no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Inscripcion regInscripcion = _inscripcionArchivo.leer(indexInscripcion);

    if(regInscripcion.getIdInscripcion() == -1)
    {
        mostrarErrorArchivo(_inscripcionArchivo.getLastError());
        system("pause");
        return;
    }

    if(regInscripcion.getEliminado() || !regInscripcion.getActivo())
    {
        std::cout << "\nLa inscripcion no se encuentra activa..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    int indexAlumno = _alumnoArchivo.buscarByLegajo(regInscripcion.getLegajo());

    if(indexAlumno == -1)
    {
        if(mostrarErrorArchivo(_alumnoArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nEl alumno con legajo " << regInscripcion.getLegajo()
                  << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);

    if(regAlumno.getLegajo() == -1)
    {
        mostrarErrorArchivo(_alumnoArchivo.getLastError());
        system("pause");
        return;
    }

    if(regAlumno.getEliminado())
    {
        std::cout << "\nEl alumno esta dado de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    if(!menuModificarInscripcion(regInscripcion))
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    rlutil::cls();
    std::cout << "===== MODIFICAR INSCRIPCION =====" << std::endl;

    int idNuevoCurso = seleccionarCurso();

    if(idNuevoCurso == regInscripcion.getIdCurso())
    {
        std::cout << "\nDebe seleccionar un curso distinto al actualmente asignado..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    int nuevoIdInscripcion = _inscripcionArchivo.getNewID();
    Fecha fechaAlta;
    fechaAlta.cargarFechaActual();

    Inscripcion nuevaInscripcion(nuevoIdInscripcion,
                                 regInscripcion.getLegajo(),
                                 idNuevoCurso,
                                 fechaAlta,
                                 Fecha(),
                                 true);

    if(_inscripcionArchivo.guardar(nuevaInscripcion) != ArchivoError::OK)
    {
        mostrarErrorArchivo(_inscripcionArchivo.getLastError());
        system("pause");
        return;
    }

    Fecha fechaBaja;
    fechaBaja.cargarFechaActual();
    regInscripcion.setFechaBaja(fechaBaja);
    regInscripcion.setActivo(false);
    regInscripcion.setEliminado(true);

    if(_inscripcionArchivo.guardar(indexInscripcion, regInscripcion) != ArchivoError::OK)
    {
        mostrarErrorArchivo(_inscripcionArchivo.getLastError());
        system("pause");
        return;
    }

    std::cout << "\nLa inscripcion del alumno al nuevo curso se actualizo con exito!" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    system("pause");
}


void InscripcionManager::eliminarInscripcion()
{
    rlutil::cls();
    std::cout << "===== DAR DE BAJA INSCRIPCION =====" << std::endl;

    int cantReg = _inscripcionArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_inscripcionArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "\nNo hay inscripciones registradas para dar de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    std::cout << std::endl;
    mostrarInscripcionesActivas();

    int id = pedirEntero("\nID de la inscripcion a dar de baja: ");
    int index = _inscripcionArchivo.buscarByID(id);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_inscripcionArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nLa inscripcion con ID " << id
                  << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Inscripcion reg = _inscripcionArchivo.leer(index);

    if(reg.getIdInscripcion() == -1)
    {
        mostrarErrorArchivo(_inscripcionArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "\nLa inscripcion ya esta dada de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    rlutil::cls();
    std::cout << "===== DAR DE BAJA INSCRIPCION =====" << std::endl;
    std::cout << "\n----- INSCRIPCION SELECCIONADA -----" << std::endl;
    mostrarInscripcion(reg);

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
        Fecha fechaBaja;

        fechaBaja.cargarFechaActual();
        reg.setFechaBaja(fechaBaja);
        reg.setActivo(false);
        reg.setEliminado(true);

        if(_inscripcionArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "\nLa inscripcion se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_inscripcionArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
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
            }
        }
        delete []vInscripcion;
    }
    system("pause");
    rlutil::cls();
}

Inscripcion InscripcionManager::crearInscripcion()
{
    int idInscripcion, legajo, idCurso;
    Fecha fechaAlta, fechaBaja;

    idInscripcion = _inscripcionArchivo.getNewID();

    rlutil::cls();
    std::cout << "===== REGISTRAR INSCRIPCION =====" << std::endl;
    std::cout << "ID Inscripcion: " << idInscripcion << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    cargarInscripcionUnica(legajo, idCurso);
    fechaAlta.cargarFechaActual();
    fechaBaja = Fecha();

    return Inscripcion(idInscripcion,
                       legajo,
                       idCurso,
                       fechaAlta,
                       fechaBaja,
                       true);
}

void InscripcionManager::cargarInscripcionUnica(int &legajo, int &idCurso)
{
    bool existe = false;

    do
    {
        legajo = seleccionarAlumno();
        idCurso = seleccionarCurso();

        existe = _inscripcionArchivo.tieneInscripcionActiva(legajo);

        if(existe)
        {
            std::cout << "\nERROR: El alumno ya se encuentra inscripto en un curso..." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            system("pause");
            rlutil::cls();
            std::cout << "===== REGISTRAR INSCRIPCION =====" << std::endl;
        }
    }
    while(existe);
}

int InscripcionManager::seleccionarAlumno()
{
    listarAlumnos();

    int legajo;
    bool existe = false;

    do
    {
        legajo = pedirEntero("\nLegajo alumno: ");
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

bool InscripcionManager::menuModificarInscripcion(Inscripcion &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "===== MODIFICAR INSCRIPCION =====" << std::endl;
        std::cout << "\n----- DATOS ACTUALES -----" << std::endl;
        mostrarInscripcion(reg);

        std::cout << "\n----- OPCIONES -----" << std::endl;
        std::cout << "1 - Modificar el curso del alumno inscripto" << std::endl;
        std::cout << "0 - Cancelar y salir" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

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

void InscripcionManager::mostrarInscripcion(const Inscripcion &reg)
{
    int indexAlumno = _alumnoArchivo.buscarByLegajo(reg.getLegajo());
    int indexCurso = _cursoArchivo.buscarByID(reg.getIdCurso());

    Alumno alumno = _alumnoArchivo.leer(indexAlumno);
    Curso curso = _cursoArchivo.leer(indexCurso);

    std::cout << "Id Inscripcion: " << reg.getIdInscripcion() << std::endl;
    std::cout << "Alumno: " << alumno.getNombre() << " " << alumno.getApellido() <<std::endl;
    std::cout << "Curso: " << gradoToString(curso.getGrado()) << " " << divisionToString(curso.getDivision()) << std::endl;
    std::cout << "Fecha de alta: " << reg.getFechaAlta().toString() << std::endl;
    std::cout << "Fecha de baja: " << reg.getFechaBaja().toString() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
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
        }
    }
}

void InscripcionManager::listarAlumnos()
{
    int cantReg;

    cantReg = _alumnoArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "\nNo hay alumnos registrados..." << std::endl;
        system("pause");
        return;
    }

    Alumno *vAlumnos = new Alumno[cantReg];
    _alumnoArchivo.leerTodos(vAlumnos, cantReg);

    std::cout << "\n----- ALUMNOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vAlumnos[i].getEliminado())
        {
            std::cout << "Legajo: " << vAlumnos[i].getLegajo()
                      << " - " << vAlumnos[i].getNombre()
                      << " " << vAlumnos[i].getApellido() << std::endl;
        }
    }

    std::cout << "----------------------------------------" << std::endl;

    delete[] vAlumnos;
}

void InscripcionManager::listarCursos()
{
    int cantReg;

    cantReg = _cursoArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "\nNo hay cursos registrados..." << std::endl;
        return;
    }

    Curso *vCursos = new Curso[cantReg];
    _cursoArchivo.leerTodos(vCursos, cantReg);

    std::cout << "\n----- CURSOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vCursos[i].getEliminado())
        {
            std::cout << "ID: "<< vCursos[i].getIdCurso() << std::endl;
            std::cout << "Grado: " << gradoToString(vCursos[i].getGrado()) << std::endl;
            std::cout << "Division: " << divisionToString(vCursos[i].getDivision()) << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
        }
    }

    delete[] vCursos;
}


