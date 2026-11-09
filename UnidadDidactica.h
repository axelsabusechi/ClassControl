#pragma once
#include <string>

class UnidadDidactica
{
public:
    UnidadDidactica();
    UnidadDidactica(int idUnidad,
                    int idCurso,
                    const std::string &nombre,
                    int orden);

    void setIdUnidad(int idUnidad);
    void setIdCurso(int idCurso);
    void setNombre(const std::string &nombre);
    void setOrden(int orden);
    void setEliminado(bool eliminado);

    int getIdUnidad()const;
    int getIdCurso()const;
    std::string getNombre()const;
    int getOrden()const;
    bool getEliminado()const;

private:
    int _idUnidad;
    int _idCurso;
    char _nombre[50];
    int _orden;
    bool _eliminado;
};
