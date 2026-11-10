#pragma once
#include "Fecha.h"

class AsignacionDocente
{
public:
    AsignacionDocente();
    AsignacionDocente(int idAsignacion,
                      int idDocente,
                      int idCurso,
                      const Fecha &fechaAlta,
                      const Fecha &fechaBaja,
                      bool activo);

    void setIdAsignacion(int idAsignacion);
    void setIdDocente(int idDocente);
    void setIdCurso(int idICurso);
    void setFechaAlta(const Fecha &fechaAlta);
    void setFechaBaja(const Fecha &fechaBaja);
    void setActivo(bool activo);
    void setEliminado(bool eliminado);

    int getIdAsignacion()const;
    int getIdDocente()const;
    int getIdCurso()const;
    Fecha getFechaAlta()const;
    Fecha getFechaBaja()const;
    bool getActivo()const;
    bool getEliminado()const;

private:
    int _idAsignacion;
    int _idDocente;
    int _idCurso;
    Fecha _fechaAlta;
    Fecha _fechaBaja;
    bool _activo;
    bool _eliminado;
};
