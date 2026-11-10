#include <ctime>
#include "Fecha.h"

Fecha::Fecha()
    :_dia(0),
     _mes(0),
     _anio(0)
{
}

Fecha::Fecha(int d,
             int m,
             int a)
{
    setDia(d);
    setMes(m);
    setAnio(a);
}

void Fecha::setDia(int dia)
{
    _dia = dia;
}

void Fecha::setMes(int mes)
{
    _mes = mes;
}

void Fecha::setAnio(int anio)
{
    _anio = anio;
}

int Fecha::getDia()const
{
    return _dia;
}

int Fecha::getMes()const
{
    return _mes;
}

int Fecha::getAnio()const
{
    return _anio;
}

std::string Fecha::toString()const
{
    if(_dia == 0 && _mes == 0 && _anio == 0)
    {
        return "Sin fecha";
    }

    return std::to_string(_dia) + "/" +
           std::to_string(_mes) + "/" +
           std::to_string(_anio);
}

void Fecha::cargarFechaActual()
{
    time_t ahora = time(nullptr);

    tm *info = localtime(&ahora);

    _dia = info->tm_mday;
    _mes = info->tm_mon + 1;
    _anio = info->tm_year + 1900;
}



