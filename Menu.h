#pragma once
#include <string>

class Menu
{
public:
    Menu(int cantOpciones);
    void setOpciones(int opcion, const std::string &texto);
    void setTituloMenu(const std::string &tituloMenu);
    void setOpCero(const std::string &opCero);
    int runMenu()const;
    ~Menu();


private:
    int _cantOpciones;
    std::string* _vOpciones;
    std::string _tituloMenu;
    std::string _opCero;
};
