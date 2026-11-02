#pragma once
#include "Periodo.h"
#include "Fecha.h"

class Nota
{
public:
    Nota();
    Nota(int idNota,
         int legajo,
         Periodo periodo,
         Fecha fechaCarga);

    void setIdNota(int idNota);
    void setLegajo(int legajo);
    void setPeriodo(Periodo periodo);
    void setFechaCarga(Fecha fechaCarga);
    void setEliminado(bool eliminado);

    int getIdNota();
    int getLegajo();
    Periodo getPeriodo();
    Fecha getFechaCarga();
    bool getEliminado();

private:
    int _idNota;
    int _legajo;
    Periodo _periodo;
    Fecha _fechaCarga;
    bool _eliminado;
};
