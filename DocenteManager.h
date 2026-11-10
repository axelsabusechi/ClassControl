#pragma once
#include "Docente.h"
#include "DocenteArchivo.h"

class DocenteManager
{
public:
    DocenteManager();

    void registrarDocente();
    void modificarDocente();
    void eliminarDocente();
    void listarDocentes();
private:
    Docente crearDocente();
    void cargarDocente(std::string &nombre,
                      std::string &apellido,
                      std::string &dni);
    void mostrarDocente(const Docente &reg);
    void mostrarDocentesActivos();
    std::string pedirDniUnico(const std::string &mensaje, int idIgnorar = -1);
    bool menuModificarDocente(Docente &reg);
    void modificarNombre(Docente &reg);
    void modificarApellido(Docente &reg);
    void modificarDni(Docente &reg);
    void modificarTodos(Docente &reg);

    DocenteArchivo _docenteArchivo;

};
