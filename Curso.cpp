#include "Curso.h"

Curso::Curso()
    :_idCurso(0),
     _grado(Grado::NONE),
     _div(Division::NONE),
     _eliminado(false)
{
}

Curso::Curso(int id,
             Grado grado,
             Division div)
{
    setIdCurso(id);
    setGrado(grado);
    setDivision(div);
    setEliminado(false);
}

void Curso::setIdCurso(int idCurso)
{
    _idCurso = idCurso;
}

void Curso::setGrado(Grado grado)
{
    _grado = grado;
}

void Curso::setDivision(Division div)
{
    _div = div;
}

void Curso::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int Curso::getIdCurso()const
{
    return _idCurso;
}

Grado Curso::getGrado()const
{
    return _grado;
}

Division Curso::getDivision()const
{
    return _div;
}

bool Curso::getEliminado()const
{
    return _eliminado;
}
