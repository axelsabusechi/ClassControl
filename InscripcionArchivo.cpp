#include "InscripcionArchivo.h"

InscripcionArchivo::InscripcionArchivo(const std::string &fileName)
    :_fileName(fileName)

{
}

ArchivoError InscripcionArchivo::guardar(const Inscripcion &reg)
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

    escritura = fwrite(&reg, sizeof(Inscripcion), CANT_REG, pFile);
    fclose(pFile);

    if(escritura != CANT_REG)
    {
        _errorMessage = "No se pudo escribir en el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

ArchivoError InscripcionArchivo::guardar(int index, const Inscripcion &reg)
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

    fseek(PFile, index*sizeof(  Inscripcion), SEEK_SET);
    escritura = fwrite(&reg, sizeof(Inscripcion), CANT_REGISTROS,PFile);
    fclose(PFile);

    if(escritura != CANT_REGISTROS)
    {
        _errorMessage = "No se pudo actualizar el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

ArchivoError InscripcionArchivo::leerTodos(Inscripcion reg[], int cant)
{
    FILE *pFile;
    size_t lectura;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se epudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    lectura = fread(reg, sizeof(Inscripcion), cant, pFile);
    fclose(pFile);

    if(lectura != cant)
    {
        _errorMessage = "No se pudieron leer los registros";
        return ArchivoError::LEER;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

Inscripcion InscripcionArchivo::leer(int index)
{
    FILE *pFile;
    Inscripcion reg;
    size_t lectura;
    const int CANT_REG = 1;

    reg.setIdInscripcion(-1);
    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return reg;
    }

    fseek(pFile, index*sizeof(Inscripcion), SEEK_SET);
    lectura = fread(&reg, sizeof(Inscripcion), CANT_REG, pFile);
    fclose(pFile);

    if(lectura != CANT_REG)
    {
        _errorMessage = "No se pudo leer el registro...";
        return reg;
    }

    _errorMessage = "";
    return reg;
}

int InscripcionArchivo::getCantReg()
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
    cant = ftell(pFile)/sizeof(Inscripcion);
    fclose(pFile);
    _errorMessage = "";

    return cant;
}
int InscripcionArchivo::getNewID()
{
    return getCantReg()+1;
}

int InscripcionArchivo::buscarByID(int id)
{
    FILE *pFile;
    Inscripcion reg;
    int index = 0;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return -1;
    }

    while(fread(&reg, sizeof(Inscripcion), 1, pFile))
    {
        if(reg.getIdInscripcion() == id)
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

bool InscripcionArchivo::existeInscripcion(int legajo, int idCurso)
{
    FILE *pFile;
    Inscripcion reg;

    pFile = fopen(_fileName.c_str(), "rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return false;
    }


    while(fread(&reg, sizeof(Inscripcion), 1, pFile))
    {
        if(!reg.getEliminado() &&
                reg.getLegajo() == legajo &&
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

int InscripcionArchivo::getCantRegActivos()
{
    FILE *pFile;
    Inscripcion reg;
    int cantidad = 0;

    pFile = fopen(_fileName.c_str(), "rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return 0;
    }

    while(fread(&reg, sizeof(Inscripcion), 1, pFile))
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

std::string InscripcionArchivo::getLastError()const
{
    return _errorMessage;
}
