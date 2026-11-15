#include <cstring>
#include "Nota.h"

Nota::Nota()
    :_idNota(0),
     _legajo(0),
     _periodo(Periodo::NONE),
     _nota(0),
     _fechaCarga(0,0,0),
     _eliminado(false)
{
    strcpy(_descripcion,"");
}

Nota::Nota(int idNota,
           int legajo,
           Periodo periodo,
           int nota,
           const Fecha &fechaCarga,
           const std::string &descripcion)
{
    setIdNota(idNota);
    setLegajo(legajo);
    setPeriodo(periodo);
    setNota(nota);
    setFechaCarga(fechaCarga);
    setDescripcion(descripcion);
    setEliminado(false);
}

void Nota::setIdNota(int idNota)
{
    _idNota = idNota;
}

void Nota::setLegajo(int legajo)
{
    _legajo = legajo;
}

void Nota::setPeriodo(Periodo periodo)
{
    _periodo = periodo;
}

void Nota::setNota(int nota)
{
    _nota = nota;
}

void Nota::setFechaCarga(const Fecha &fechaCarga)
{
    _fechaCarga = fechaCarga;
}

void Nota::setDescripcion(const std::string &descripcion)
{
    if(descripcion.size() <= 49)
    {
        strcpy(_descripcion, descripcion.c_str());
    }
    else
    {
        strcpy(_descripcion, descripcion.substr(0, 49).c_str());
    }
}

void Nota::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int Nota::getIdNota()const
{
    return _idNota;
}

int Nota::getLegajo()const
{
    return _legajo;
}

Periodo Nota::getPeriodo()const
{
    return _periodo;
}

int Nota::getNota()const
{
    return _nota;
}

std::string Nota::getDescripcion()const
{
    return std::string(_descripcion);
}

Fecha Nota::getFechaCarga()const
{
    return _fechaCarga;
}

bool Nota::getEliminado()const
{
    return _eliminado;
}
