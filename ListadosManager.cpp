#include <iostream>
#include "ListadosManager.h"
#include "rlutil.h"
#include "utils.h"


void ListadosManager::listarAlumnosPorCurso()
{
    rlutil::cls();

    int idCurso = seleccionarCurso();
    int indexCurso = _cursoArchivo.buscarByID(idCurso);
    Curso regCurso = _cursoArchivo.leer(indexCurso);
    mostrarEncabezadoCurso(regCurso, "ALUMNOS DEL CURSO");

    if(!mostrarAlumnosCurso(idCurso))
    {
        std::cout << "No hay alumnos inscriptos en el curso..." << std::endl;
    }
    system("pause");
}

void ListadosManager::listarDocentesPorCurso()
{
    rlutil::cls();

    int idCurso = seleccionarCurso();
    int indexCurso = _cursoArchivo.buscarByID(idCurso);
    Curso regCurso = _cursoArchivo.leer(indexCurso);
    mostrarEncabezadoCurso(regCurso, "DOCENTES DEL CURSO");

    if(!mostrarDocentesCurso(idCurso))
    {
        std::cout << "No hay docentes asignados en el curso..." << std::endl;
    }
    system("pause");
}

void ListadosManager::listarTemasPorEstado()
{

}

int ListadosManager::seleccionarCurso()
{
    Grado grado;
    Division division;
    int indexCurso;

    listarCursos();

    do
    {
        grado = pedirGrado();
        division = pedirDivision();

        indexCurso = _cursoArchivo.buscarByGradoDivision(grado,division);

        if(indexCurso == -1)
        {
            std::cout << "ERROR: No existe un curso registrado para "
                      << gradoToString(grado)
                      << " "
                      << divisionToString(division)
                      << "..."
                      << std::endl;
        }
    }
    while(indexCurso == -1);

    Curso regCurso = _cursoArchivo.leer(indexCurso);

    return regCurso.getIdCurso();
}

void ListadosManager::listarCursos()
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
            std::cout << "Grado: " << gradoToString(vCursos[i].getGrado()) << std::endl;
            std::cout << "Division: " << divisionToString(vCursos[i].getDivision()) << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
        }
    }

    delete[] vCursos;
}

void ListadosManager::mostrarEncabezadoCurso(const Curso &reg, const std::string &titulo)const
{
    std::cout << "----- "
              << titulo
              << " "
              << gradoToString(reg.getGrado())
              << " "
              << divisionToString(reg.getDivision())
              << " -----"
              << std::endl;
}

void ListadosManager::mostrarAlumno(const Alumno &reg)const
{
    std::cout << "Legajo: "
              << reg.getLegajo()
              << " - "
              << reg.getApellido()
              << ", "
              << reg.getNombre()
              << std::endl;
}

bool ListadosManager::mostrarAlumnosCurso(int idCurso)
{
    bool encontrado = false;
    int cantReg = _inscripcionArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Inscripcion regInscripcion = _inscripcionArchivo.leer(i);

        if(!regInscripcion.getEliminado())
        {
            if(regInscripcion.getIdCurso() == idCurso)
            {
                int indexAlumno = _alumnoArchivo.buscarByLegajo(regInscripcion.getLegajo());

                if(indexAlumno != -1)
                {
                    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);

                    if(!regAlumno.getEliminado())
                    {
                        encontrado = true;
                        mostrarAlumno(regAlumno);
                    }
                }
            }
        }
    }

    return encontrado;
}

void ListadosManager::mostrarDocente(const Docente &reg)const
{
    std::cout << "ID: "
              << reg.getIdDocente()
              << " - "
              << reg.getApellido()
              << ", "
              << reg.getNombre()
              << std::endl;
}

bool ListadosManager::mostrarDocentesCurso(int idCurso)
{
    bool encontrado = false;
    int cantReg = _asignacionDocenteArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        AsignacionDocente regAsigDocente = _asignacionDocenteArchivo.leer(i);

        if(!regAsigDocente.getEliminado())
        {
            if(regAsigDocente.getIdCurso() == idCurso)
            {
                int indexDocente = _docenteArchivo.buscarByID(regAsigDocente.getIdDocente());

                if(indexDocente != -1)
                {
                    Docente regDocente = _docenteArchivo.leer(indexDocente);

                    if(!regDocente.getEliminado())
                    {
                        encontrado = true;
                        mostrarDocente(regDocente);
                    }
                }
            }
        }
    }

    return encontrado;
}







