#pragma once
#include <string>

class Persona
{
public:
    Persona();
    Persona(//int id,
            const std::string &nombre,
            const std::string &apellido,
            const std::string &dni);

    //void setID(int id);
    void setNombre(const std::string &nombre);
    void setApellido(const std::string &apellido);
    void setDni(const std::string &dni);
    //void setEliminado(bool eliminado);

    //int getID();
    std::string getNombre()const;
    std::string getApellido()const;
    std::string getDni()const;
    //bool getEliminado();

private:
    //int _id;
    char _nombre[50];
    char _apellido[50];
    char _dni[50];
    //bool _eliminado;
};
