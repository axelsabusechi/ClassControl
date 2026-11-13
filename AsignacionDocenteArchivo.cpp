#include "AsignacionDocenteArchivo.h"

AsignacionDocenteArchivo::AsignacionDocenteArchivo(const std::string &fileName)
    :_fileName(fileName)
{
}

ArchivoError AsignacionDocenteArchivo::guardar(const AsignacionDocente &reg)
{
    FILE *pFile;
    size_t escritura;
    const int CANT_REG=1;

    pFile = fopen(_fileName.c_str(),"ab");

    if (pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    escritura = fwrite(&reg, sizeof(AsignacionDocente), CANT_REG, pFile);
    fclose(pFile);

    if(escritura != CANT_REG)
    {
        _errorMessage = "No se pudo escribir en el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

ArchivoError AsignacionDocenteArchivo::guardar(int index, const AsignacionDocente &reg)
{
    FILE *PFile;
    size_t escritura;
    const int CANT_REGISTROS=1;

    PFile = fopen(_fileName.c_str(),"rb+");

    if(PFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    fseek(PFile, index*sizeof(AsignacionDocente), SEEK_SET);
    escritura = fwrite(&reg, sizeof(AsignacionDocente), CANT_REGISTROS,PFile);
    fclose(PFile);

    if(escritura != CANT_REGISTROS)
    {
        _errorMessage = "No se pudo actualizar el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

ArchivoError AsignacionDocenteArchivo::leerTodos(AsignacionDocente reg[], int cant)
{
    FILE *pFile;
    size_t lectura;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se epudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    lectura = fread(reg, sizeof(AsignacionDocente), cant, pFile);
    fclose(pFile);

    if(lectura != cant)
    {
        _errorMessage = "No se pudieron leer los registros";
        return ArchivoError::LEER;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

AsignacionDocente AsignacionDocenteArchivo::leer(int index)
{
    FILE *pFile;
    AsignacionDocente reg;
    size_t lectura;
    const int CANT_REG = 1;

    reg.setIdAsignacion(-1);
    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return reg;
    }

    fseek(pFile, index*sizeof(AsignacionDocente), SEEK_SET);
    lectura = fread(&reg, sizeof(AsignacionDocente), CANT_REG, pFile);
    fclose(pFile);

    if(lectura != CANT_REG)
    {
        _errorMessage = "No se pudo leer el registro...";
        return reg;
    }

    _errorMessage = "";
    return reg;
}

int AsignacionDocenteArchivo::getCantReg()
{
    FILE *pFile;
    int cant;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return 0;
    }

    fseek(pFile,0,SEEK_END);
    cant = ftell(pFile)/sizeof(AsignacionDocente);
    fclose(pFile);
    _errorMessage = "";

    return cant;
}

int AsignacionDocenteArchivo::getNewID()
{
    return getCantReg()+1;
}

int AsignacionDocenteArchivo::buscarByID(int id)
{
    FILE *pFile;
    AsignacionDocente reg;
    int index = 0;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return -1;
    }

    while(fread(&reg, sizeof(AsignacionDocente), 1, pFile))
    {
        if(reg.getIdAsignacion() == id)
        {
            fclose(pFile);
            return index;
        }
        index++;
    }

    fclose(pFile);
    _errorMessage = "";
    return -1;
}

bool AsignacionDocenteArchivo::existeAsignacion(int idDocente, int idCurso)
{
    FILE *pFile;
    AsignacionDocente reg;

    pFile = fopen(_fileName.c_str(), "rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return false;
    }


    while(fread(&reg, sizeof(AsignacionDocente), 1, pFile))
    {
        if(!reg.getEliminado() &&
                reg.getIdDocente() == idDocente &&
                reg.getIdCurso() == idCurso)
        {
            fclose(pFile);
            return true;
        }
    }

    fclose(pFile);
    _errorMessage = "";
    return false;
}

int AsignacionDocenteArchivo::getCantRegActivos()
{
    FILE *pFile;
    AsignacionDocente reg;
    int cantidad = 0;

    pFile = fopen(_fileName.c_str(), "rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return 0;
    }

    while(fread(&reg, sizeof(AsignacionDocente), 1, pFile))
    {
        if(!reg.getEliminado())
        {
            cantidad++;
        }
    }

    fclose(pFile);
    _errorMessage = "";
    return cantidad;
}

std::string AsignacionDocenteArchivo::getLastError()const
{
    return _errorMessage;
}


