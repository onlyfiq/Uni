#include "WeatherLog.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;
using std::stringstream;
using std::stof;
using std::invalid_argument;
using std::out_of_range;

// Constructor: initialize empty weather log
WeatherLog::WeatherLog() {}

bool IsValidNumber(const string& s)
{
    if (s.empty())
        return false;

    // handle invalid words like NA, N/A, --- etc.
    string lower;
    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if (c >= 'A' && c <= 'Z')
            c = c - 'A' + 'a';
        lower += c;
    }

    if (lower == "na" || lower == "n/a" || lower == "---" || lower == "-9999")
        return false;

    bool hasDigit = false;
    bool hasDot = false;
    bool hasE = false;

    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if (c >= '0' && c <= '9')
        {
            hasDigit = true;
        }
        else if (c == '.')
        {
            if (hasDot || hasE)
                return false;
            hasDot = true;
        }
        else if (c == 'e' || c == 'E')
        {
            if (hasE || !hasDigit || i + 1 == s.size())
                return false;
            hasE = true;
            hasDigit = false;
        }
        else if (c == '+' || c == '-')
        {
            if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E')
                return false;
        }
        else
        {
            return false;
        }
    }

    return hasDigit;
}

// Load CSV data into weatherData
bool WeatherLog::LoadData(const string& dataSourceFile)
{
    // Read the CSV file name from data_source.txt
    ifstream sourceFile(dataSourceFile);
    if (!sourceFile.is_open())
    {
        cout << "Failed to open " << dataSourceFile << endl;
        return false;
    }

    string csvFileName;
    int totalRecords = 0;

    while(getline(sourceFile, csvFileName))
    {
        if(csvFileName.empty())
        {
            continue;
        }
        string csvFilePath = "data/" + csvFileName;
        ifstream csvFile(csvFilePath);
        if(!csvFile.is_open())
        {
            cout << "Failed to open CSV File" << csvFilePath << endl;
            continue;
        }
        cout <<  "Reading " << csvFilePath << "..." << endl;

        // Read header and map columns
        string headerLine;
        getline(csvFile, headerLine);
        stringstream headerStream(headerLine);
        string col;
        Vector<string> columns;

        while (getline(headerStream, col, ','))
        {
            columns.Insert(columns.GetSize(), col);
        }

        int idxWAST = -1, idxWind = -1, idxTemp = -1, idxSolar = -1;
        for (int i = 0; i < columns.GetSize(); i++)
        {
            if (columns[i] == "WAST")
            {
                idxWAST = i;
            }
            else if (columns[i] == "S")
            {
                idxWind = i;
            }
            else if (columns[i] == "T")
            {
                idxTemp = i;
            }
            else if (columns[i] == "SR")
            {
                idxSolar = i;
            }
        }

        if (idxWAST == -1 || idxWind == -1 || idxTemp == -1 || idxSolar == -1)
        {
            cout << "CSV missing required columns (WAST, S, T, SR) in " << csvFilePath << endl;
            csvFile.close();
            continue;
        }


        // Read data rows
        string line;
        while (getline(csvFile, line))
        {
            stringstream ss(line);
            string token;
            Vector<string> row;

            while (getline(ss, token, ','))
            {
                row.Insert(row.GetSize(), token);
            }

            if (row.GetSize() != columns.GetSize())
            {
                continue;
            }

            // Parse WAST column into Date and Time
            string wast = row[idxWAST]; // e.g., "01/01/2025 12:00"
            int day, month, year, hour, minute;
            if (sscanf(wast.c_str(), "%d/%d/%d %d:%d", &day, &month, &year, &hour, &minute) != 5)
            {
                cout << "Skipping invalid WAST: " << wast << endl;
                continue;
            }

            if (!IsValidNumber(row[idxWind]) ||
                    !IsValidNumber(row[idxTemp]) ||
                    !IsValidNumber(row[idxSolar]))
            {
                cout << "Skipping invalid numeric row: " << line << endl;
                continue;
            }

            try
            {
                float wind = stof(row[idxWind]);
                float temp = stof(row[idxTemp]);
                float solar = stof(row[idxSolar]);

                Date d(day, month, year);
                Time t(hour, minute);
                WeatherRec rec(d, t, wind, solar, temp);
                weatherData.Insert(weatherData.GetSize(), rec);
                totalRecords++;
            }

            catch (const invalid_argument& e)
            {
                cout << "Skipping invalid numeric conversion: " << line
                     << " (" << e.what() << ")" << endl;
            }
            catch (const out_of_range& e)
            {
                cout << "Skipping out-of-range numeric value: " << line
                     << " (" << e.what() << ")" << endl;
            }
        }
        csvFile.close();
    }

    sourceFile.close();
    cout << "Loaded total " << totalRecords << " records from all CSV files." << endl;
    return true;
}

// 1. Average wind speed and SD for a month/year
void WeatherLog::DisplayAvgSpeed(int month, int year)
{
    float sum = 0.0f;
    int count = 0;

    for (int i = 0; i < weatherData.GetSize(); i++)
    {
        WeatherRec& rec = weatherData[i];
        if (rec.GetMonth() == month && rec.GetYear() == year)
        {
            sum += rec.GetSpeed();
            count++;
        }
    }

    if (count == 0)
    {
        cout << "No data for " << month << "/" << year << endl;
        return;
    }

    float avg = sum / count;

    float sumSq = 0.0f;
    for (int i = 0; i < weatherData.GetSize(); i++)
    {
        WeatherRec& rec = weatherData[i];
        if (rec.GetMonth() == month && rec.GetYear() == year)
        {
            sumSq += (rec.GetSpeed() - avg) * (rec.GetSpeed() - avg);
        }
    }

    float sd = (count > 1) ? sqrt(sumSq / (count - 1)) : 0.0f;

    cout << "Month: " << month << " Year: " << year
         << " | Avg Speed: " << avg << " km/h"
         << " | SD: " << sd << endl;
}

// 2. Average temperature and SD for each month of a year
void WeatherLog::DisplayAvgTempSD(int year)
{
    for (int month = 1; month <= 12; month++)
    {
        float sum = 0.0f;
        int count = 0;

        for (int i = 0; i < weatherData.GetSize(); i++)
        {
            WeatherRec& rec = weatherData[i];
            if (rec.GetMonth() == month && rec.GetYear() == year)
            {
                sum += rec.GetAmbAirTemp();
                count++;
            }
        }

        if (count == 0)
        {
            continue;
        }

        float avg = sum / count;
        float sumSq = 0.0f;

        for (int i = 0; i < weatherData.GetSize(); i++)
        {
            WeatherRec& rec = weatherData[i];
            if (rec.GetMonth() == month && rec.GetYear() == year)
            {
                sumSq += (rec.GetAmbAirTemp() - avg) * (rec.GetAmbAirTemp() - avg);
            }
        }

        float sd = (count > 1) ? sqrt(sumSq / (count - 1)) : 0.0f;

        cout << "Month: " << month
             << " | Avg Temp: " << avg << " C"
             << " | SD: " << sd << endl;
    }
}

// 3. Total solar radiation per month for a year
void WeatherLog::DisplayTotalSolarRad(int year)
{
    for (int month = 1; month <= 12; month++)
    {
        float total = 0.0f;

        for (int i = 0; i < weatherData.GetSize(); i++)
        {
            WeatherRec& rec = weatherData[i];
            if (rec.GetMonth() == month && rec.GetYear() == year)
            {
                total += rec.GetSolarRad() * 0.0001667f;
            }
        }

        if (total > 0)
        {
            cout << "Month: " << month << " | Total Solar Radiation: " << total << " kWh/m2" << endl;
        }
    }
}

// 4. Combined averages and totals per month
void WeatherLog::DisplaySpeedTempSolarRad(int year)
{
    for (int month = 1; month <= 12; month++)
    {
        float sumSpeed = 0, sumTemp = 0, totalRad = 0;
        int count = 0;

        for (int i = 0; i < weatherData.GetSize(); i++)
        {
            WeatherRec& rec = weatherData[i];
            if (rec.GetMonth() == month && rec.GetYear() == year)
            {
                sumSpeed += rec.GetSpeed();
                sumTemp += rec.GetAmbAirTemp();
                totalRad += rec.GetSolarRad() * 0.0001667f;
                count++;
            }
        }

        if (count == 0)
        {
            continue;
        }

        float avgSpeed = sumSpeed / count;
        float avgTemp = sumTemp / count;

        float sumSq = 0.0f;
        for (int i = 0; i < weatherData.GetSize(); i++)
        {
            WeatherRec& rec = weatherData[i];
            if (rec.GetMonth() == month && rec.GetYear() == year)
            {
                sumSq += (rec.GetSpeed() - avgSpeed) * (rec.GetSpeed() - avgSpeed);
            }
        }

        float sdSpeed = (count > 1) ? sqrt(sumSq / (count - 1)) : 0.0f;

        cout << "Month: " << month
             << " | Avg Speed: " << avgSpeed << " (SD:" << sdSpeed << ") km/h"
             << " | Avg Temp: " << avgTemp << " C"
             << " | Total Solar Rad: " << totalRad << " kWh/m2" << endl;
    }

    // Automatically export results to CSV
    PrintToCsv(year);
}

// Print results to CSV
void WeatherLog::PrintToCsv(int year)
{
    ofstream file("WindTempSolar.csv");
    if (!file.is_open())
    {
        cout << "Failed to open CSV file for writing." << endl;
        return;
    }

    file << "Month,AvgSpeed,SDSpeed,AvgTemp,TotalSolarRad\n";

    for (int month = 1; month <= 12; month++)
    {
        float sumSpeed = 0, sumTemp = 0, totalRad = 0;
        int count = 0;

        for (int i = 0; i < weatherData.GetSize(); i++)
        {
            WeatherRec& rec = weatherData[i];
            if (rec.GetMonth() == month && rec.GetYear() == year)
            {
                sumSpeed += rec.GetSpeed();
                sumTemp += rec.GetAmbAirTemp();
                totalRad += rec.GetSolarRad() * 0.0001667f;
                count++;
            }
        }

        if (count == 0)
        {
            continue;
        }

        float avgSpeed = sumSpeed / count;
        float avgTemp = sumTemp / count;

        float sumSq = 0.0f;
        for (int i = 0; i < weatherData.GetSize(); i++)
        {
            WeatherRec& rec = weatherData[i];
            if (rec.GetMonth() == month && rec.GetYear() == year)
            {
                sumSq += (rec.GetSpeed() - avgSpeed) * (rec.GetSpeed() - avgSpeed);
            }
        }

        float sdSpeed = (count > 1) ? sqrt(sumSq / (count - 1)) : 0.0f;

        file << month << "," << avgSpeed << "," << sdSpeed << "," << avgTemp << "," << totalRad << "\n";
    }

    file.close();
    cout << "Results written to WindTempSolar.csv" << endl;
}
