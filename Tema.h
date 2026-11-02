#pragma once
#include <string>

class Tema
{
public:
    Tema();
    Tema(int idTema,
         int idUnidad,
         std::string nombre,
         int orden);

    void setIdTema(int idTema);
    void setIdUnidad(int idUnidad);
    void setNombre(std::string nombre);
    void setOrden(int orden);
    void setEliminado(bool eliminado);

    int getIdTema();
    int getIdUnidad();
    std::string getNombre();
    int getOrden();
    int getEliminado();

private:
    int _idTema;
    int _idUnidad;
    char _nombre[80];
    int _orden;
    bool _eliminado;
};
