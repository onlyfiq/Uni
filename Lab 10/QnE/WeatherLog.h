#ifndef WEATHERLOG_H_INCLUDED
#define WEATHERLOG_H_INCLUDED

#include <string>
#include "EncapVect.h"
#include "WeatherRec.h"

using std::string;

/**
 * @class WeatherLog
 * @brief Manages and processes weather records loaded from CSV files.
 *
 * Provides methods to calculate average wind speed, temperature, solar radiation,
 * standard deviations, and export summarized results to a CSV file.
 */
class WeatherLog
{
public:
    /**
     * @brief Default constructor.
     *
     * Initializes an empty WeatherLog object.
     */
    WeatherLog();

    /**
     * @brief Loads weather data from a CSV file.
     * @param filePath Path to the data source file.
     * @return True if data was successfully loaded, false otherwise.
     */
    bool LoadData(const string& filePath);

    /**
     * @brief Displays average wind speed and standard deviation for a specific month and year.
     * @param month Month (1-12) to calculate statistics for.
     * @param year Year to calculate statistics for.
     */
    void DisplayAvgSpeed(int month, int year);

    /**
     * @brief Displays average ambient air temperature and standard deviation
     *        for each month of a specified year.
     * @param year Year to calculate statistics for.
     */
    void DisplayAvgTempSD(int year);

    /**
     * @brief Displays total solar radiation for each month of a specified year.
     * @param year Year to calculate total solar radiation.
     */
    void DisplayTotalSolarRad(int year);

    /**
     * @brief Displays combined averages and totals per month for a specified year:
     *        average wind speed (with SD), average temperature, total solar radiation.
     * @param year Year to calculate combined statistics for.
     */
    void DisplaySpeedTempSolarRad(int year);

    /**
     * @brief Exports combined averages and totals (option 4) to a CSV file.
     * @param year Year to export statistics for.
     *
     * CSV file columns: Month, AvgSpeed, SDSpeed, AvgTemp, TotalSolarRad
     */
    void PrintToCsv(int year);

private:
    Vector<WeatherRec> weatherData; /**< Container storing all weather records */
};

#endif // WEATHERLOG_H_INCLUDED
