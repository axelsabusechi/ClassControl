#pragma once
#include "Fecha.h"

class Inscripcion
{
public:
    Inscripcion();
    Inscripcion(int idInscripcion,
                int legajo,
                int idCurso,
                const Fecha &fechaAlta,
                const Fecha &fechaBaja,
                bool activo);

    void setIdInscripcion(int idInscripcion);
    void setLegajo(int legajo);
    void setIdCurso(int idICurso);
    void setFechaAlta(const Fecha &fechaAlta);
    void setFechaBaja(const Fecha &fechaBaja);
    void setActivo(bool activo);
    void setEliminado(bool eliminado);

    int getIdInscripcion()const;
    int getlegajo()const;
    int getIdCurso()const;
    Fecha getFechaAlta()const;
    Fecha getFechaBaja()const;
    bool getActivo()const;
    bool getEliminado()const;

private:
    int _idInscripcion;
    int _legajo;
    int _idCurso;
    Fecha _fechaAlta;
    Fecha _fechaBaja;
    bool _activo;
    bool _eliminado;
};
