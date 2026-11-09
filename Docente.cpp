#include "Docente.h"

Docente::Docente()
    :Persona(),
     _idDocente(0),
     _eliminado(false)
{
}

Docente::Docente(const std::string &nombre,
                 const std::string &apellido,
                 const std::string &dni,
                 int idDocente)
    :Persona(nombre,
             apellido,
             dni)
{
    setIdDocente(idDocente);
    setEliminado(false);
}

void Docente::setIdDocente(int idDocente)
{
    _idDocente = idDocente;
}

void Docente::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int Docente::getIdDocente()const
{
    return _idDocente;
}

bool Docente::getEliminado()const
{
    return _eliminado;
}
