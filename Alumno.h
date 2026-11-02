#pragma once
#include <string>
#include "Persona.h"
#include "Fecha.h"

class Alumno:public Persona
{
public:
    Alumno();
    Alumno(//int id,
            std::string nombre,
            std::string apellido,
            std::string dni,
            int legajo,
            Fecha fechaNacimiento,
            std::string email,
            std::string adaptacion);

    void setLegajo(int legajo);
    void setFechaNacimiento(Fecha fechaNacimiento);
    void setEmail(std::string email);
    void setAdaptacion(std::string adaptacion);
    void setEliminado(bool eliminado);

    int getLegajo();
    Fecha getFechaNacimiento();
    std::string getEmail();
    std::string getAdaptacion();
    bool getEliminado();

private:
    int _legajo;
    Fecha _fechaNacimiento;
    char _email[50];
    char _adaptacion[50];
    bool _eliminado;
};
