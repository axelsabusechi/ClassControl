#include <iostream>
#include "AlumnoManager.h"
#include "utils.h"
#include "rlutil.h"

AlumnoManager::AlumnoManager()
{
}

void AlumnoManager::registrarAlumno()
{
    if(_alumnoArchivo.guardar(crearAlumno()) == ArchivoError::OK)
    {
        std::cout << "\nAlumno registrado con exito!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_alumnoArchivo.getLastError());
    }
    std::cout << "----------------------------------------" << std::endl;
    system("pause");
    rlutil::cls();
}

void AlumnoManager::modificarAlumno()
{
    rlutil::cls();
    std::cout << "===== MODIFICAR ALUMNO =====" << std::endl;

    int cantReg = _alumnoArchivo.getCantRegActivos();

    if(!cantReg)
    {
        if(mostrarErrorArchivo(_alumnoArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo hay alumnos registrados para modificar..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    mostrarAlumnosActivos();

    int legajo = pedirEntero("\nLegajo del alumno a modificar: ");
    int index = _alumnoArchivo.buscarByLegajo(legajo);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_alumnoArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nEl alumno con legajo " << legajo << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Alumno reg = _alumnoArchivo.leer(index);

    if(reg.getLegajo() == -1)
    {
        mostrarErrorArchivo(_alumnoArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "\nEl alumno esta dado de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    mostrarAlumno(reg);

    if(!menuModificarAlumno(reg))
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    if(_alumnoArchivo.guardar(index,reg) == ArchivoError::OK)
    {
        std::cout << "\nEl alumno se modifico exitosamente!" << std::endl;
    }
    else
    {
        mostrarErrorArchivo(_alumnoArchivo.getLastError());
    }
    std::cout << "----------------------------------------" << std::endl;
    system("pause");
}

void AlumnoManager::eliminarAlumno()
{
    rlutil::cls();
    std::cout << "===== DAR DE BAJA ALUMNO =====" << std::endl;

    int cantReg = _alumnoArchivo.getCantRegActivos();

    if(cantReg == 0)
    {
        if(mostrarErrorArchivo(_alumnoArchivo.getLastError()))
        {
            system("pause");
            return;
        }

        std::cout << "\nNo hay alumnos registrados para dar de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    mostrarAlumnosActivos();

    int legajo = pedirEntero("\nLegajo del alumno a dar de baja: ");
    int index = _alumnoArchivo.buscarByLegajo(legajo);

    if(index == -1)
    {
        if(mostrarErrorArchivo(_alumnoArchivo.getLastError()))
        {
            system("pause");
            return;
        }
        std::cout << "\nEl alumno con legajo " << legajo << " no se encuentra en el sistema..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    Alumno reg = _alumnoArchivo.leer(index);

    if(reg.getLegajo() == -1)
    {
        mostrarErrorArchivo(_alumnoArchivo.getLastError());
        system("pause");
        return;
    }

    if(reg.getEliminado())
    {
        std::cout << "\nEl alumno ya esta dado de baja..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        system("pause");
        return;
    }

    std::cout << "===== DAR DE BAJA ALUMNO =====" << std::endl;
    std::cout << "\n----- ALUMNO SELECCIONADO -----" << std::endl;
    mostrarAlumno(reg);
    std::cout << "----------------------------------------" << std::endl;

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
        reg.setEliminado(true);

        if(_alumnoArchivo.guardar(index,reg) == ArchivoError::OK)
        {
            std::cout << "\nEl alumno con legajo " << legajo << " se dio de baja con exito!" << std::endl;
        }
        else
        {
            mostrarErrorArchivo(_alumnoArchivo.getLastError());
        }
    }
    else
    {
        std::cout << "\nOperacion cancelada..." << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    system("pause");
}

void AlumnoManager::listarAlumno()
{
    rlutil::cls();
    int cantReg;

    std::cout << "-------------LISTADO DE ALUMNOS--------------" << std::endl;
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

Alumno AlumnoManager::crearAlumno()
{
    int legajo;
    std::string nombre,apellido,dni,email,adaptacion;
    Fecha fechaNacimiento;

    legajo = _alumnoArchivo.getNewLegajo();

    rlutil::cls();

    std::cout << "===== REGISTRAR ALUMNO =====" << std::endl;
    std::cout << "Legajo: " << legajo << std::endl;
    std::cout << "----------------------------------------" << std::endl;

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

void AlumnoManager::cargarAlumno(std::string &nombre,
                                 std::string &apellido,
                                 std::string &dni,
                                 Fecha &fechaNacimiento,
                                 std::string &email,
                                 std::string &adaptacion)
{
    nombre = pedirNombreApellido("Nombre: ");
    apellido = pedirNombreApellido("Apellido: ");
    dni = cargarDniUnico("DNI: ");
    email = pedirEmail("E-mail: ");
    fechaNacimiento = pedirFecha("Fecha de nacimiento: ");
    adaptacion = pedirTexto("Adaptacion: ");
}

bool AlumnoManager::menuModificarAlumno(Alumno &reg)
{
    int opcion;

    do
    {
        rlutil::cls();
        std::cout << "===== MODIFICAR ALUMNO =====" << std::endl;
        std::cout << "\n----- DATOS ACTUALES -----" << std::endl;
        mostrarAlumno(reg);
        std::cout << "----------------------------------------" << std::endl;

        std::cout << "\n----- CAMPOS A MODIFICAR -----" << std::endl;
        std::cout << "1 - Nombre" << std::endl;
        std::cout << "2 - Apellido" << std::endl;
        std::cout << "3 - DNI" << std::endl;
        std::cout << "4 - Fecha de nacimiento" << std::endl;
        std::cout << "5 - Email" << std::endl;
        std::cout << "6 - Adaptacion" << std::endl;
        std::cout << "7 - Todos los campos" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "8 - Cancelar y salir " << std::endl;
        std::cout << "0 - Guardar y salir" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

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
            system("pause");
        }

        if(opcion >= 1 && opcion <= 7)
        {
            std::cout << "\nCampo modificado..." << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            system("pause");
        }
    }
    while(true);

    return false;
}

void AlumnoManager::modificarNombre(Alumno &reg)
{
    std::cout << std::endl;
    reg.setNombre(pedirNombreApellido("Nuevo nombre: "));
}

void AlumnoManager::modificarApellido(Alumno &reg)
{
    std::cout << std::endl;
    reg.setApellido(pedirNombreApellido("Nuevo apellido: "));
}

void AlumnoManager::modificarDni(Alumno &reg)
{
    std::cout << std::endl;
    reg.setDni(cargarDniUnico(("Nuevo DNI: "),reg.getLegajo()));
}
void AlumnoManager::modificarFechaNacimiento(Alumno &reg)
{
    std::cout << std::endl;
    reg.setFechaNacimiento(pedirFecha("Nueva fecha de nacimiento: "));
}

void AlumnoManager::modificarEmail(Alumno &reg)
{
    std::cout << std::endl;
    reg.setEmail(pedirEmail("Nuevo Email: "));
}

void AlumnoManager::modificarAdaptacion(Alumno &reg)
{
    std::cout << std::endl;
    reg.setAdaptacion(pedirTexto("Nueva adaptacion: "));
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

void AlumnoManager::mostrarAlumno(const Alumno &reg)const
{
    std::cout << "Legajo: " << reg.getLegajo() << std::endl;
    std::cout << "Nombre: " << reg.getNombre() << std::endl;
    std::cout << "Apellido: " << reg.getApellido() << std::endl;
    std::cout << "DNI: " << reg.getDni() << std::endl;
    std::cout << "Fecha de nacimiento: " << reg.getFechaNacimiento().toString() << std::endl;
    std::cout << "Email " << reg.getEmail() << std::endl;
    std::cout << "Adaptacion " << reg.getAdaptacion() << std::endl;
}

void AlumnoManager::mostrarAlumnosActivos()
{
    Alumno reg;
    int cantReg;

    cantReg = _alumnoArchivo.getCantReg();

    std::cout << "----- ALUMNOS ACTIVOS -----" << std::endl;

    for(int i = 0; i < cantReg; i++)
    {
        reg = _alumnoArchivo.leer(i);

        if(reg.getLegajo() == -1)
        {
            mostrarErrorArchivo(_alumnoArchivo.getLastError());
            system("pause");
            return;
        }

        if(!reg.getEliminado())
        {
            mostrarAlumno(reg);
            std::cout << "----------------------------------" << std::endl;
        }
    }
}

std::string AlumnoManager::cargarDniUnico(const std::string &mensaje, int legajoIgnorar)
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







