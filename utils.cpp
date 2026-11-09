#include <iostream>
#include <cctype>
#include "rlutil.h"
#include "utils.h"
#include "CursoArchivo.h"

Grado intToGrado(int grado)
{
    switch(grado)
    {
    case 1:
        return Grado::PRIMERO;
    case 2:
        return Grado::SEGUNDO;
    case 3:
        return Grado::TERCERO;
    case 4:
        return Grado::CUARTO;
    case 5:
        return Grado::QUINTO;
    case 6:
        return Grado::SEXTO;
    default:
        return Grado::NONE;
    }
}

Division intToDivision(int div)
{
    switch(div)
    {
    case 1:
        return Division::A;
    case 2:
        return Division::B;
    case 3:
        return Division::C;
    default:
        return Division::NONE;
    }
}

std::string gradoToString(Grado grado)
{
    switch(grado)
    {
    case Grado::PRIMERO:
        return "Primero";
    case Grado::SEGUNDO:
        return "Segundo";
    case Grado::TERCERO:
        return "Tercero";
    case Grado::CUARTO:
        return "Cuarto";
    case Grado::QUINTO:
        return "Quinto";
    case Grado::SEXTO:
        return "Sexto";
    default:
        return "Desconocido";
    }
}

std::string divisionToString(Division div)
{
    switch(div)
    {
    case Division::A:
        return "A";
    case Division::B:
        return "B";
    case Division::C:
        return "C";
    default:
        return "Desconocido";
    }
}

void showItem(const std::string &text, int posx, int posy, bool selected)
{
    if(selected)
    {
        setBackgroundColor(rlutil::BLUE);
        //locate(posx -4, posy);
        //cout << " " << text << " " << endl;
    }
    else
    {
        setBackgroundColor(rlutil::BLACK);
        //locate(posx -4, posy);
        //cout << " " << text << " " << endl;
    }

    rlutil::locate(posx, posy);
    std::cout << text << std::endl;
    setBackgroundColor(rlutil::BLACK);
}

std::string cargarCadena()
{
    std::string texto;

    if(std::cin.peek() == '\n')
    {
        std::cin.ignore();
    }
    std::getline(std::cin, texto);
    return texto;
}

bool nombreApellidoValido(const std::string &nombreApellido)
{
    if(nombreApellido.empty())
    {
        return false;
    }

    bool contieneLetras=false;

    for(char c : nombreApellido)
    {
        if(std::isalpha(c))
        {
            contieneLetras = true;
        }
        else if(c != ' ')
        {
            return false;
        }
    }

    return contieneLetras;
}

bool dniValido(const std::string &dni)
{
    if(dni.length() < 7 || dni.length() > 8)
    {
        return false;
    }

    for(char d : dni)
    {
        if(!std::isdigit(d))
        {
            return false;
        }
    }

    return true;
}

bool anioBisiesto(int anio)
{
    return ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0));
}

bool fechaValida(int dia, int mes, int anio)
{
    if(anio < 1900 || anio > 2100)
    {
        return false;
    }

    if(mes < 1 || mes > 12)
    {
        return false;
    }

    int diasMes;

    switch(mes)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        diasMes = 30;
        break;

    case 2:
        if(anioBisiesto(anio))
        {
            diasMes = 29;
        }
        else
        {
            diasMes = 28;
        }
        break;

    default:
        diasMes = 31;
    }

    return dia >= 1 && dia <= diasMes;
}

bool emailValido(const std::string &email)
{
    if(email.empty())
    {
        return false;
    }

    size_t posicionArroba = email.find('@');

    if(posicionArroba == std::string::npos)
    {
        return false;
    }

    size_t posicionPunto = email.find('.', posicionArroba);

    if(posicionPunto == std::string::npos)
    {
        return false;
    }

    return true;
}

bool textoVacio(const std::string &texto)
{
    for(char c : texto)
    {
        if(c != ' ')
        {
            return true;
        }
    }

    return false;
}

int pedirEntero(const std::string &mensaje)
{
    int valor;
    bool valido;

    do
    {
        std::cout << mensaje;
        std::cin >> valor;

        valido = !std::cin.fail();

        if(!valido)
        {
            std::cout << "ERROR. Ingrese un numero valido." << std::endl;
            std::cin.clear();
        }

        std::cin.ignore(10000,'\n');
    }
    while(!valido);

    return valor;
}

std::string pedirNombreApellido(const std::string &mensaje)
{
    std::string nombreApellido;
    bool valido = false;

    do
    {
        std::cout << mensaje;
        nombreApellido = cargarCadena();

        valido = nombreApellidoValido(nombreApellido);

        if(!valido)
        {
            std::cout << "ERROR. Ingrese solo letras y espacios." << std::endl;
        }

    }
    while(!valido);

    return nombreApellido;
}

std::string pedirDni(const std::string &mensaje)
{
    std::string dni;
    bool valido = false;

    do
    {
        std::cout << mensaje;
        dni = cargarCadena();

        valido = dniValido(dni);

        if(!valido)
        {
            std::cout << "ERROR: DNI invalido..." << std::endl;
        }
    }
    while(!valido);

    return dni;
}

std::string pedirEmail(const std::string &mensaje)
{
    std::string email;
    bool valido = false;

    do
    {
        std::cout << mensaje;
        email = cargarCadena();

        valido = emailValido(email);

        if(!valido)
        {
            std::cout << "ERROR: Email invalido..." << std::endl;
        }
    }
    while(!valido);

    return email;
}

std::string pedirAdaptacion(const std::string &mensaje)
{
    std::string adaptacion;
    bool valido = false;

    do
    {
        std::cout << mensaje;
        adaptacion = cargarCadena();

        valido = textoVacio(adaptacion);

        if(!valido)
        {
            std::cout << "ERROR: Adaptacion invalida..." << std::endl;
        }
    }
    while(!valido);

    return adaptacion;
}

Fecha pedirFecha(const std::string &mensaje)
{
    int dia,mes,anio;
    bool valido = false;

    do
    {
        std::cout << mensaje << std::endl;

        dia = pedirEntero("Dia: ");
        mes = pedirEntero("Mes: ");
        anio = pedirEntero("Anio: ");

        valido = fechaValida(dia,mes,anio);

        if(!valido)
        {
            std::cout << "ERROR: Fecha invalida..." << std::endl;
        }
    }
    while(!valido);

    return Fecha(dia,mes,anio);
}











