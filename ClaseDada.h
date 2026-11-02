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
              Fecha fecha,
              std::string observaciones,
              bool claseDada);

    void setIdClase(int idClase);
    void setIdCurso(int idCurso);
    void setIdTema(int idTema);
    void setFecha(Fecha fecha);
    void setObservaciones(std::string observaciones);
    void setClaseDada(bool claseDada);
    void setEliminado(bool eliminado);

    int getIdClase();
    int getIdCurso();
    int getIdTema();
    Fecha getFecha();
    std::string getObservaciones();
    bool getClaseDada();
    bool getEliminado();

private:
    int _idClase;
    int _idCurso;
    int _idTema;
    Fecha _fecha;
    char _observaciones[200];
    bool _claseDada;
    bool _eliminado;
};
