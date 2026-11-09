#include "Nota.h"

Nota::Nota()
    :_idNota(0),
     _legajo(0),
     _periodo(Periodo::NONE),
     _fechaCarga(0,0,0),
     _eliminado(false)
{
}

Nota::Nota(int idNota,
           int legajo,
           Periodo periodo,
           const Fecha &fechaCarga)
{
    setIdNota(idNota);
    setLegajo(legajo);
    setPeriodo(periodo);
    setFechaCarga(fechaCarga);
    setEliminado(false);
}

void Nota::setIdNota(int idNota)
{
    _idNota = idNota;
}

void Nota::setLegajo(int legajo)
{
    _legajo=legajo;
}

void Nota::setPeriodo(Periodo periodo)
{
    _periodo = periodo;
}

void Nota::setFechaCarga(const Fecha &fechaCarga)
{
    _fechaCarga = fechaCarga;
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

Fecha Nota::getFechaCarga()const
{
    return _fechaCarga;
}

bool Nota::getEliminado()const
{
    return _eliminado;
}
