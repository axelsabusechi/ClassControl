#pragma once
#include <string>

class Persona
{
public:
    Persona();
    Persona(//int id,
            std::string nombre,
            std::string apellido,
            std::string dni);

    //void setID(int id);
    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setDni(std::string dni);
    //void setEliminado(bool eliminado);

    //int getID();
    std::string getNombre();
    std::string getApellido();
    std::string getDni();
    //bool getEliminado();

private:
    //int _id;
    char _nombre[50];
    char _apellido[50];
    char _dni[50];
    //bool _eliminado;
};
