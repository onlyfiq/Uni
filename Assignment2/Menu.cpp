#include <iostream>
#include "Menu.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Main menu
void Menu::Run()
{
    // Load weather data from CSV files before starting menu
    if (!log.LoadData())
    {
        cout << "Failed to load weather data. Exiting.\n";
        return;
    }

    int choice = -1;

    // Main menu loop, continues until user chooses to exit
    do
    {
        // Display menu options to the user
        cout << "\n Weather Data Menu \n";
        cout << "1. Display average wind speed and SD for a month/year\n";
        cout << "2. Display average ambient air temperature and SD for each month of a year\n";
        cout << "3. Display sample Pearson Correlation Coefficient (sPCC) for a month\n";
        cout << "4. Display average wind speed(km/h), average ambient air temperature and total solar radiation in kWh/m2 for each month of a specified year\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Execute the user's selected option
        switch (choice)
        {
        case 1:
        {
            // Option 1: Average wind speed and standard deviation for a given month and year
            int month, year;
            cout << "Enter month (1-12): ";
            cin >> month;
            cout << "Enter year: ";
            cin >> year;
            log.DisplayAvgSpeed(month, year);  // Call WeatherLog method
            break;
        }
        case 2:
        {
            // Option 2: Average ambient air temperature and SD for each month of a given year
            int year;
            cout << "Enter year: ";
            cin >> year;
            log.DisplayAvgTempSD(year);  // Call WeatherLog method
            break;
        }
        case 3:
        {
            // Option 3: Compute sample Pearson Correlation Coefficient for a specified month
            int month;
            cout << "Enter month: ";
            cin >> month;
            log.DisplaySPCC(month);  // Call WeatherLog method
            break;
        }
        case 4:
        {
            // Option 4: Display combined stats (avg wind speed, avg temp, total solar radiation) with SD and MAD for a specified year
            int year;
            cout << "Enter year: ";
            cin >> year;
            log.DisplaySpeedTempSolarRadWithMAD(year);  // Call WeatherLog method
            break;
        }
        case 0:
            // Exit the program
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            // Handle invalid menu choices
            cout << "Invalid choice. Please try again.\n";
        }

    }
    while (choice != 0);    // Continue loop until user chooses 0 (Exit)
}
