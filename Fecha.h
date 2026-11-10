#pragma once
#include <string>

class Fecha
{

public:
    Fecha();
    Fecha(int dia,
          int mes,
          int anio);

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    int getDia()const;
    int getMes()const;
    int getAnio()const;

    void cargarFechaActual();
    std::string toString()const;

private:
    int _dia;
    int _mes;
    int _anio;
};
