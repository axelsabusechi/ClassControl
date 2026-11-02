#include <cstring>
#include "ClaseDada.h"

ClaseDada::ClaseDada()
    :_idClase(0),
     _idCurso(0),
     _idTema(0),
     _fecha(0,0,0),
     _claseDada(true),
     _eliminado(true)
{
    strcpy(_observaciones,"");
}

ClaseDada::ClaseDada(int idClase,
                     int idCurso,
                     int idTema,
                     Fecha fecha,
                     std::string observaciones,
                     bool claseDada)
{
    setIdClase(idClase);
    setIdCurso(idCurso);
    setIdTema(idTema);
    setFecha(fecha);
    setObservaciones(observaciones);
    setClaseDada(claseDada);
    setEliminado(true);
}

void ClaseDada::setIdClase(int idClase)
{
    _idClase=idClase;
}

void ClaseDada::setIdCurso(int idCurso)
{
    _idCurso=idCurso;
}

void ClaseDada::setIdTema(int idTema)
{
    _idTema=idTema;
}

void ClaseDada::setFecha(Fecha fecha)
{
    _fecha=fecha;
}

void ClaseDada::setObservaciones(std::string observaciones)
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
    _claseDada=claseDada;
}

void ClaseDada::setEliminado(bool eliminado)
{
    _eliminado=eliminado;
}

int ClaseDada::getIdClase()
{
    return _idClase;
}

int ClaseDada::getIdCurso()
{
    return _idCurso;
}

int ClaseDada::getIdTema()
{
    return _idTema;
}

Fecha ClaseDada::getFecha()
{
    return _fecha;
}

std::string ClaseDada::getObservaciones()
{
    return std::string(_observaciones);
}

bool ClaseDada::getClaseDada()
{
    return _claseDada;
}

bool ClaseDada::getEliminado()
{
    return _eliminado;
}
