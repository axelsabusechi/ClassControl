#include "Docente.h"

Docente::Docente()
    :Persona(),
     _idDocente(0),
     _eliminado(true)
{
}

Docente::Docente(std::string nombre,
                 std::string apellido,
                 std::string dni,
                 int idDocente)
    :Persona(nombre,apellido,dni)
{
    setIdDocente(idDocente);
    setEliminado(true);
}

void Docente::setIdDocente(int idDocente)
{
    _idDocente=idDocente;
}

void Docente::setEliminado(bool eliminado)
{
    _eliminado=eliminado;
}

int Docente::getIdDocente()
{
    return _idDocente;
}

bool Docente::getEliminado()
{
    return _eliminado;
}
