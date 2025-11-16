#include <iostream>
#include <string>
#include "WeatherLog.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    WeatherLog log;

    // Load the data source
    string dataSourceFile = "data/data_source.txt";
    if (!log.LoadData(dataSourceFile))
    {
        cout << "Failed to load weather data. Exiting program." << endl;
        return 1;
    }

    int choice;
    do
    {
        // Display menu options
        cout << "\n Weather Data Menu \n";
        cout << "1. Display average wind speed and SD for a month/year\n";
        cout << "2. Display average ambient air temperature and SD for each month of a year\n";
        cout << "3. Display total solar radiation for each month of a year\n";
        cout << "4. Display combined averages and totals for each month of a year\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Option 1: Avg wind speed and SD
            int month, year;
            cout << "Enter month (1-12): ";
            cin >> month;
            cout << "Enter year: ";
            cin >> year;
            log.DisplayAvgSpeed(month, year);
            break;
        }
        case 2:
        {
            // Option 2: Avg temp and SD per month
            int year;
            cout << "Enter year: ";
            cin >> year;
            log.DisplayAvgTempSD(year);
            break;
        }
        case 3:
        {
            // Option 3: Total solar radiation
            int year;
            cout << "Enter year: ";
            cin >> year;
            log.DisplayTotalSolarRad(year);
            break;
        }
        case 4:
        {
            // Option 4: Combined averages and totals
            int year;
            cout << "Enter year: ";
            cin >> year;
            log.DisplaySpeedTempSolarRad(year);
            break;
        }
        case 0:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    }
    while (choice != 0);

    return 0;
}
