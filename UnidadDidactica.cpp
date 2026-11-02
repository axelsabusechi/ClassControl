#include <cstring>
#include "UnidadDidactica.h"

UnidadDidactica::UnidadDidactica()
    :_idUnidad(0),
     _idCurso(0),
     _orden(0)
{
    strcpy(_nombre,"");
}

UnidadDidactica::UnidadDidactica(int idUnidad,
                                 int idCurso,
                                 std::string nombre,
                                 int orden)
{
    setIdUnidad(idUnidad);
    setIdCurso(idCurso);
    setNombre(nombre);
    setOrden(orden);
}

void UnidadDidactica::setIdUnidad(int idUnidad)
{
    _idUnidad=idUnidad;
}

void UnidadDidactica::setIdCurso(int idCurso)
{
    _idCurso=idCurso;
}

void UnidadDidactica::setNombre(std::string nombre)
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
    _orden=orden;
}

int UnidadDidactica::getIdUnidad()
{
    return _idUnidad;
}

int UnidadDidactica::getIdCurso()
{
    return _idCurso;
}

std::string UnidadDidactica::getNombre()
{
    return std::string(_nombre);
}

int UnidadDidactica::getOrden()
{
    return _orden;
}
