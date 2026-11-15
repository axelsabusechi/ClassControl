#include "NotaArchivo.h"

NotaArchivo::NotaArchivo(const std::string &fileName)
    :_fileName(fileName)
{
}

ArchivoError NotaArchivo::guardar(const Nota &reg)
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

    escritura = fwrite(&reg, sizeof(Nota), CANT_REG, pFile);
    fclose(pFile);

    if(escritura != CANT_REG)
    {
        _errorMessage = "No se pudo escribir en el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";

    return ArchivoError::OK;
}

ArchivoError NotaArchivo::guardar(int index, const Nota &reg)
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

    fseek(PFile, index*sizeof(Nota), SEEK_SET);
    escritura = fwrite(&reg, sizeof(Nota), CANT_REGISTROS, PFile);
    fclose(PFile);

    if(escritura != CANT_REGISTROS)
    {
        _errorMessage = "No se pudo actualizar el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";

    return ArchivoError::OK;
}

ArchivoError NotaArchivo::leerTodos(Nota reg[], int cant)
{
    FILE *pFile;
    size_t lectura;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    lectura = fread(reg, sizeof(Nota), cant, pFile);
    fclose(pFile);

    if(lectura != cant)
    {
        _errorMessage = "No se pudieron leer los registros";
        return ArchivoError::LEER;
    }

    _errorMessage = "";

    return ArchivoError::OK;
}

Nota NotaArchivo::leer(int index)
{
    FILE *pFile;
    Nota reg;
    size_t lectura;
    const int CANT_REG = 1;

    reg.setIdNota(-1);
    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return reg;
    }

    fseek(pFile, index*sizeof(Nota), SEEK_SET);
    lectura = fread(&reg, sizeof(Nota), CANT_REG,pFile);
    fclose(pFile);

    if(lectura != CANT_REG)
    {
        _errorMessage = "No se pudo leer el registro...";
        return reg;
    }

    _errorMessage = "";

    return reg;
}

int NotaArchivo::getCantReg()
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
    cant = ftell(pFile)/sizeof(Nota);
    fclose(pFile);

    return cant;
}

int NotaArchivo::getNewId()
{
    return getCantReg()+1;
}

int NotaArchivo::buscarById(int id)
{
    FILE *pFile;
    Nota reg;
    int index = 0;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return -1;
    }

    while(fread(&reg, sizeof(Nota), 1, pFile))
    {
        if(reg.getIdNota() == id)
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

int NotaArchivo::getCantRegActivos()
{
    FILE *pFile;
    Nota reg;
    int cantidad = 0;

    pFile = fopen(_fileName.c_str(), "rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return 0;
    }

    while(fread(&reg, sizeof(Nota), 1, pFile))
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

std::string NotaArchivo::getLastError()
{
    return _errorMessage;
}
