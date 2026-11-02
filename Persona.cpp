#include "Persona.h"
#include <cstring>

Persona::Persona()
    //: //_id(0),
      //_eliminado(true)
{
    strcpy(_nombre,"");
    strcpy(_apellido,"");
    strcpy(_dni,"");
}

Persona::Persona(//int id,
    std::string nombre,
    std::string apellido,
    std::string dni)
{
    //setID(id);
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
    //setEliminado(true);
}
/*
void Persona::setID(int id)
{
    _id=id;
}*/

void Persona::setNombre(std::string nombre)
{
    if(nombre.size() <= 49)
    {
        strcpy(_nombre, nombre.c_str());
    }
    else
    {
        strcpy(_nombre, nombre.substr(0, 49).c_str());
    }
}

void Persona::setApellido(std::string apellido)
{
    if(apellido.size() <= 49)
    {
        strcpy(_apellido, apellido.c_str());
    }
    else
    {
        strcpy(_apellido, apellido.substr(0, 49).c_str());
    }
}

void Persona::setDni(std::string dni)
{
    if(dni.size() <= 49)
    {
        strcpy(_dni, dni.c_str());
    }
    else
    {
        strcpy(_dni, dni.substr(0, 49).c_str());
    }
}
/*
void Persona::setEliminado(bool eliminado)
{
    _eliminado=eliminado;
}*/
/*
int Persona::getID()
{
    return _id;
}*/

std::string Persona::getNombre()
{
    return std::string(_nombre);
}

std::string Persona::getApellido()
{
    return std::string(_apellido);
}

std::string Persona::getDni()
{
    return std::string(_dni);
}
/*
bool Persona::getEliminado()
{
    return _eliminado;
}*/
