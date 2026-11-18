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

    std::cout << "===== CANTIDAD DE ALUMNOS POR GRADO =====" << std::endl;

    mostrarCantAlumnosGrado(primero,
                            segundo,
                            tercero,
                            cuarto,
                            quinto,
                            sexto);

    std::cout << "-----------------------------------------" << std::endl;

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

    std::cout << "===== PROMEDIO DE NOTAS POR ALUMNO =====" << std::endl;

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
    rlutil::cls();

    int cantCursos = _cursoArchivo.getCantReg();

    bool hayCursos = false;

    std::cout << "===== CLASES SUSPENDIDAS POR CURSO =====" << std::endl;

    for(int i=0; i<cantCursos; i++)
    {
        Curso regCurso = _cursoArchivo.leer(i);

        if(!regCurso.getEliminado())
        {
            hayCursos = true;
            int suspendidas = contarClasesSuspendidas(regCurso.getIdCurso());

            std::cout << "Curso: "
                      << gradoToString(regCurso.getGrado())
                      << " "
                      << divisionToString(regCurso.getDivision())
                      << " - Clases suspendidas: "
                      << suspendidas
                      << std::endl;
        }
    }

    if(!hayCursos)
    {
        std::cout << "No hay cursos registrados..." << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;

    system("pause");
}

void InformesManager::historialRendimientoPorCurso()
{
    rlutil::cls();

    int cantCursos = _cursoArchivo.getCantReg();
    bool hayCursos = false;

    std::cout << "===== RENDIMIENTO ACADEMICO POR CURSO =====" << std::endl;

    for(int i=0; i<cantCursos; i++)
    {
        Curso regCurso = _cursoArchivo.leer(i);

        if(!regCurso.getEliminado())
        {
            hayCursos = true;

            std::cout << "Curso: "
                      << gradoToString(regCurso.getGrado())
                      << " "
                      << divisionToString(regCurso.getDivision())
                      << std::endl;

            if(!mostrarHistorialRendimientoPorCurso(regCurso.getIdCurso()))
            {
                std::cout << "  No existen alumnos inscriptos..." << std::endl;
            }

            std::cout << "-------------------------------------------" << std::endl;
        }
    }

    if(!hayCursos)
    {
        std::cout << "No hay cursos registrados..." << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
    }

    system("pause");
}

void InformesManager::avanceCurricularPorCurso()
{
    rlutil::cls();

    int cantCursos = _cursoArchivo.getCantReg();
    bool hayCursos = false;

    std::cout << "===== AVANCE CURRICULAR POR CURSO =====" << std::endl;

    for(int i = 0; i < cantCursos; i++)
    {
        Curso regCurso = _cursoArchivo.leer(i);

        if(!regCurso.getEliminado())
        {
            hayCursos = true;
            int totalTemas = 0;
            int temasVistos = 0;

            calcularAvanceCurso(regCurso.getIdCurso(), totalTemas, temasVistos);

            std::cout << "Curso: "
                      << gradoToString(regCurso.getGrado())
                      << " "
                      << divisionToString(regCurso.getDivision())
                      << std::endl;

            if(totalTemas == 0)
            {
                std::cout << "  Sin temas registrados en la curricula." << std::endl;
            }
            else
            {
                float porcentaje = ((float)temasVistos/totalTemas)*100;

                std::cout << " Temas vistos: " << temasVistos << " / " << totalTemas << std::endl;
                std::cout << " Avance: " << porcentaje << "%" << std::endl;
            }
            std::cout << "---------------------------------------" << std::endl;
        }
    }

    if(!hayCursos)
    {
        std::cout << "No hay cursos registrados..." << std::endl;
    }

    system("pause");
}

void InformesManager::mostrarPromedioAlumno(const Alumno &reg, float promedio)const
{
    std::cout << reg.getLegajo()
              << " - "
              << reg.getApellido()
              << ", "
              << reg.getNombre()
              << " : "
              << promedio
              << std::endl;

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

    for(int i=0; i<cantReg; i++)
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



int InformesManager::contarClasesSuspendidas(int idCurso)
{
    int cont = 0;
    int cantReg = _claseDadaArchivo.getCantReg();

    for(int i=0; i<cantReg; i++)
    {
        ClaseDada reg = _claseDadaArchivo.leer(i);

        if(!reg.getEliminado() &&
                reg.getIdCurso() == idCurso &&
                !reg.getClaseDada())
        {
            cont++;
        }
    }

    return cont;
}

void InformesManager::calcularAvanceCurso(int idCurso, int &totalTemas, int &temasVistos)
{
    totalTemas = 0;
    temasVistos = 0;

    int cantUnidades = _unidadDidacticaArchivo.getCantReg();
    int cantTemas = _temaArchivo.getCantReg();

    for(int i=0; i<cantUnidades; i++)
    {
        UnidadDidactica regUnidad = _unidadDidacticaArchivo.leer(i);

        if(!regUnidad.getEliminado() && regUnidad.getIdCurso() == idCurso)
        {
            for(int j=0; j<cantTemas; j++)
            {
                Tema regTema = _temaArchivo.leer(j);

                if(!regTema.getEliminado() && regTema.getIdUnidad() == regUnidad.getIdUnidad())
                {
                    totalTemas++;

                    if(temaVisto(regTema.getIdTema()))
                    {
                        temasVistos++;
                    }
                }
            }
        }
    }
}

bool InformesManager::temaVisto(int idTema)
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

