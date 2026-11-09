#include <cstring>
#include "Tema.h"

Tema::Tema()
    :_idTema(0),
     _idUnidad(0),
     _orden(0),
     _eliminado(false)
{
    strcpy(_nombre,"");
}

Tema::Tema(int idTema,
           int idUnidad,
           const std::string &nombre,
           int orden)
{
    setIdTema(idTema);
    setIdUnidad(idUnidad);
    setNombre(nombre);
    setOrden(orden);
    setEliminado(false);
}

void Tema::setIdTema(int idTema)
{
    _idTema = idTema;
}

void Tema::setIdUnidad(int idUnidad)
{
    _idUnidad = idUnidad;
}

void Tema::setNombre(const std::string &nombre)
{
    if(nombre.size() <= 79)
    {
        strcpy(_nombre, nombre.c_str());
    }
    else
    {
        strcpy(_nombre, nombre.substr(0, 79).c_str());
    }
}

void Tema::setOrden(int orden)
{
    _orden = orden;
}

void Tema::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int Tema::getIdTema()const
{
    return _idTema;
}

int Tema::getIdUnidad()const
{
    return _idUnidad;
}

std::string Tema::getNombre()const
{
    return std::string(_nombre);
}

int Tema::getOrden()const
{
    return _orden;
}

int Tema::getEliminado()const
{
    return _eliminado;
}
