#include "Nota.h"

Nota::Nota()
    :_idNota(0),
     _legajo(0),
     _periodo(Periodo::NONE),
     _fechaCarga(0,0,0),
     _eliminado(true)
{
}

Nota::Nota(int idNota,
           int legajo,
           Periodo periodo,
           Fecha fechaCarga)
{
    setIdNota(idNota);
    setLegajo(legajo);
    setPeriodo(periodo);
    setFechaCarga(fechaCarga);
}

void Nota::setIdNota(int idNota)
{
    _idNota=idNota;
}

void Nota::setLegajo(int legajo)
{
    _legajo=legajo;
}

void Nota::setPeriodo(Periodo periodo)
{
    _periodo=periodo;
}

void Nota::setFechaCarga(Fecha fechaCarga)
{
    _fechaCarga=fechaCarga;
}

void Nota::setEliminado(bool eliminado)
{
    _eliminado=eliminado;
}

int Nota::getIdNota()
{
    return _idNota;
}

int Nota::getLegajo()
{
    return _legajo;
}

Periodo Nota::getPeriodo()
{
    return _periodo;
}

Fecha Nota::getFechaCarga()
{
    return _fechaCarga;
}

bool Nota::getEliminado()
{
    return _eliminado;
}
