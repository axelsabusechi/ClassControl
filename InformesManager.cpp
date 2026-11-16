#include <iostream>
#include "InformesManager.h"
#include "rlutil.h"
#include "utils.h"

void InformesManager::cantidadAlumnosPorGrado()
{
    rlutil::cls();

    int primero, segundo, tercero, cuarto, quinto, sexto;

    acumularAlumnosPorGrado(primero,
                            segundo,
                            tercero,
                            cuarto,
                            quinto,
                            sexto);

    mostrarCantAlumnosGrado(primero,
                            segundo,
                            tercero,
                            cuarto,
                            quinto,
                            sexto);
    system("pause");
}

void InformesManager::promedioNotasPorAlumno()
{
    rlutil::cls();

    int cantReg = _alumnoArchivo.getCantReg();

    if(cantReg == 0)
{
    std::cout << "No hay alumnos registrados..." << std::endl;

    system("pause");
    return;
}
    Alumno *vAlumnos = new Alumno[cantReg];
    _alumnoArchivo.leerTodos(vAlumnos,cantReg);

    std::cout << "----- PROMEDIO DE NOTAS POR ALUMNO -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        if(!vAlumnos[i].getEliminado())
        {
            float promedio = calcularPromedioAlumno(vAlumnos[i].getLegajo());
            mostrarPromedioAlumno(vAlumnos[i],promedio);
        }
    }

    delete[] vAlumnos;

    std::cout << "----------------------------------------" << std::endl;

    system("pause");
}

void InformesManager::cantidadClasesSuspendidasPorCurso()
{

}

void InformesManager::historialRendimientoPorCurso()
{
    rlutil::cls();

    int idCurso = seleccionarCurso();
    int indexCurso = _cursoArchivo.buscarByID(idCurso);
    Curso regCurso = _cursoArchivo.leer(indexCurso);

    mostrarEncabezadoCurso(regCurso, "RENDIMIENTO ACADEMICO");

    if(!mostrarHistorialRendimientoPorCurso(idCurso))
    {
        std::cout << "No existen alumnos inscriptos..." << std::endl;
    }

    system("pause");
}

void InformesManager::avanceCurricularPorCurso()
{

}

float InformesManager::calcularPromedioAlumno(int legajo)
{
    int acumNotas = 0;
    int cantNotas = 0;

    int cantReg = _notaArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Nota reg = _notaArchivo.leer(i);

        if(!reg.getEliminado() &&
                reg.getLegajo() == legajo)
        {
            acumNotas += reg.getNota();
            cantNotas++;
        }
    }

    if(cantNotas == 0)
    {
        return 0;
    }

    return (float)acumNotas / cantNotas;
}

void InformesManager::mostrarPromedioAlumno(const Alumno &reg, float promedio)const
{
    std::cout << reg.getLegajo()
              << " - "
              << reg.getApellido()
              << ", "
              << reg.getNombre()
              << " -> "
              << promedio
              << std::endl;

}

int InformesManager::seleccionarCurso()
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

void InformesManager::listarCursos()
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

void InformesManager::mostrarEncabezadoCurso(const Curso &reg, const std::string &titulo)const
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

void InformesManager::acumularAlumnosPorGrado(int &primero,
        int &segundo,
        int &tercero,
        int &cuarto,
        int &quinto,
        int &sexto)
{
    primero = 0;
    segundo = 0;
    tercero = 0;
    cuarto = 0;
    quinto = 0;
    sexto = 0;

    int cantReg = _inscripcionArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Inscripcion regIns = _inscripcionArchivo.leer(i);

        if(!regIns.getEliminado() && regIns.getActivo())
        {
            int indexCurso = _cursoArchivo.buscarByID(regIns.getIdCurso());

            if(indexCurso != -1)
            {
                Curso regCurso = _cursoArchivo.leer(indexCurso);

                if(!regCurso.getEliminado())
                {
                    switch(regCurso.getGrado())
                    {
                    case Grado::PRIMERO:
                        primero++;
                        break;
                    case Grado::SEGUNDO:
                        segundo++;
                        break;
                    case Grado::TERCERO:
                        tercero++;
                        break;
                    case Grado::CUARTO:
                        cuarto++;
                        break;
                    case Grado::QUINTO:
                        quinto++;
                        break;
                    case Grado::SEXTO:
                        sexto++;
                        break;
                    }
                }
            }
        }
    }
}

void InformesManager::mostrarCantAlumnosGrado(int primero,
        int segundo,
        int tercero,
        int cuarto,
        int quinto,
        int sexto)const
{
    std::cout << "Primero: " << primero << std::endl;
    std::cout << "Segundo: " << segundo << std::endl;
    std::cout << "Tercero: " << tercero << std::endl;
    std::cout << "Cuarto: " << cuarto << std::endl;
    std::cout << "Quinto: " << quinto << std::endl;
    std::cout << "Sexto: " << sexto << std::endl;
}

bool InformesManager::mostrarHistorialRendimientoPorCurso(int idCurso)
{
    bool encontrado = false;
    int cantReg = _inscripcionArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Inscripcion regIns = _inscripcionArchivo.leer(i);

        if(!regIns.getEliminado() && regIns.getActivo())
        {
            if(regIns.getIdCurso() == idCurso)
            {
                int indexAlumno = _alumnoArchivo.buscarByLegajo(regIns.getLegajo());

                if(indexAlumno != -1)
                {
                    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);

                    if(!regAlumno.getEliminado())
                    {
                        encontrado = true;
                        float promedio = calcularPromedioAlumno(regAlumno.getLegajo());
                        mostrarPromedioAlumno(regAlumno, promedio);
                    }
                }
            }
        }
    }

    return encontrado;
}


