#include <iostream>
#include "ConsultasManager.h"
#include "rlutil.h"
#include "utils.h"

void ConsultasManager::consultarAlumnoPorLegajo()
{
    rlutil::cls();

    int legajo = seleccionarAlumno();

    if(legajo == -1)
    {
        std::cout << "No hay alumnos registrados..." << std::endl;
        system("pause");
        return;
    }

    int indexAlumno = _alumnoArchivo.buscarByLegajo(legajo);
    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);

    rlutil::cls();
    std::cout << "===== FICHA DEL ALUMNO =====" << std::endl;
    mostrarAlumno(regAlumno);
    std::cout << "----------------------------" << std::endl;

    system("pause");
}

void ConsultasManager::consultarDocentePorDni()
{
    rlutil::cls();

    std::string dni = seleccionarDocente();

    if(dni == "")
    {
        std::cout << "No hay docentes registrados..." << std::endl;
        system("pause");
        return;
    }

    int indexDocente = _docenteArchivo.buscarByDni(dni);
    Docente regDocente = _docenteArchivo.leer(indexDocente);

    rlutil::cls();
    std::cout << "===== FICHA DEL DOCENTE =====" << std::endl;
    mostrarDocente(regDocente);
    std::cout << "-----------------------------" << std::endl;

    system("pause");
}

void ConsultasManager::consultarNotasPorAlumno()
{
    rlutil::cls();

    int legajo = seleccionarAlumno();

    if(legajo == -1)
    {
        std::cout << "No hay alumnos registrados..." << std::endl;
        system("pause");
        return;
    }

    int indexAlumno = _alumnoArchivo.buscarByLegajo(legajo);
    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);

    rlutil::cls();
    mostrarAlumnoResumido(regAlumno);
    std::cout << "\n===== NOTAS DEL ALUMNO =====\n" << std::endl;

    if(!mostrarNotasAlumno(legajo))
    {
        std::cout << "El alumno no posee notas registradas..." << std::endl;
        std::cout << "----------------------------" << std::endl;
    }

    system("pause");
}

void ConsultasManager::consultarCurriculaPorDocente()
{
    rlutil::cls();

    std::string dni = seleccionarDocente();

    if(dni == "")
    {
        std::cout << "No hay docentes registrados..." << std::endl;
        system("pause");
        return;
    }

    int indexDocente = _docenteArchivo.buscarByDni(dni);
    Docente regDocente = _docenteArchivo.leer(indexDocente);

    rlutil::cls();
    mostrarDocenteResumido(regDocente);

    if(!mostrarCurriculaDocente(regDocente.getIdDocente()))
    {
        std::cout << "El docente no tiene cursos asignados..." << std::endl;
    }

    std::cout << "-------------------" << std::endl;

    system("pause");
}

void ConsultasManager::consultarDesempenioAcademicoPorAlumno()
{
    rlutil::cls();

    int legajo = seleccionarAlumno();

    if(legajo == -1)
    {
        std::cout << "No hay alumnos registrados..." << std::endl;
        system("pause");
        return;
    }

    int indexAlumno = _alumnoArchivo.buscarByLegajo(legajo);
    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);

    rlutil::cls();
    std::cout << "===== ALUMNO =====" << std::endl;
    mostrarAlumno(regAlumno);
    std::cout << std::endl;

    int cantNotas, aprobadas, desaprobadas, aplazos;

    float promedio = calcularDesempenioAcademico(
                         legajo,
                         cantNotas,
                         aprobadas,
                         desaprobadas,
                         aplazos);

    if(cantNotas == 0)
    {
        std::cout << "El alumno no posee notas registradas..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    else
    {
        mostrarDesempenioAcademico(cantNotas,
                                   aprobadas,
                                   desaprobadas,
                                   aplazos,
                                   promedio);
        std::cout << std::endl;
        std::cout << "===== DETALLE DE NOTAS =====" << std::endl;
        mostrarNotasAlumno(legajo);
    }
    system("pause");
}

int ConsultasManager::seleccionarAlumno()
{
    if(!hayAlumnosActivos())
    {
        return -1;
    }

    listarAlumnos();

    int legajo;
    bool existe = false;

    do
    {
        legajo = pedirEntero("Legajo alumno: ");
        existe = _alumnoArchivo.existeAlumno(legajo);

        if(!existe)
        {
            std::cout << "ERROR: El alumno con legajo "
                      << legajo
                      << " no se encuentra en el sistema..."
                      << std::endl;
        }
    }
    while(!existe);

    return legajo;
}

std::string ConsultasManager::seleccionarDocente()
{
    if(!hayDocentesActivos())
    {
        return "";
    }

    listarDocentes();

    std::string dni;
    bool existe = false;

    do
    {
        dni = pedirDni("DNI docente: ");
        existe = _docenteArchivo.existeDni(dni);

        if(!existe)
        {
            std::cout << "ERROR: El docente con DNI "
                      << dni
                      << " no se encuentra en el sistema..."
                      << std::endl;
        }
    }
    while(!existe);

    return dni;
}

void ConsultasManager::listarAlumnos()
{
    int cantReg;

    std::cout << "===== ALUMNOS =====" << std::endl;
    cantReg = _alumnoArchivo.getCantReg();


    Alumno *vAlumnos = new Alumno[cantReg];
    _alumnoArchivo.leerTodos(vAlumnos,cantReg);

    for(int i=0; i<cantReg; i++)
    {
        if(!vAlumnos[i].getEliminado())
        {
            std::cout << "Legajo "
                      << vAlumnos[i].getLegajo()
                      << " - "
                      << vAlumnos[i].getNombre()
                      << " "
                      << vAlumnos[i].getApellido()
                      << std::endl;
        }
    }
    delete []vAlumnos;

    std::cout << "-------------------" << std::endl;
}

void ConsultasManager::mostrarAlumno(const Alumno &reg)const
{
    std::cout << "Legajo: " << reg.getLegajo() << std::endl;
    std::cout << "Nombre: " << reg.getNombre() << std::endl;
    std::cout << "Apellido: " << reg.getApellido() << std::endl;
    std::cout << "DNI: " << reg.getDni() << std::endl;
    std::cout << "Email: " << reg.getEmail() << std::endl;
}

void ConsultasManager::mostrarAlumnoResumido(const Alumno &reg)const
{
    std::cout << "===== ALUMNO =====" << std::endl;
    std::cout << "Legajo: " << reg.getLegajo()
              << " - " << reg.getNombre()
              << " " << reg.getApellido() << std::endl;
    std::cout << "------------------" << std::endl;
}

void ConsultasManager::listarDocentes()
{
    int cantReg;

    std::cout << "===== DOCENTES =====" << std::endl;

    cantReg = _docenteArchivo.getCantReg();

    Docente *vDocentes = new Docente[cantReg];
    _docenteArchivo.leerTodos(vDocentes,cantReg);

    for(int i=0; i<cantReg; i++)
    {
        if(!vDocentes[i].getEliminado())
        {
            std::cout << "DNI "
                      << vDocentes[i].getDni()
                      << " - "
                      << vDocentes[i].getNombre()
                      << " "
                      << vDocentes[i].getApellido()
                      << std::endl;
        }
    }
    delete []vDocentes;

    std::cout << "-------------------" << std::endl;
}

void ConsultasManager::mostrarDocente(const Docente &reg)const
{
    std::cout << "Id: " << reg.getIdDocente() << std::endl;
    std::cout << "Nombre: " << reg.getNombre() << std::endl;
    std::cout << "Apellido: " << reg.getApellido() << std::endl;
    std::cout << "DNI: " << reg.getDni() << std::endl;
}

void ConsultasManager::mostrarDocenteResumido(const Docente &reg)const
{
    std::cout << "===== DOCENTE =====" << std::endl;
    std::cout << reg.getApellido() << ", " << reg.getNombre()
              << " (DNI: " << reg.getDni() << ")" << std::endl;
    std::cout << "-------------------" << std::endl;
}

bool ConsultasManager::mostrarNotasAlumno(int legajo)
{
    bool encontrado = false;

    int cantReg = _notaArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Nota regNota = _notaArchivo.leer(i);

        if(!regNota.getEliminado())
        {
            if(regNota.getLegajo() == legajo)
            {
                encontrado = true;
                mostrarNota(regNota);
            }
        }
    }

    return encontrado;
}

void ConsultasManager::mostrarNota(const Nota &reg)const
{
    std::cout << "Periodo: " << periodoToString(reg.getPeriodo()) << std::endl;
    std::cout << "Descripcion: " << reg.getDescripcion() << std::endl;
    std::cout << "Nota: " << reg.getNota() << std::endl;
    std::cout << "Fecha: " << reg.getFechaCarga().toString() << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

void ConsultasManager::mostrarDesempenioAcademico(
    int cantNotas,
    int aprobadas,
    int desaprobadas,
    int aplazos,
    float promedio)const
{
    std::cout << "===== DESEMPENIO ACADEMICO =====" << std::endl;
    std::cout << "Cantidad de notas: " << cantNotas << std::endl;
    std::cout << "Notas aprobadas: " << aprobadas << std::endl;
    std::cout << "Notas desaprobadas: " << desaprobadas << std::endl;
    std::cout << "Cantidad de aplazos: " << aplazos << std::endl;
    std::cout << "Promedio general: " << promedio << std::endl;
}

bool ConsultasManager::mostrarCurriculaDocente(int idDocente)
{
    bool tieneCursos = false;

    int cantReg = _asignacionDocenteArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        AsignacionDocente regAsig = _asignacionDocenteArchivo.leer(i);

        if(!regAsig.getEliminado() && regAsig.getIdDocente() == idDocente)
        {
            int indexCurso = _cursoArchivo.buscarByID(regAsig.getIdCurso());

            if(indexCurso != -1)
            {
                Curso regCurso = _cursoArchivo.leer(indexCurso);

                if(!regCurso.getEliminado())
                {
                    tieneCursos = true;

                    std::cout << "\nCURSO: "
                              << gradoToString(regCurso.getGrado())
                              << " "
                              << divisionToString(regCurso.getDivision())
                              << std::endl;
                    std::cout << "-------------------" << std::endl;

                    if(!mostrarUnidadesCurso(regCurso.getIdCurso()))
                    {
                        std::cout << "  Sin unidades didacticas cargadas..." << std::endl;
                    }
                }
            }
        }
    }

    return tieneCursos;
}

bool ConsultasManager::mostrarUnidadesCurso(int idCurso)
{
    bool tieneUnidades = false;

    int cantReg = _unidadDidacticaArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        UnidadDidactica regUnidad = _unidadDidacticaArchivo.leer(i);

        if(!regUnidad.getEliminado() && regUnidad.getIdCurso() == idCurso)
        {
            tieneUnidades = true;

            std::cout << "Unidad " << regUnidad.getOrden()
                      << ": " << regUnidad.getNombre()
                      << std::endl;

            if(!mostrarTemasUnidad(regUnidad.getIdUnidad()))
            {
                std::cout << "    - Sin temas cargados..." << std::endl;
            }
        }
    }

    return tieneUnidades;
}

bool ConsultasManager::mostrarTemasUnidad(int idUnidad)
{
    bool tieneTemas = false;

    int cantReg = _temaArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Tema regTema = _temaArchivo.leer(i);

        if(!regTema.getEliminado() && regTema.getIdUnidad() == idUnidad)
        {
            tieneTemas = true;

            bool visto = temaVisto(regTema.getIdTema());

            std::cout << " * Tema " << regTema.getOrden()
                      << ": " << regTema.getNombre()
                      << (visto ? " [VISTO]" : " [PENDIENTE]")
                      << std::endl;
        }
    }

    return tieneTemas;
}

float ConsultasManager::calcularDesempenioAcademico(int legajo,
        int &cantNotas,
        int &aprobadas,
        int &desaprobadas,
        int &aplazos)
{
    cantNotas = 0;
    aprobadas = 0;
    desaprobadas = 0;
    aplazos = 0;

    int acumNotas = 0;
    int cantReg = _notaArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Nota reg = _notaArchivo.leer(i);

        if(!reg.getEliminado())
        {
            if(reg.getLegajo() == legajo)
            {
                int nota = reg.getNota();

                acumNotas += nota;
                cantNotas++;

                if(nota >= 6)
                {
                    aprobadas++;
                }
                else
                {
                    desaprobadas++;
                }

                if(nota <= 3)
                {
                    aplazos++;
                }
            }
        }
    }

    if(cantNotas == 0)
    {
        return 0;
    }

    return (float)acumNotas/cantNotas;
}


bool ConsultasManager::hayAlumnosActivos()
{
    int cantReg = _alumnoArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Alumno reg = _alumnoArchivo.leer(i);
        if(!reg.getEliminado())
        {
            return true;
        }
    }

    return false;
}
bool ConsultasManager::hayDocentesActivos()
{
    int cantReg = _docenteArchivo.getCantReg();

    for(int i = 0; i < cantReg; i++)
    {
        Docente reg = _docenteArchivo.leer(i);
        if(!reg.getEliminado())
        {
            return true;
        }
    }

    return false;
}

bool ConsultasManager::temaVisto(int idTema)
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




