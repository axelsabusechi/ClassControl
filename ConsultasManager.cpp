#include <iostream>
#include "ConsultasManager.h"
#include "rlutil.h"
#include "utils.h"

void ConsultasManager::consultarAlumnoPorLegajo()
{
    rlutil::cls();

    int legajo = seleccionarAlumno();
    int indexAlumno = _alumnoArchivo.buscarByLegajo(legajo);
    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);
    mostrarAlumno(regAlumno);

    system("pause");
}

void ConsultasManager::consultarDocentePorDni()
{
    rlutil::cls();

    std::string dni = seleccionarDocente();
    int indexDocente = _docenteArchivo.buscarByDni(dni);
    Docente regDocente = _docenteArchivo.leer(indexDocente);
    mostrarDocente(regDocente);

    system("pause");
}

void ConsultasManager::consultarNotasPorAlumno()
{
    rlutil::cls();

    int legajo = seleccionarAlumno();
    int indexAlumno = _alumnoArchivo.buscarByLegajo(legajo);
    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);
    mostrarAlumnoResumido(regAlumno);

    std::cout << "\n----- NOTAS DEL ALUMNO -----\n" << std::endl;

    if(!mostrarNotasAlumno(legajo))
    {
        std::cout << "El alumno no posee notas registradas..." << std::endl;
    }

    system("pause");
}

void ConsultasManager::consultarCurricularPorDocente()
{

}

void ConsultasManager::consultarDesempenioAcademicoPorAlumno()
{
    rlutil::cls();

    int legajo = seleccionarAlumno();
    int indexAlumno = _alumnoArchivo.buscarByLegajo(legajo);
    Alumno regAlumno = _alumnoArchivo.leer(indexAlumno);
    mostrarAlumno(regAlumno);

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
    }
    else
    {
        mostrarDesempenioAcademico(cantNotas,
                                   aprobadas,
                                   desaprobadas,
                                   aplazos,
                                   promedio);

        std::cout << std::endl;
        std::cout << "----- DETALLE DE NOTAS -----" << std::endl;

        mostrarNotasAlumno(legajo);
    }

    system("pause");

}

int ConsultasManager::seleccionarAlumno()
{
    listarAlumnos();
    std::cout << std::endl;

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

void ConsultasManager::listarAlumnos()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------ALUMNOS--------------" << std::endl;
    cantReg = _alumnoArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "No hay Alumnos registrados..." << std::endl;
    }
    else
    {
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
    }
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
    std::cout << "\nALUMNO: "
              << reg.getLegajo()
              << " - "
              << reg.getNombre()
              << " "
              << reg.getApellido()
              << std::endl;

    std::cout << "----------------------------------"
              << std::endl;
}

std::string ConsultasManager::seleccionarDocente()
{
    listarDocentes();
    std::cout << std::endl;

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

void ConsultasManager::mostrarDocente(const Docente &reg)const
{
    std::cout << "Id: " << reg.getIdDocente() << std::endl;
    std::cout << "Nombre: " << reg.getNombre() << std::endl;
    std::cout << "Apellido: " << reg.getApellido() << std::endl;
    std::cout << "DNI: " << reg.getDni() << std::endl;
}

void ConsultasManager::listarDocentes()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------DOCENTES--------------" << std::endl;
    cantReg = _docenteArchivo.getCantReg();

    if(cantReg == 0)
    {
        std::cout << "No hay docentes registrados..." << std::endl;
    }
    else
    {
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
    }
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

void ConsultasManager::mostrarDesempenioAcademico(
    int cantNotas,
    int aprobadas,
    int desaprobadas,
    int aplazos,
    float promedio)const
{
    std::cout << "----- DESEMPENIO ACADEMICO -----" << std::endl;
    std::cout << "Cantidad de notas: " << cantNotas << std::endl;
    std::cout << "Notas aprobadas: " << aprobadas << std::endl;
    std::cout << "Notas desaprobadas: " << desaprobadas << std::endl;
    std::cout << "Cantidad de aplazos: " << aplazos << std::endl;
    std::cout << "Promedio general: " << promedio << std::endl;
}



