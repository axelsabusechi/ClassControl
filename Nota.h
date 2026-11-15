#pragma once
#include <string>
#include "Periodo.h"
#include "Fecha.h"

class Nota
{
public:
    Nota();
    Nota(int idNota,
         int legajo,
         Periodo periodo,
         int nota,
         const Fecha &fechaCarga,
         const std::string &descripcion);

    void setIdNota(int idNota);
    void setLegajo(int legajo);
    void setPeriodo(Periodo periodo);
    void setNota(int nota);
    void setFechaCarga(const Fecha &fechaCarga);
    void setDescripcion(const std::string &descripcion);
    void setEliminado(bool eliminado);

    int getIdNota()const;
    int getLegajo()const;
    Periodo getPeriodo()const;
    int getNota()const;
    Fecha getFechaCarga()const;
    std::string getDescripcion()const;
    bool getEliminado()const;

private:
    int _idNota;
    int _legajo;
    Periodo _periodo;
    int _nota;
    Fecha _fechaCarga;
    char _descripcion[50];
    bool _eliminado;
};
