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
         const Fecha &fechaCarga);

    void setIdNota(int idNota);
    void setLegajo(int legajo);
    void setPeriodo(Periodo periodo);
    void setFechaCarga(const Fecha &fechaCarga);
    void setEliminado(bool eliminado);

    int getIdNota()const;
    int getLegajo()const;
    Periodo getPeriodo()const;
    Fecha getFechaCarga()const;
    bool getEliminado()const;

private:
    int _idNota;
    int _legajo;
    Periodo _periodo;
    Fecha _fechaCarga;
    bool _eliminado;
};
