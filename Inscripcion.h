#pragma once
#include "Fecha.h"

class Inscripcion
{
public:
    Inscripcion();
    Inscripcion(int idInscripcion,
                int legajo,
                int idCurso,
                Fecha fechaAlta,
                Fecha fechaBaja,
                bool activo);

    void setIdInscripcion(int idInscripcion);
    void setLegajo(int legajo);
    void setIdCurso(int idICurso);
    void setFechaAlta(Fecha fechaAlta);
    void setFechaBaja(Fecha fechaBaja);
    void setActivo(bool activo);
    void setEliminado(bool eliminado);

    int getIdInscripcion();
    int getlegajo();
    int getIdCurso();
    Fecha getFechaAlta();
    Fecha getFechaBaja();
    bool getActivo();
    bool getEliminado();

private:
    int _idInscripcion;
    int _legajo;
    int _idCurso;
    Fecha _fechaAlta;
    Fecha _fechaBaja;
    bool _activo;
    bool _eliminado;
};
