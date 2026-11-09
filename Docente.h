#pragma once
#include "Persona.h"

class Docente:public Persona
{
public:
    Docente();
    Docente(const std::string &nombre,
            const std::string &apellido,
            const std::string &dni,
            int idDocente);

    void setIdDocente(int idDocente);
    void setEliminado(bool eliminado);

    int getIdDocente()const;
    bool getEliminado()const;

private:
    int _idDocente;
    bool _eliminado;
};
