#include <cstring>
#include "UnidadDidactica.h"

UnidadDidactica::UnidadDidactica()
    :_idUnidad(0),
     _idCurso(0),
     _orden(0),
     _eliminado(false)
{
    strcpy(_nombre,"");
}

UnidadDidactica::UnidadDidactica(int idUnidad,
                                 int idCurso,
                                 const std::string &nombre,
                                 int orden)
{
    setIdUnidad(idUnidad);
    setIdCurso(idCurso);
    setNombre(nombre);
    setOrden(orden);
    setEliminado(false);
}

void UnidadDidactica::setIdUnidad(int idUnidad)
{
    _idUnidad = idUnidad;
}

void UnidadDidactica::setIdCurso(int idCurso)
{
    _idCurso = idCurso;
}

void UnidadDidactica::setNombre(const std::string &nombre)
{
    if(nombre.size() <= 49)
    {
        strcpy(_nombre, nombre.c_str());
    }
    else
    {
        strcpy(_nombre, nombre.substr(0,49).c_str());
    }
}

void UnidadDidactica::setOrden(int orden)
{
    _orden = orden;
}

void UnidadDidactica::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int UnidadDidactica::getIdUnidad()const
{
    return _idUnidad;
}

int UnidadDidactica::getIdCurso()const
{
    return _idCurso;
}

std::string UnidadDidactica::getNombre()const
{
    return std::string(_nombre);
}

int UnidadDidactica::getOrden()const
{
    return _orden;
}

bool UnidadDidactica::getEliminado()const
{
    return _eliminado;
}

