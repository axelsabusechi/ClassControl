#include <iostream>
#include "AlumnoManager.h"
#include "utils.h"
#include "rlutil.h"

AlumnoManager::AlumnoManager()
{
}

Alumno AlumnoManager::crearAlumno()
{
    int legajo;
    std::string nombre,apellido,dni,email,adaptacion;
    Fecha fechaNacimiento;

    legajo = _alumnoArchivo.getNewLegajo();

    rlutil::cls();

    std::cout << "-----CARGAR ALUMNO-------" << std::endl;
    std::cout << "Legajo: " << legajo << std::endl << std::endl;

    cargarAlumno(nombre,
                 apellido,
                 dni,
                 fechaNacimiento,
                 email,
                 adaptacion);

    return Alumno(nombre,
                  apellido,
                  dni,
                  legajo,
                  fechaNacimiento,
                  email,
                  adaptacion);
}

void AlumnoManager::registrarAlumno()
{
    if(_alumnoArchivo.guardar(crearAlumno()) == ArchivoError::OK)
    {
        std::cout << "Alumno registrado..." << std::endl;
    }
    else
    {
        std::cout << "Error: " << _alumnoArchivo.getLastError() << std::endl;
    }
    system("pause");
    rlutil::cls();
}

void AlumnoManager::listarAlumno()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------Listado de Alumnos--------------" << std::endl;
    cantReg = _alumnoArchivo.getCantReg();

    if(!cantReg)
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
                mostrarAlumno(vAlumnos[i]);
                std::cout << "--------------------------------------------" << std::endl;
            }
        }
        delete []vAlumnos;
    }
    system("pause");
    rlutil::cls();
}

void AlumnoManager::modificarAlumno()
{
    rlutil::cls();
    int index, legajo,cantReg;
    Alumno reg;

    cantReg = _alumnoArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay Alumnos registrados para modificar..." << std::endl;
        system("pause");
        return;
    }

    legajo = pedirEntero("Legajo del alumno a modificar: ");

    index = _alumnoArchivo.buscarByLegajo(legajo);

    if(index == -1)
    {
        std::cout << "El Alumno con legajo " << legajo << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    reg = _alumnoArchivo.leer(index);

    if(reg.getEliminado())
    {
        std::cout << "El alumno esta dado de baja." << std::endl;
        system("pause");
        return;
    }

    mostrarAlumno(reg);

    if(!menuModificarAlumno(reg))
    {
        std::cout << "Operacion cancelada..." << std::endl;
        system("pause");
        return;
    }

    if(_alumnoArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "Se modifico exitosamente!" << std::endl;
    }
    else
    {
        std::cout << "Ocurrio un error al guardar el Alumno: " << _alumnoArchivo.getLastError() << std::endl;
    }

    system("pause");
}

void AlumnoManager::eliminarAlumno()
{
    rlutil::cls();
    int index, legajo, cantReg;
    Alumno reg;

    cantReg = _alumnoArchivo.getCantReg();

    if(!cantReg)
    {
        std::cout << "No hay Alumnos registrados para dar de baja..." << std::endl;
        system("pause");
        return;
    }

    legajo = pedirEntero("Legajo del alumno a dar de baja: ");

    index = _alumnoArchivo.buscarByLegajo(legajo);

    if(index == -1)
    {
        std::cout << "El Alumno con ID " << legajo << " no se encuentra en el sistema..." << std::endl;
        system("pause");
        return;
    }

    reg = _alumnoArchivo.leer(index);

    if(reg.getEliminado())
    {
        std::cout << "El alumno esta dado de baja." << std::endl;
        system("pause");
        return;
    }

    if(reg.getLegajo() == -1)
    {
        std::cout << "Error Alumno no encontrado por ID";
        system("pause");
        return;
    }

    mostrarAlumno(reg);

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
        reg.setEliminado(true);

        if(_alumnoArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "Alumno con legajo " << legajo << " se dio de baja con exito!" << std::endl;
        }
    }
    else
    {
        std::cout << "Operacion cancelada..." << std::endl;
    }

    system("pause");
}

void AlumnoManager::cargarAlumno(std::string &nombre,
                                 std::string &apellido,
                                 std::string &dni,
                                 Fecha &fechaNacimiento,
                                 std::string &email,
                                 std::string &adaptacion)
{
    nombre = pedirNombreApellido("Nombre: ");
    apellido = pedirNombreApellido("Apellido: ");
    dni = pedirDniUnico("DNI: ");
    email = pedirEmail("E-mail: ");
    fechaNacimiento = pedirFecha("Fecha de nacimiento: ");
    adaptacion = pedirAdaptacion("Adaptacion: ");
}

void AlumnoManager::mostrarAlumno(const Alumno &reg)
{
    std::cout << "Legajo: " << reg.getLegajo() << std::endl;
    std::cout << "Nombre: " << reg.getNombre() << std::endl;
    std::cout << "Apellido: " << reg.getApellido() << std::endl;
    std::cout << "DNI: " << reg.getDni() << std::endl;
    std::cout << "Fecha de nacimiento: " << reg.getFechaNacimiento().toString() << std::endl;
    std::cout << "Email " << reg.getEmail() << std::endl;
    std::cout << "Adaptacion " << reg.getAdaptacion() << std::endl;
}

std::string AlumnoManager::pedirDniUnico(const std::string &mensaje, int legajoIgnorar)
{
    std::string dni;
    bool existe = false;

    do
    {
        dni = pedirDni(mensaje);
        existe = _alumnoArchivo.existeDni(dni,legajoIgnorar);

        if(existe)
        {
            std::cout << "ERROR: Ya existe un alumno con ese DNI..." << std::endl;
        }
    }
    while(existe);
    return dni;
}

bool AlumnoManager::menuModificarAlumno(Alumno &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "----- DATOS ACTUALES DEL ALUMNO -----" << std::endl;
        mostrarAlumno(reg);

        std::cout << "\n----- MODIFICAR ALUMNO -----" << std::endl;
        std::cout << "1 - Nombre" << std::endl;
        std::cout << "2 - Apellido" << std::endl;
        std::cout << "3 - DNI" << std::endl;
        std::cout << "4 - Fecha de nacimiento" << std::endl;
        std::cout << "5 - Email" << std::endl;
        std::cout << "6 - Adaptacion" << std::endl;
        std::cout << "7 - Todos los campos" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "8 - Cancelar y salir " << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;

        opcion = pedirEntero("Opcion: ");

        switch(opcion)
        {
        case 1:
            modificarNombre(reg);
            break;

        case 2:
            modificarApellido(reg);
            break;

        case 3:
            modificarDni(reg);
            break;

        case 4:
            modificarFechaNacimiento(reg);
            break;

        case 5:
            modificarEmail(reg);
            break;

        case 6:
            modificarAdaptacion(reg);
            break;

        case 7:
            modificarTodos(reg);
            break;

        case 8:
            return false;

        case 0:
            return true;

        default:
            std::cout << "ERROR. Opcion invalida." << std::endl;
        }

        if(opcion >= 1 && opcion <= 7)
        {
            std::cout << "Campo modificado..." << std::endl;
            system("pause");
        }
    }
    while(true);

    return false;
}

void AlumnoManager::modificarNombre(Alumno &reg)
{
    reg.setNombre(pedirNombreApellido("Nuevo nombre: "));
}

void AlumnoManager::modificarApellido(Alumno &reg)
{
    reg.setApellido(pedirNombreApellido("Nuevo apellido: "));
}

void AlumnoManager::modificarDni(Alumno &reg)
{
    reg.setDni(pedirDniUnico(("Nuevo DNI: "),reg.getLegajo()));
}
void AlumnoManager::modificarFechaNacimiento(Alumno &reg)
{
    reg.setFechaNacimiento(pedirFecha("Nueva fecha de nacimiento: "));
}

void AlumnoManager::modificarEmail(Alumno &reg)
{
    reg.setEmail(pedirEmail("Nuevo Email: "));
}

void AlumnoManager::modificarAdaptacion(Alumno &reg)
{
    reg.setAdaptacion(pedirAdaptacion("Nueva adaptacion: "));
}

void AlumnoManager::modificarTodos(Alumno &reg)
{
    modificarNombre(reg);
    modificarApellido(reg);
    modificarDni(reg);
    modificarFechaNacimiento(reg);
    modificarEmail(reg);
    modificarAdaptacion(reg);
}

