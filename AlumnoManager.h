#pragma once
#include "Alumno.h"
#include "AlumnoArchivo.h"
#include "Fecha.h"

class AlumnoManager
{
public:
    AlumnoManager();

    void registrarAlumno();
    void modificarAlumno();
    void eliminarAlumno();
    void listarAlumno();

private:
    Alumno crearAlumno();
    void cargarAlumno(std::string &nombre,
                      std::string &apellido,
                      std::string &dni,
                      Fecha &fechaNacimiento,
                      std::string &email,
                      std::string &adaptacion);
    void mostrarAlumno(const Alumno &reg);
    void mostrarAlumnosActivos();
    std::string pedirDniUnico(const std::string &mensaje, int legajoIgnorar=-1);
    bool menuModificarAlumno(Alumno &reg);
    void modificarNombre(Alumno &reg);
    void modificarApellido(Alumno &reg);
    void modificarDni(Alumno &reg);
    void modificarFechaNacimiento(Alumno &reg);
    void modificarEmail(Alumno &reg);
    void modificarAdaptacion(Alumno &reg);
    void modificarTodos(Alumno &reg);

    AlumnoArchivo _alumnoArchivo;
};
