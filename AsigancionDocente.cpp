#include "AsignacionDocente.h"

AsignacionDocente::AsignacionDocente()
    :_idAsignacion(0),
     _idDocente(0),
     _idCurso(0),
     _fechaAlta(0,0,0),
     _fechaBaja(0,0,0),
     _activo(true),
     _eliminado(false)
{
}

AsignacionDocente::AsignacionDocente(int idAsignacion,
                                     int idDocente,
                                     int idCurso,
                                     const Fecha &fechaAlta,
                                     const Fecha &fechaBaja,
                                     bool activo)
{
    setIdAsignacion(idAsignacion);
    setIdDocente(idDocente);
    setIdCurso(idCurso);
    setFechaAlta(fechaAlta);
    setFechaBaja(fechaBaja);
    setActivo(activo);
    setEliminado(false);
}

void AsignacionDocente::setIdAsignacion(int idAsignacion)
{
    _idAsignacion = idAsignacion;
}

void AsignacionDocente::setIdDocente(int idDocente)
{
    _idDocente = idDocente;
}

void AsignacionDocente::setIdCurso(int idCurso)
{
    _idCurso = idCurso;
}

void AsignacionDocente::setFechaAlta(const Fecha &fechaAlta)
{
    _fechaAlta = fechaAlta;
}

void AsignacionDocente::setFechaBaja(const Fecha &fechaBaja)
{
    _fechaBaja = fechaBaja;
}

void AsignacionDocente::setActivo(bool activo)
{
    _activo = activo;
}

void AsignacionDocente::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int AsignacionDocente::getIdAsignacion()const
{
    return _idAsignacion;
}

int AsignacionDocente::getIdDocente()const
{
    return _idDocente;
}

int AsignacionDocente::getIdCurso()const
{
    return _idCurso;
}

Fecha AsignacionDocente::getFechaAlta()const
{
    return _fechaAlta;
}

Fecha AsignacionDocente::getFechaBaja()const
{
    return _fechaBaja;
}

bool AsignacionDocente::getActivo()const
{
    return _activo;
}

bool AsignacionDocente::getEliminado()const
{
    return _eliminado;
}
