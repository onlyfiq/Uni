#ifndef WEATHERLOG_H_INCLUDED
#define WEATHERLOG_H_INCLUDED

#include <string>
#include "Map.h"
#include "BST.h"
#include "Date.h"
#include "Time.h"
#include "EncapVect.h"
#include "DateTimeKey.h"
#include "WeatherRec.h"
#include "RecNode.h"

using std::string;

/**
 * @class WeatherLog
 * @brief Loads, stores, and performs statistical analysis on weather records.
 *
 * The WeatherLog class manages all weather data used by the application.
 * Data is loaded from one or more CSV files whose filenames are listed inside
 * **data/data_source.txt**.
 *
 * Internally, data is stored in a three-level structure:
 *
 *     Map<year, Map<month, Bst<RecNode>>>
 *
 * Each RecNode contains a WeatherRec and is inserted into the BST using
 * a DateTimeKey, ensuring chronological ordering and fast searching.
 *
 * The class provides methods for computing:
 *   - Average wind speed (with standard deviation)
 *   - Average ambient air temperature (with standard deviation)
 *   - Total solar radiation
 *   - Pearson correlation coefficients (S/T/R)
 *   - MAD (Mean Absolute Deviation) for selected statistics
 *
 * Results can be displayed to console or exported to CSV.
 */
class WeatherLog
{
public:

    /**
     * @brief Constructs an empty WeatherLog container.
     */
    WeatherLog();

    /**
     * @brief Loads and parses all weather data from CSV files.
     *
     * The method performs the following:
     *   1. Reads the list of CSV filenames from data/data_source.txt
     *   2. Opens each CSV file inside the data/ directory
     *   3. Parses WAST, wind speed, temperature, and solar radiation
     *   4. Converts units (wind: m/s → km/h externally; solar: W/m² → kWh/m² if required)
     *   5. Builds month-based BSTs for each year
     *
     * Invalid rows are skipped only if:
     *   - WAST timestamp cannot be parsed
     *   - The required numeric values (S, T, SR) are not valid numbers
     *
     * @return True if all accessible files were processed, false if none succeeded.
     */
    bool LoadData();

    /**
     * @brief Displays the average wind speed and standard deviation for a given month/year.
     *
     * Retrieves the appropriate BST, traverses it in-order, and computes:
     *   - Mean wind speed
     *   - Standard deviation
     *
     * @param month Month number (1–12).
     * @param year  Full year (e.g., 2024).
     */
    void DisplayAvgSpeed(int month, int year);

    /**
     * @brief Displays monthly average ambient air temperature and standard deviation for a year.
     *
     * Traverses each month’s BST (if present) and prints:
     *   - Monthly average temperature
     *   - Standard deviation
     *
     * @param year Year to analyze.
     */
    void DisplayAvgTempSD(int year);

    /**
     * @brief Computes and displays the Sample Pearson Correlation Coefficient (SPCC)
     *        for all records in a given month across all years.
     *
     * Calculates the three correlation pairs:
     *   - S vs. T   (wind speed vs. temperature)
     *   - S vs. SR  (wind speed vs. solar radiation)
     *   - T vs. SR  (temperature vs. solar radiation)
     *
     * @param month Month (1–12) to analyze.
     */
    void DisplaySPCC(int month);

    /**
     * @brief Displays combined monthly statistics for a given year.
     *
     * For each month with data, computes:
     *   - Average wind speed and SD
     *   - Average ambient temperature and SD
     *   - Total solar radiation
     *
     * @param year Year to calculate statistics for.
     */
    void DisplaySpeedTempSolarRad(int year);

    /**
     * @brief Displays extended monthly statistics including MAD (Mean Absolute Deviation).
     *
     * For each month:
     *   - Average wind speed, SD, MAD
     *   - Average temperature, SD, MAD
     *   - Total solar radiation
     *
     * Results are also stored in the output file: `WindTempSolar.csv`
     *
     * @param year Year to process.
     */
    void DisplaySpeedTempSolarRadWithMAD(int year);

    /**
     * @brief Exports monthly statistics (Option 4) to a CSV file.
     *
     * Output format:
     *     Month, AvgSpeed, SDSpeed, AvgTemp, TotalSolarRad
     *
     * @param year Year to export.
     */
    void PrintToCsv(int year);

private:
    /**
     * @brief Hierarchical weather data storage.
     *
     * Structure:
     *     m_data[year][month] → BST sorted by DateTimeKey
     *
     * Ensures:
     *   - Fast access by year/month
     *   - Chronological ordering within each month
     */
    Map<int, Map<int, Bst<RecNode>>> m_data;
};

#endif // WEATHERLOG_H_INCLUDED
