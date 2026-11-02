#pragma once
#include <string>

class UnidadDidactica
{
public:
    UnidadDidactica();
    UnidadDidactica(int idUnidad,
                    int idCurso,
                    std::string nombre,
                    int orden);

    void setIdUnidad(int idUnidad);
    void setIdCurso(int idCurso);
    void setNombre(std::string nombre);
    void setOrden(int orden);

    int getIdUnidad();
    int getIdCurso();
    std::string getNombre();
    int getOrden();

private:
    int _idUnidad;
    int _idCurso;
    char _nombre[50];
    int _orden;
    bool _eliminado;
};
