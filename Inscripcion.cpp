#include "Inscripcion.h"

Inscripcion::Inscripcion()
    :_idInscripcion(0),
     _legajo(0),
     _idCurso(0),
     _fechaAlta(0,0,0),
     _fechaBaja(0,0,0),
     _activo(true),
     _eliminado(false)
{
}

Inscripcion::Inscripcion(int idInscripcion,
                         int legajo,
                         int idCurso,
                         const Fecha &fechaAlta,
                         const Fecha &fechaBaja,
                         bool activo)
{
    setIdInscripcion(idInscripcion);
    setLegajo(legajo);
    setIdCurso(idCurso);
    setFechaAlta(fechaAlta);
    setFechaBaja(fechaBaja);
    setActivo(activo);
    setEliminado(false);
}

void Inscripcion::setIdInscripcion(int idInscripcion)
{
    _idInscripcion = idInscripcion;
}

void Inscripcion::setLegajo(int legajo)
{
    _legajo = legajo;
}

void Inscripcion::setIdCurso(int idCurso)
{
    _idCurso = idCurso;
}

void Inscripcion::setFechaAlta(const Fecha &fechaAlta)
{
    _fechaAlta = fechaAlta;
}

void Inscripcion::setFechaBaja(const Fecha &fechaBaja)
{
    _fechaBaja = fechaBaja;
}

void Inscripcion::setActivo(bool activo)
{
    _activo = activo;
}

void Inscripcion::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int Inscripcion::getIdInscripcion()const
{
    return _idInscripcion;
}

int Inscripcion::getLegajo()const
{
    return _legajo;
}

int Inscripcion::getIdCurso()const
{
    return _idCurso;
}

Fecha Inscripcion::getFechaAlta()const
{
    return _fechaAlta;
}

Fecha Inscripcion::getFechaBaja()const
{
    return _fechaBaja;
}

bool Inscripcion::getActivo()const
{
    return _activo;
}

bool Inscripcion::getEliminado()const
{
    return _eliminado;
}
