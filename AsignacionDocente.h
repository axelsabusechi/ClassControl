#pragma once
#include "Fecha.h"

class AsignacionDocente
{
public:
    AsignacionDocente();
    AsignacionDocente(int idAsignacion,
                int idDocente,
                int idCurso,
                Fecha fechaAlta,
                Fecha fechaBaja,
                bool activo);

    void setIdAsignacion(int idAsignacion);
    void setIdDocente(int idDocente);
    void setIdCurso(int idICurso);
    void setFechaAlta(Fecha fechaAlta);
    void setFechaBaja(Fecha fechaBaja);
    void setActivo(bool activo);
    void setEliminado(bool eliminado);

    int getIdAsignacion();
    int getIdDocente();
    int getIdCurso();
    Fecha getFechaAlta();
    Fecha getFechaBaja();
    bool getActivo();
    bool getEliminado();

private:
    int _idAsignacion;
    int _idDocente;
    int _idCurso;
    Fecha _fechaAlta;
    Fecha _fechaBaja;
    bool _activo;
    bool _eliminado;
};
