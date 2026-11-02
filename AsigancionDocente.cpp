#include "AsignacionDocente.h"

AsignacionDocente::AsignacionDocente()
    :_idAsignacion(0),
     _idDocente(0),
     _idCurso(0),
     _fechaAlta(0,0,0),
     _fechaBaja(0,0,0),
     _activo(true),
     _eliminado(true)
{
}

AsignacionDocente::AsignacionDocente(int idAsignacion,
                                     int idDocente,
                                     int idCurso,
                                     Fecha fechaAlta,
                                     Fecha fechaBaja,
                                     bool activo)
{
    setIdAsignacion(idAsignacion);
    setIdDocente(idDocente);
    setIdCurso(idCurso);
    setFechaAlta(fechaAlta);
    setFechaBaja(fechaBaja);
    setActivo(activo);
    setEliminado(true);
}

void AsignacionDocente::setIdAsignacion(int idAsignacion)
{
    _idAsignacion=idAsignacion;
}

void AsignacionDocente::setIdDocente(int idDocente)
{
    _idDocente=idDocente;
}

void AsignacionDocente::setIdCurso(int idCurso)
{
    _idCurso=idCurso;
}

void AsignacionDocente::setFechaAlta(Fecha fechaAlta)
{
    _fechaAlta=fechaAlta;

}

void AsignacionDocente::setFechaBaja(Fecha fechaBaja)
{
    _fechaBaja=fechaBaja;

}

void AsignacionDocente::setActivo(bool activo)
{
    _activo=activo;

}

void AsignacionDocente::setEliminado(bool eliminado)
{
    _eliminado=eliminado;

}

int AsignacionDocente::getIdAsignacion()
{
    return _idAsignacion;
}

int AsignacionDocente::getIdDocente()
{
    return _idDocente;

}

int AsignacionDocente::getIdCurso()
{
    return _idCurso;

}

Fecha AsignacionDocente::getFechaAlta()
{
    return _fechaAlta;

}

Fecha AsignacionDocente::getFechaBaja()
{
    return _fechaBaja;

}

bool AsignacionDocente::getActivo()
{
    return _activo;

}

bool AsignacionDocente::getEliminado()
{
    return _eliminado;

}
