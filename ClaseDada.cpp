#include <cstring>
#include "ClaseDada.h"

ClaseDada::ClaseDada()
    :_idClase(0),
     _idCurso(0),
     _idTema(0),
     _fecha(0,0,0),
     _claseDada(true),
     _eliminado(false)
{
    strcpy(_observaciones,"");
}

ClaseDada::ClaseDada(int idClase,
                     int idCurso,
                     int idTema,
                     const Fecha &fecha,
                     const std::string &observaciones,
                     bool claseDada)
{
    setIdClase(idClase);
    setIdCurso(idCurso);
    setIdTema(idTema);
    setFecha(fecha);
    setObservaciones(observaciones);
    setClaseDada(claseDada);
    setEliminado(false);
}

void ClaseDada::setIdClase(int idClase)
{
    _idClase = idClase;
}

void ClaseDada::setIdCurso(int idCurso)
{
    _idCurso = idCurso;
}

void ClaseDada::setIdTema(int idTema)
{
    _idTema = idTema;
}

void ClaseDada::setFecha(const Fecha &fecha)
{
    _fecha = fecha;
}

void ClaseDada::setObservaciones(const std::string &observaciones)
{
    if(observaciones.size() <= 199)
    {
        strcpy(_observaciones, observaciones.c_str());
    }
    else
    {
        strcpy(_observaciones, observaciones.substr(0, 199).c_str());
    }
}

void ClaseDada::setClaseDada(bool claseDada)
{
    _claseDada = claseDada;
}

void ClaseDada::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int ClaseDada::getIdClase()const
{
    return _idClase;
}

int ClaseDada::getIdCurso()const
{
    return _idCurso;
}

int ClaseDada::getIdTema()const
{
    return _idTema;
}

Fecha ClaseDada::getFecha()const
{
    return _fecha;
}

std::string ClaseDada::getObservaciones()const
{
    return std::string(_observaciones);
}

bool ClaseDada::getClaseDada()const
{
    return _claseDada;
}

bool ClaseDada::getEliminado()const
{
    return _eliminado;
}
