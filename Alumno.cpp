#include <cstring>
#include "Alumno.h"

Alumno::Alumno()
    :Persona(),
     _legajo(0),
     _fechaNacimiento(0,0,0),
     _eliminado(true)
{
    strcpy(_email,"");
    strcpy(_adaptacion,"");
}

Alumno::Alumno(//int id,
    std::string nombre,
    std::string apellido,
    std::string dni,
    int legajo,
    Fecha fechaNacimiento,
    std::string email,
    std::string adaptacion)
    :Persona(/*id,*/ nombre, apellido, dni)
{
    setLegajo(legajo);
    setFechaNacimiento(fechaNacimiento);
    setEmail(email);
    setAdaptacion(adaptacion);
    setEliminado(true);
}

void Alumno::setLegajo(int legajo)
{
    _legajo=legajo;
}

void Alumno::setFechaNacimiento(Fecha fechaNacimiento)
{
    _fechaNacimiento=fechaNacimiento;
}

void Alumno::setEmail(std::string email)
{
    if(email.size() <= 49)
    {
        strcpy(_email, email.c_str());
    }
    else
    {
        strcpy(_email, email.substr(0, 49).c_str());
    }
}

void Alumno::setAdaptacion(std::string adaptacion)
{
    if(adaptacion.size() <= 49)
    {
        strcpy(_adaptacion, adaptacion.c_str());
    }
    else
    {
        strcpy(_adaptacion, adaptacion.substr(0, 49).c_str());
    }
}

void Alumno::setEliminado(bool eliminado)
{
    _eliminado=eliminado;
}

int Alumno::getLegajo()
{
    return _legajo;
}

Fecha Alumno::getFechaNacimiento()
{
    return _fechaNacimiento;
}

std::string Alumno::getEmail()
{
    return std::string(_email);
}

std::string Alumno::getAdaptacion()
{
    return std::string(_adaptacion);
}

bool Alumno::getEliminado()
{
    return _eliminado;
}
