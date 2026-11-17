#pragma once
#include <string>

class MantenimientoManager
{
public:
    void backupAlumnos();
    void restoreAlumnos();

    void backupDocentes();
    void restoreDocentes();

    void backupCursos();
    void restoreCursos();

    void backupInscripciones();
    void restoreInscripciones();

    void backupAsignaciones();
    void restoreAsignaciones();

    void backupClasesDadas();
    void restoreClasesDadas();

    void backupUnidadesDidacticas();
    void restoreUnidadesDidacticas();

    void backupTemas();
    void restoreTemas();

    void backupNotas();
    void restoreNotas();

    void backupGeneral();
    void restoreGeneral();

private:
    bool copiarArchivo(const std::string &origen,
                       const std::string &destino);

    void mostrarResultadoIndividual(bool resultado,
                                   const std::string &entidad,
                                   const std::string &operacion);

    void mostrarResultadoGeneral(const std::string &operacion,
                                 int errores);
};
