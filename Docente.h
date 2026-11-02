#pragma once
#include "Persona.h"

class Docente:public Persona
{
public:
    Docente();
    Docente(std::string nombre,
            std::string apellido,
            std::string dni,
            int idDocente);

    void setIdDocente(int idDocente);
    void setEliminado(bool eliminado);

    int getIdDocente();
    bool getEliminado();

private:
    int _idDocente;
    bool _eliminado;

};
