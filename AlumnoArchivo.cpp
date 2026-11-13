#include "AlumnoArchivo.h"

AlumnoArchivo::AlumnoArchivo(const std::string &fileName)
    :_fileName(fileName)
{
}

ArchivoError AlumnoArchivo::guardar(const Alumno &reg)
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

    escritura = fwrite(&reg,sizeof(Alumno),CANT_REG,pFile);
    fclose(pFile);

    if(escritura != CANT_REG)
    {
        _errorMessage = "No se pudo escribir en el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

ArchivoError AlumnoArchivo::guardar(int index, const Alumno &reg)
{
    FILE *PFile;
    size_t escritura;
    const int CANT_REGISTROS = 1;

    PFile = fopen(_fileName.c_str(),"rb+");

    if(PFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    fseek(PFile,index*sizeof(Alumno),SEEK_SET);
    escritura = fwrite(&reg,sizeof(Alumno),CANT_REGISTROS,PFile);
    fclose(PFile);

    if(escritura != CANT_REGISTROS)
    {
        _errorMessage = "No se pudo actualizar el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

ArchivoError AlumnoArchivo::leerTodos(Alumno reg[], int cant)
{
    FILE *pFile;
    size_t lectura;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    lectura = fread(reg,sizeof(Alumno),cant,pFile);
    fclose(pFile);

    if(lectura != cant)
    {
        _errorMessage = "No se pudieron leer los registros";
        return ArchivoError::LEER;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

Alumno AlumnoArchivo::leer(int index)
{
    FILE *pFile;
    Alumno reg;
    size_t lectura;
    const int CANT_REG=1;

    reg.setLegajo(-1);
    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return reg;
    }

    fseek(pFile,index*sizeof(Alumno),SEEK_SET);
    lectura = fread(&reg,sizeof(Alumno),CANT_REG,pFile);
    fclose(pFile);

    if(lectura != CANT_REG)
    {
        _errorMessage = "No se pudo leer el registro...";
        return reg;
    }
    _errorMessage = "";
    return reg;
}

int AlumnoArchivo::getCantReg()
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
    cant = ftell(pFile)/sizeof(Alumno);
    fclose(pFile);
    return cant;
}

int AlumnoArchivo::getNewLegajo()
{
    return getCantReg()+1;
}

int AlumnoArchivo::buscarByLegajo(int legajo)
{
    FILE *pFile;
    Alumno reg;
    int index = 0;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return -1;
    }

    while(fread(&reg,sizeof(Alumno), 1,pFile))
    {
        if(reg.getLegajo() == legajo)
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

bool AlumnoArchivo::existeAlumno(int legajo)
{
    return buscarByLegajo(legajo) != -1;
}

bool AlumnoArchivo::existeDni(const std::string &dni, int legajoIgnorar)
{
    FILE *pFile;
    Alumno reg;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return false;;
    }

    while(fread(&reg,sizeof(Alumno),1,pFile))
    {
        if(!reg.getEliminado() &&
                reg.getDni() == dni &&
                reg.getLegajo() != legajoIgnorar)
        {
            fclose(pFile);
            return true;
        }
    }

    fclose(pFile);
    _errorMessage = "";
    return false;
}

int AlumnoArchivo::getCantRegActivos()
{
    FILE *pFile;
    Alumno reg;
    int cantidad = 0;

    pFile = fopen(_fileName.c_str(), "rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return 0;
    }

    while(fread(&reg, sizeof(Alumno), 1, pFile))
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

std::string AlumnoArchivo::getLastError()const
{
    return _errorMessage;
}




