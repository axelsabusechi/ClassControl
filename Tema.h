#pragma once
#include <string>

class Tema
{
public:
    Tema();
    Tema(int idTema,
         int idUnidad,
         const std::string &nombre,
         int orden);

    void setIdTema(int idTema);
    void setIdUnidad(int idUnidad);
    void setNombre(const std::string &nombre);
    void setOrden(int orden);
    void setEliminado(bool eliminado);

    int getIdTema()const;
    int getIdUnidad()const;
    std::string getNombre()const;
    int getOrden()const;
    int getEliminado()const;

private:
    int _idTema;
    int _idUnidad;
    char _nombre[80];
    int _orden;
    bool _eliminado;
};
