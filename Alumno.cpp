#include <cstring>
#include "Alumno.h"

Alumno::Alumno()
    :Persona(),
     _legajo(0),
     _fechaNacimiento(0,0,0),
     _eliminado(false)
{
    strcpy(_email,"");
    strcpy(_adaptacion,"");
}

Alumno::Alumno(//int id,
    const std::string &nombre,
    const std::string &apellido,
    const std::string &dni,
    int legajo,
    const Fecha &fechaNacimiento,
    const std::string &email,
    const std::string &adaptacion)
    :Persona(/*id,*/ nombre, apellido, dni)
{
    setLegajo(legajo);
    setFechaNacimiento(fechaNacimiento);
    setEmail(email);
    setAdaptacion(adaptacion);
    setEliminado(false);
}

void Alumno::setLegajo(int legajo)
{
    _legajo=legajo;
}

void Alumno::setFechaNacimiento(const Fecha &fechaNacimiento)
{
    _fechaNacimiento = fechaNacimiento;
}

void Alumno::setEmail(const std::string &email)
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

void Alumno::setAdaptacion(const std::string &adaptacion)
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
    _eliminado = eliminado;
}

int Alumno::getLegajo()const
{
    return _legajo;
}

Fecha Alumno::getFechaNacimiento()const
{
    return _fechaNacimiento;
}

std::string Alumno::getEmail()const
{
    return std::string(_email);
}

std::string Alumno::getAdaptacion()const
{
    return std::string(_adaptacion);
}

bool Alumno::getEliminado()const
{
    return _eliminado;
}
