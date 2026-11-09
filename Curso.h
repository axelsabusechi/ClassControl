#pragma once
#include "Grado.h"
#include "Division.h"

class Curso
{
public:
    Curso();
    Curso(int idCurso,
          Grado grado,
          Division div);

    void setIdCurso(int idCurso);
    void setGrado(Grado grado);
    void setDivision(Division division);
    void setEliminado(bool eliminado);

    int getIdCurso()const;
    Grado getGrado()const;
    Division getDivision()const;
    bool getEliminado()const;

private:
    int _idCurso;
    Grado _grado;
    Division _div;
    bool _eliminado;
};
