#pragma once
#include <string>
#include "Persona.h"
#include "Fecha.h"

class Alumno:public Persona
{
public:
    Alumno();
    Alumno(//int id,
            const std::string &nombre,
            const std::string &apellido,
            const std::string &dni,
            int legajo,
            const Fecha &fechaNacimiento,
            const std::string &email,
            const std::string &adaptacion);

    void setLegajo(int legajo);
    void setFechaNacimiento(const Fecha &fechaNacimiento);
    void setEmail(const std::string &email);
    void setAdaptacion(const std::string &adaptacion);
    void setEliminado(bool eliminado);

    int getLegajo()const;
    Fecha getFechaNacimiento()const;
    std::string getEmail()const;
    std::string getAdaptacion()const;
    bool getEliminado()const;

private:
    int _legajo;
    Fecha _fechaNacimiento;
    char _email[50];
    char _adaptacion[50];
    bool _eliminado;
};
