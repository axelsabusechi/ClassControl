#include "Inscripcion.h"

Inscripcion::Inscripcion()
    :_idInscripcion(0),
     _legajo(0),
     _idCurso(0),
     _fechaAlta(0,0,0),
     _fechaBaja(0,0,0),
     _activo(true),
     _eliminado(true)
{
}

Inscripcion::Inscripcion(int idInscripcion,
                         int legajo,
                         int idCurso,
                         Fecha fechaAlta,
                         Fecha fechaBaja,
                         bool activo)
{
    setIdInscripcion(idInscripcion);
    setLegajo(legajo);
    setIdCurso(idCurso);
    setFechaAlta(fechaAlta);
    setFechaBaja(fechaBaja);
    setActivo(activo);
    setEliminado(true);
}

void Inscripcion::setIdInscripcion(int idInscripcion)
{
    _idInscripcion=idInscripcion;
}

void Inscripcion::setLegajo(int legajo)
{
    _legajo=legajo;
}

void Inscripcion::setIdCurso(int idCurso)
{
    _idCurso=idCurso;
}

void Inscripcion::setFechaAlta(Fecha fechaAlta)
{
    _fechaAlta=fechaAlta;
}

void Inscripcion::setFechaBaja(Fecha fechaBaja)
{
    _fechaBaja=fechaBaja;
}

void Inscripcion::setActivo(bool activo)
{
    _activo=activo;
}

void Inscripcion::setEliminado(bool eliminado)
{
    _eliminado=eliminado;
}

int Inscripcion::getIdInscripcion()
{
    return _idInscripcion;
}

int Inscripcion::getlegajo()
{
    return _legajo;
}

int Inscripcion::getIdCurso()
{
    return _idCurso;
}

Fecha Inscripcion::getFechaAlta()
{
    return _fechaAlta;
}

Fecha Inscripcion::getFechaBaja()
{
    return _fechaBaja;
}

bool Inscripcion::getActivo()
{
    return _activo;
}

bool Inscripcion::getEliminado()
{
    return _eliminado;
}
