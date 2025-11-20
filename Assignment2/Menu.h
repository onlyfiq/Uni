#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "WeatherLog.h"

class Menu
{
public:
    void Run();             // Main menu loop

private:
    WeatherLog log;         // The WeatherLog object is inside Menu
};

#endif // MENU_H_INCLUDED
