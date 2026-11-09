#pragma once
#include <string>
#include "Fecha.h"

class ClaseDada
{
public:
    ClaseDada();
    ClaseDada(int idClase,
              int idCurso,
              int idTema,
              const Fecha &fecha,
              const std::string &observaciones,
              bool claseDada);

    void setIdClase(int idClase);
    void setIdCurso(int idCurso);
    void setIdTema(int idTema);
    void setFecha(const Fecha &fecha);
    void setObservaciones(const std::string &observaciones);
    void setClaseDada(bool claseDada);
    void setEliminado(bool eliminado);

    int getIdClase()const;
    int getIdCurso()const;
    int getIdTema()const;
    Fecha getFecha()const;
    std::string getObservaciones()const;
    bool getClaseDada()const;
    bool getEliminado()const;

private:
    int _idClase;
    int _idCurso;
    int _idTema;
    Fecha _fecha;
    char _observaciones[200];
    bool _claseDada;
    bool _eliminado;
};
