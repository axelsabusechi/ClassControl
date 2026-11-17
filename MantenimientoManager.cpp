#include <iostream>
#include "MantenimientoManager.h"

void MantenimientoManager::backupAlumnos()
{
    mostrarResultadoIndividual(copiarArchivo("Alumnos.dat", "Alumnos.bkp"),
                               "Alumnos", "Back Up");
    system("pause");
}

void MantenimientoManager::restoreAlumnos()
{
    mostrarResultadoIndividual(copiarArchivo("Alumnos.bkp", "Alumnos.dat"),
                               "Alumnos", "Restore");
    system("pause");
}

void MantenimientoManager::backupDocentes()
{
    mostrarResultadoIndividual(copiarArchivo("Docentes.dat", "Docentes.bkp"),
                               "Docentes", "Back up");
    system("pause");
}

void MantenimientoManager::restoreDocentes()
{
    mostrarResultadoIndividual(copiarArchivo("Docentes.bkp", "Docentes.dat"),
                               "Docentes", "Restore");
    system("pause");
}

void MantenimientoManager::backupCursos()
{
    mostrarResultadoIndividual(copiarArchivo("Cursos.dat", "Cursos.bkp"),
                               "Cursos", "Back up");
    system("pause");
}

void MantenimientoManager::restoreCursos()
{
    mostrarResultadoIndividual(copiarArchivo("Cursos.bkp", "Cursos.dat"),
                               "Cursos", "Restore");
    system("pause");
}

void MantenimientoManager::backupInscripciones()
{
    mostrarResultadoIndividual(copiarArchivo("Inscripciones.dat", "Inscripciones.bkp"),
                               "Inscripciones", "Back up");
    system("pause");
}

void MantenimientoManager::restoreInscripciones()
{
    mostrarResultadoIndividual(copiarArchivo("Inscripciones.bkp", "Inscripciones.dat"),
                               "Inscripciones", "Restore");
    system("pause");
}

void MantenimientoManager::backupAsignaciones()
{
    mostrarResultadoIndividual(copiarArchivo("AsignacionesDocentes.dat", "AsignacionesDocentes.bkp"),
                               "Asignaciones Docentes", "Back up");
    system("pause");
}

void MantenimientoManager::restoreAsignaciones()
{
    mostrarResultadoIndividual(copiarArchivo("AsignacionesDocentes.bkp", "AsignacionesDocentes.dat"),
                               "Asignaciones Docentes", "Restore");
    system("pause");
}

void MantenimientoManager::backupClasesDadas()
{
    mostrarResultadoIndividual(copiarArchivo("ClasesDadas.dat", "ClasesDadas.bkp"),
                               "Clases Dadas", "Back up");
    system("pause");
}

void MantenimientoManager::restoreClasesDadas()
{
    mostrarResultadoIndividual(copiarArchivo("ClasesDadas.bkp", "ClasesDadas.dat"),
                               "Clases Dadas", "Restore");
    system("pause");
}

void MantenimientoManager::backupUnidadesDidacticas()
{
    mostrarResultadoIndividual(copiarArchivo("UnidadesDidacticas.dat", "UnidadesDidacticas.bkp"),
                               "Unidades Didacticas", "Back up");
    system("pause");
}

void MantenimientoManager::restoreUnidadesDidacticas()
{
    mostrarResultadoIndividual(copiarArchivo("UnidadesDidacticas.bkp", "UnidadesDidacticas.dat"),
                               "Unidades Didacticas", "Restore");
    system("pause");
}

void MantenimientoManager::backupTemas()
{
    mostrarResultadoIndividual(copiarArchivo("Temas.dat", "Temas.bkp"),
                               "Temas", "Back up");
    system("pause");
}

void MantenimientoManager::restoreTemas()
{
    mostrarResultadoIndividual(copiarArchivo("Temas.bkp", "Temas.dat"),
                               "Temas", "Restore");
    system("pause");
}

void MantenimientoManager::backupNotas()
{
    mostrarResultadoIndividual(copiarArchivo("Notas.dat", "Notas.bkp"),
                               "Notas", "Back up");
    system("pause");
}

void MantenimientoManager::restoreNotas()
{
    mostrarResultadoIndividual(copiarArchivo("Notas.bkp", "Notas.dat"),
                               "Notas", "Restore");
    system("pause");
}

void MantenimientoManager::backupGeneral()
{
    int errores = 0;

    if(!copiarArchivo("Alumnos.dat", "Alumnos.bkp"))
    {
        errores++;
    }
    if(!copiarArchivo("Docentes.dat", "Docentes.bkp"))
    {
        errores++;
    }
    if(!copiarArchivo("Cursos.dat", "Cursos.bkp"))
    {
        errores++;

    }
    if(!copiarArchivo("Inscripciones.dat", "Inscripciones.bkp"))
    {
        errores++;
    }
    if(!copiarArchivo("AsignacionesDocentes.dat", "AsignacionesDocentes.bkp"))
    {
        errores++;
    }
    if(!copiarArchivo("ClasesDadas.dat", "ClasesDadas.bkp"))
    {
        errores++;
    }
    if(!copiarArchivo("UnidadesDidacticas.dat", "UnidadesDidacticas.bkp"))
    {
        errores++;
    }
    if(!copiarArchivo("Temas.dat", "Temas.bkp"))
    {
        errores++;
    }
    if(!copiarArchivo("Notas.dat", "Notas.bkp"))
    {
        errores++;
    }

    mostrarResultadoGeneral("Backup general", errores);
    system("pause");
}

void MantenimientoManager::restoreGeneral()
{
    int errores = 0;

    if(!copiarArchivo("Alumnos.bkp", "Alumnos.dat"))
    {
        errores++;
    }
    if(!copiarArchivo("Docentes.bkp", "Docentes.dat"))
    {
        errores++;
    }
    if(!copiarArchivo("Cursos.bkp", "Cursos.dat"))
    {
        errores++;
    }
    if(!copiarArchivo("Inscripciones.bkp", "Inscripciones.dat"))
    {
        errores++;
    }
    if(!copiarArchivo("AsignacionesDocentes.bkp", "AsignacionesDocentes.dat"))
    {
        errores++;
    }
    if(!copiarArchivo("ClasesDadas.bkp", "ClasesDadas.dat"))
    {
        errores++;
    }
    if(!copiarArchivo("UnidadesDidacticas.bkp", "UnidadesDidacticas.dat"))
    {
        errores++;
    }
    if(!copiarArchivo("Temas.bkp", "Temas.dat"))
    {
        errores++;
    }
    if(!copiarArchivo("Notas.bkp", "Notas.dat"))
    {
        errores++;
    }

    mostrarResultadoGeneral("Restore general", errores);
    system("pause");
}

bool MantenimientoManager::copiarArchivo(const std::string &origen, const std::string &destino)
{
    FILE *pOrigen;
    FILE *pDestino;

    char buffer;

    pOrigen = fopen(origen.c_str(), "rb");

    if(pOrigen == nullptr)
    {
        return false;
    }

    pDestino = fopen(destino.c_str(), "wb");

    if(pDestino == nullptr)
    {
        fclose(pOrigen);
        return false;
    }

    while(fread(&buffer, sizeof(char), 1, pOrigen))
    {
        fwrite(&buffer, sizeof(char), 1, pDestino);
    }

    fclose(pOrigen);
    fclose(pDestino);

    return true;
}

void MantenimientoManager::mostrarResultadoIndividual(bool resultado,
        const std::string &entidad,
        const std::string &operacion)
{
    if(resultado)
    {
        std::cout << operacion
                  << " de "
                  << entidad
                  << " realizado correctamente..."
                  << std::endl;
    }
    else
    {
        std::cout << "No se pudo realizar "
                  << operacion
                  << " de "
                  << entidad
                  << "..."
                  << std::endl;
    }
}

void MantenimientoManager::mostrarResultadoGeneral(const std::string &operacion, int errores)
{
    if(errores == 0)
    {
        std::cout << operacion
                  << " realizado correctamente..."
                  << std::endl;
    }
    else
    {
        std::cout << operacion
                  << " finalizado con "
                  << errores
                  << " error/es..."
                  << std::endl;
    }
}

