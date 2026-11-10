#include "DocenteArchivo.h"

DocenteArchivo::DocenteArchivo(const std::string &fileName)
    :_fileName(fileName)
{
}

ArchivoError DocenteArchivo::guardar(const Docente &reg)
{
    FILE *pFile;
    size_t escritura;
    const int CANT_REG = 1;

    pFile = fopen(_fileName.c_str(),"ab");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    escritura = fwrite(&reg,sizeof(Docente),CANT_REG,pFile);
    fclose(pFile);

    if(escritura != CANT_REG)
    {
        _errorMessage = "No se pudo escribir en el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

ArchivoError DocenteArchivo::guardar(int index, const Docente &reg)
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

    fseek(PFile,index*sizeof(Docente),SEEK_SET);
    escritura = fwrite(&reg,sizeof(Docente),CANT_REGISTROS,PFile);
    fclose(PFile);

    if(escritura != CANT_REGISTROS)
    {
        _errorMessage = "No se pudo actualizar el registro...";
        return ArchivoError::ESCRIBIR;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

ArchivoError DocenteArchivo::leerTodos(Docente reg[], int cant)
{
    FILE *pFile;
    size_t lectura;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No s epudo abrir el archivo..." + _fileName;
        return ArchivoError::ABRIR;
    }

    lectura = fread(reg,sizeof(Docente),cant,pFile);
    fclose(pFile);

    if(lectura != cant)
    {
        _errorMessage = "No se pudieron leer los registros";
        return ArchivoError::LEER;
    }

    _errorMessage = "";
    return ArchivoError::OK;
}

Docente DocenteArchivo::leer(int index)
{
    FILE *pFile;
    Docente reg;
    size_t lectura;
    const int CANT_REG = 1;

    reg.setIdDocente(-1);
    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return reg;
    }

    fseek(pFile,index*sizeof(Docente),SEEK_SET);
    lectura = fread(&reg,sizeof(Docente),CANT_REG,pFile);
    fclose(pFile);

    if(lectura != CANT_REG)
    {
        _errorMessage = "No se pudo leer el registro...";
        return reg;
    }

    _errorMessage = "";
    return reg;
}

int DocenteArchivo::getCantReg()
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
    cant = ftell(pFile)/sizeof(Docente);
    fclose(pFile);
    return cant;
}

int DocenteArchivo::getNewID()
{
    return getCantReg()+1;
}

int DocenteArchivo::buscarByID(int id)
{
    FILE *pFile;
    Docente reg;
    int index = 0;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return -1;
    }

    while(fread(&reg,sizeof(Docente), 1,pFile))
    {
        if(reg.getIdDocente() == id)
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

bool DocenteArchivo::existeDocente(int id)
{
    return buscarByID(id) != -1;
}

bool DocenteArchivo::existeDni(const std::string &dni, int iDIgnorar)
{
    FILE *pFile;
    Docente reg;

    pFile = fopen(_fileName.c_str(),"rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return false;;
    }

    while(fread(&reg,sizeof(Docente),1,pFile))
    {
        if(!reg.getEliminado() &&
                reg.getDni() == dni &&
                reg.getIdDocente() != iDIgnorar)
        {
            fclose(pFile);
            return true;
        }
    }

    fclose(pFile);
    _errorMessage = "";
    return false;
}

int DocenteArchivo::getCantRegActivos()
{
    FILE *pFile;
    Docente reg;
    int cantidad = 0;

    pFile = fopen(_fileName.c_str(), "rb");

    if(pFile == nullptr)
    {
        _errorMessage = "No se pudo abrir el archivo..." + _fileName;
        return 0;
    }

    while(fread(&reg, sizeof(Docente), 1, pFile))
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

std::string DocenteArchivo::getLastError()const
{
    return _errorMessage;
}
