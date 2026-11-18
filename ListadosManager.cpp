#include <iostream>
#include "ListadosManager.h"
#include "rlutil.h"
#include "utils.h"

void ListadosManager::listarAlumnosPorCurso()
{
    rlutil::cls();

    int cantCursos = _cursoArchivo.getCantReg();
    bool hayCursos = false;

    std::cout << "===== LISTADO DE ALUMNOS POR CURSO =====" << std::endl;

    for(int i = 0; i < cantCursos; i++)
    {
        Curso regCurso = _cursoArchivo.leer(i);

        if(!regCurso.getEliminado())
        {
            hayCursos = true;
            std::cout << std::endl;
            mostrarEncabezadoCurso(regCurso, "CURSO:");

            if(!mostrarAlumnosCurso(regCurso.getIdCurso()))
            {
                std::cout << "  No hay alumnos inscriptos en el curso..." << std::endl;
            }
            std::cout << "----------------------------------------" << std::endl;
        }
    }

    if(!hayCursos)
    {
        std::cout << "\nNo hay cursos registrados..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    system("pause");
}

void ListadosManager::listarDocentesPorCurso()
{
    rlutil::cls();

    int cantCursos = _cursoArchivo.getCantReg();
    bool hayCursos = false;

    std::cout << "===== LISTADO DE DOCENTES POR CURSO =====" << std::endl;

    for(int i = 0; i < cantCursos; i++)
    {
        Curso regCurso = _cursoArchivo.leer(i);

        if(!regCurso.getEliminado())
        {
            hayCursos = true;
            std::cout << std::endl;
            mostrarEncabezadoCurso(regCurso, "CURSO:");

            if(!mostrarDocentesCurso(regCurso.getIdCurso()))
            {
                std::cout << "  No hay docentes asignados en el curso..." << std::endl;
            }
            std::cout << "-----------------------------------------" << std::endl;
        }
    }

    if(!hayCursos)
    {
        std::cout << "\nNo hay cursos registrados..." << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
    }

    system("pause");
}

void ListadosManager::listarTemasPorEstado()
{
    rlutil::cls();

    std::cout << "===== LISTADO DE TEMAS POR ESTADO =====" << std::endl;

    std::cout << std::endl;
    mostrarEncabezadoTemas(true);
    if(!mostrarTemasPorEstado(true))
    {
        std::cout << "No hay temas vistos registrados..." << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    std::cout << std::endl;
    mostrarEncabezadoTemas(false);
    if(!mostrarTemasPorEstado(false))
    {
        std::cout << "No hay temas pendientes registrados..." << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    system("pause");

}

void ListadosManager::mostrarEncabezadoCurso(const Curso &reg, const std::string &titulo) const
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

bool ListadosManager::mostrarAlumnosCurso(int idCurso)
{
    bool encontrado = false;
    int cantReg = _inscripcionArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Inscripcion regInscripcion = _inscripcionArchivo.leer(i);

        if(!regInscripcion.getEliminado() && regInscripcion.getActivo())
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

void ListadosManager::mostrarAlumno(const Alumno &reg) const
{
    std::cout << "Legajo: "
              << reg.getLegajo()
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

void ListadosManager::mostrarDocente(const Docente &reg) const
{
    std::cout << "ID: "
              << reg.getIdDocente()
              << " - "
              << reg.getApellido()
              << ", "
              << reg.getNombre()
              << std::endl;
}

void ListadosManager::mostrarEncabezadoTemas(bool estado) const
{
    std::cout << (estado ? "----- TEMAS VISTOS -----" : "----- TEMAS PENDIENTES -----")
              << std::endl;
}

bool ListadosManager::mostrarTemasPorEstado(bool visto)
{
    bool encontrado = false;
    int cantReg = _temaArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Tema regTema = _temaArchivo.leer(i);

        if(!regTema.getEliminado())
        {
            bool estadoTema = temaVisto(regTema.getIdTema());

            if(estadoTema == visto)
            {
                encontrado = true;
                mostrarTema(regTema);
            }
        }
    }

    return encontrado;
}

void ListadosManager::mostrarTema(const Tema &reg) const
{
    std::cout << "Id: " << reg.getIdTema() << std::endl;
    std::cout << "Tema: " << reg.getNombre() << std::endl;
    std::cout << "Orden: " << reg.getOrden() << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

bool ListadosManager::temaVisto(int idTema)
{
    int cantReg = _claseDadaArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        ClaseDada reg = _claseDadaArchivo.leer(i);

        if(!reg.getEliminado() &&
           reg.getIdTema() == idTema &&
           reg.getClaseDada())
        {
            return true;
        }
    }

    return false;
}















