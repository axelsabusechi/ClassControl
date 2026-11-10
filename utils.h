#pragma once
#include <string>
#include "Grado.h"
#include "Division.h"
#include "Curso.h"
#include "Fecha.h"

Grado intToGrado(int grado);
Division intToDivision(int div);
std::string gradoToString(Grado grado);
std::string divisionToString(Division div);
void showItem(const std::string &text, int posx, int posy, bool selected);
std::string cargarCadena();
bool nombreApellidoValido(const std::string &nombreApellido);
bool dniValido(const std::string &dni);
bool emailValido(const std::string &email);
bool anioBisiesto(int anio);
bool fechaValida(int dia, int mes, int anio);
bool textoVacio(const std::string &texto);
int pedirEntero(const std::string &mensaje);
std::string pedirNombreApellido(const std::string &mensaje);
std::string pedirDni(const std::string &mensaje);
std::string pedirEmail(const std::string &mensaje);
std::string pedirAdaptacion(const std::string &mensaje);
Fecha pedirFecha(const std::string &mensaje);
bool mostrarErrorArchivo(const std::string &mensaje);
