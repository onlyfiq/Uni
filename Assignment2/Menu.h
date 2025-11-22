#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "WeatherLog.h"

/**
 * @class Menu
 * @brief Provides a user interface loop for interacting with WeatherLog operations.
 *
 * The Menu class acts as the primary interface between the user and the system.
 * It owns a WeatherLog instance and provides a menu-driven loop where users can
 * select operations such as loading data, viewing statistics, and exporting results.
 */
class Menu
{
public:
    /**
     * @brief Starts the main menu loop.
     *
     * Displays available operations, handles user input, and invokes the
     * corresponding WeatherLog functions. The loop continues until the user
     * chooses to exit the program.
     */
    void Run();

private:
    WeatherLog log; /**< Internal WeatherLog instance managed by the menu. */
};

#endif // MENU_H_INCLUDED
