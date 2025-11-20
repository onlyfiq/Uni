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
    if(s.empty())
    {
        return false;
    }

    // handle invalid words like NA, N/A, --- etc.
    string lower;
    for(size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if(c >= 'A' && c <= 'Z')
        {
            c = c - 'A' + 'a';
        }
        lower += c;
    }

    if(lower == "na" || lower == "n/a" || lower == "---" || lower == "-9999")
    {
        return false;
    }

    bool hasDigit = false;
    bool hasDot = false;
    bool hasE = false;

    for(size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if(c >= '0' && c <= '9')
        {
            hasDigit = true;
        }
        else if(c == '.')
        {
            if(hasDot || hasE)
            {
                return false;
            }
            hasDot = true;
        }
        else if(c == 'e' || c == 'E')
        {
            if(hasE || !hasDigit || i + 1 == s.size())
            {
                return false;
            }
            hasE = true;
            hasDigit = false;
        }
        else if(c == '+' || c == '-')
        {
            if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E')
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    return hasDigit;
}

// Recursive middle insertion to build balanced BST
void InsertMiddle(Bst<RecNode>& bst, Vector<RecNode>& nodes, int start, int end)
{
    if(start > end)
    {
        return;
    }

    int mid = (start + end) / 2;
    bst.Insert(nodes[mid]);
    InsertMiddle(bst, nodes, start, mid - 1);
    InsertMiddle(bst, nodes, mid + 1, end);
}

// Global traversal buffer
static Vector<RecNode>* g_traverseBuffer = nullptr;

// Function pointer callback to collect nodes
static void CollectRecNode(const RecNode& node)
{
    if (g_traverseBuffer != nullptr)
    {
        g_traverseBuffer->Insert(g_traverseBuffer->GetSize(), node);
    }
}

// Load CSV data into weatherData
bool WeatherLog::LoadData()
{
    // Load the data source
    string dataSourceFile = "data/data_source.txt";

    // Read the CSV file name from data_source.txt
    ifstream sourceFile(dataSourceFile);
    if(!sourceFile.is_open())
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

        while(getline(headerStream, col, ','))
        {
            columns.Insert(columns.GetSize(), col);
        }

        int idxWAST = -1, idxWind = -1, idxTemp = -1, idxSolar = -1;
        for(int i = 0; i < columns.GetSize(); i++)
        {
            if(columns[i] == "WAST")
            {
                idxWAST = i;
            }
            else if(columns[i] == "S")
            {
                idxWind = i;
            }
            else if(columns[i] == "T")
            {
                idxTemp = i;
            }
            else if(columns[i] == "SR")
            {
                idxSolar = i;
            }
        }

        if(idxWAST == -1 || idxWind == -1 || idxTemp == -1 || idxSolar == -1)
        {
            cout << "CSV missing required columns (WAST, S, T, SR) in " << csvFilePath << endl;
            csvFile.close();
            continue;
        }

        Map<int, Map<int, Vector<RecNode>>> tempData;

        // Read data rows
        string line;
        while(getline(csvFile, line))
        {
            stringstream ss(line);
            string token;
            Vector<string> row;

            while(getline(ss, token, ','))
            {
                row.Insert(row.GetSize(), token);
            }

            if(row.GetSize() != columns.GetSize())
            {
                continue;
            }

            // Parse WAST column into Date and Time
            string wast = row[idxWAST]; // e.g., "01/01/2025 12:00"
            int day, month, year, hour, minute;
            if(sscanf(wast.c_str(), "%d/%d/%d %d:%d", &day, &month, &year, &hour, &minute) != 5)
            {
//                cout << "Skipping invalid WAST: " << wast << endl;
                continue;
            }

            if(!IsValidNumber(row[idxWind]) ||
                    !IsValidNumber(row[idxTemp]) ||
                    !IsValidNumber(row[idxSolar]))
            {
//                cout << "Skipping invalid numeric row: " << line << endl;
                continue;
            }

            try
            {
                float wind = stof(row[idxWind]);
                float temp = stof(row[idxTemp]);
                float solar = stof(row[idxSolar]);

                wind = wind * 3.6f;
                solar = solar * 0.0001667f;

                Date d(day, month, year);
                Time t(hour, minute);
                WeatherRec w(d, t, wind, solar, temp);
                RecNode recNode(w);

                if(!tempData.Contains(year))
                {
                    tempData[year] = Map<int, Vector<RecNode>>();
                }
                if(!tempData[year].Contains(month))
                {
                    tempData[year][month] = Vector<RecNode>();
                }

                tempData[year][month].Insert(tempData[year][month].GetSize(), recNode);
                totalRecords++;
            }

            catch(const invalid_argument& e)
            {
                cout << "Skipping invalid numeric conversion: " << line
                     << " (" << e.what() << ")" << endl;
            }
            catch(const out_of_range& e)
            {
                cout << "Skipping out-of-range numeric value: " << line
                     << " (" << e.what() << ")" << endl;
            }
        }

        Vector<int> yearKeys;
        tempData.GetKeys(yearKeys);
        for(int y = 0; y < yearKeys.GetSize(); y++)
        {
            int yearKey = yearKeys[y];
            if(!m_data.Contains(yearKey))
            {
                m_data[yearKey] = Map<int, Bst<RecNode>>();
            }

            Map<int, Vector<RecNode>>& months = tempData[yearKey];

            Vector<int> monthKeys;
            months.GetKeys(monthKeys);

            for(int m = 0; m < monthKeys.GetSize(); m++)
            {
                int monthKey = monthKeys[m];
                Vector<RecNode>& nodes = months[monthKey];

                if(!m_data[yearKey].Contains(monthKey))
                {
                    m_data[yearKey][monthKey] = Bst<RecNode>();
                }

                InsertMiddle(m_data[yearKey][monthKey], nodes, 0, nodes.GetSize() - 1);
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
    if (!m_data.Contains(year) || !m_data[year].Contains(month))
    {
        cout << "No data for " << month << "/" << year << endl;
        return;
    }

    Vector<RecNode> nodes;
    g_traverseBuffer = &nodes;
    m_data[year][month].InOrder(CollectRecNode);
    g_traverseBuffer = nullptr;

    if (nodes.GetSize() == 0)
    {
        cout << "No data for " << month << "/" << year << endl;
        return;
    }

    Vector<float> speeds;
    for (int i = 0; i < nodes.GetSize(); i++)
    {
        speeds.Insert(speeds.GetSize(), nodes[i].rec.GetSpeed());
    }

    float sum = 0;
    for (int i = 0; i < speeds.GetSize(); i++)
    {
        sum += speeds[i];
    }

    float avg = sum / speeds.GetSize();

    float sumSq = 0;
    for (int i = 0; i < speeds.GetSize(); i++)
    {
        sumSq += (speeds[i] - avg) * (speeds[i] - avg);
    }

    float sd = (speeds.GetSize() > 1) ? sqrt(sumSq / (speeds.GetSize() - 1)) : 0;


    cout << "Month: " << month << " Year: " << year
         << " | Avg Speed: " << avg << " | SD: " << sd << endl;
}

// 2. Average temperature and SD for each month of a year
void WeatherLog::DisplayAvgTempSD(int year)
{
    if(!m_data.Contains(year))
    {
        cout << "No data for year " << year << endl;
        return;
    }

    Map<int, Bst<RecNode>>& months = m_data[year];

    Vector<int> monthKeys;
    months.GetKeys(monthKeys);

    for(int m = 0; m < monthKeys.GetSize(); m++)
    {
        int month = monthKeys[m];

        Vector<RecNode> nodes;
        g_traverseBuffer = &nodes;
        Bst<RecNode>& bst = months[month];
        bst.InOrder(CollectRecNode);
        g_traverseBuffer = nullptr;

        Vector<float> temps;
        for (int i = 0; i < nodes.GetSize(); i++)
        {
            temps.Insert(temps.GetSize(), nodes[i].rec.GetAmbAirTemp());
        }

        if(temps.GetSize() == 0)
        {
            continue;
        }

        float sum = 0.0f;
        for(int i = 0; i < temps.GetSize(); i++)
        {
            sum += temps[i];
        }

        float avg = sum / temps.GetSize();

        float sumSq = 0.0f;
        for(int i = 0; i < temps.GetSize(); i++)
        {
            sumSq += (temps[i] - avg) * (temps[i] - avg);
        }

        float sd = (temps.GetSize() > 1) ? sqrt(sumSq / (temps.GetSize() - 1)) : 0.0f;

        cout << "Month: " << month
             << " | Avg Temp: " << avg << " C"
             << " | SD: " << sd << endl;
    }
}

float sPCC(const Vector<float>& X, const Vector<float>& Y)
{
    int n = X.GetSize();
    if(n == 0 || n != Y.GetSize())
    {
        return 0.0f;
    }

    float sumX = 0.0f, sumY = 0.0f;
    for(int i = 0; i < n; i++)
    {
        sumX += X[i];
        sumY += Y[i];
    }

    float meanX = sumX / n;
    float meanY = sumY / n;

    float numerator = 0.0f;
    float denomX = 0.0f, denomY = 0.0f;

    for(int i = 0; i < n; i++)
    {
        float dx = X[i] - meanX;
        float dy = Y[i] - meanY;
        numerator += dx * dy;
        denomX += dx * dx;
        denomY += dy * dy;
    }

    if(denomX == 0 || denomY == 0)
    {
        return 0.0f;
    }

    return numerator / sqrt(denomX * denomY);
}

void WeatherLog::DisplaySPCC(int month)
{
    Vector<float> S, T, R;

    // Collect all data for specified month across all years
    Vector<int> yearKeys;
    m_data.GetKeys(yearKeys);
    for(int y = 0; y < yearKeys.GetSize(); y++)
    {
        int yearKey = yearKeys[y];
        Map<int, Bst<RecNode>>& months = m_data[yearKey];
        if(!months.Contains(month))
        {
            continue;
        }

        Bst<RecNode>& bst = months[month];
        Vector<RecNode> nodes;
        g_traverseBuffer = &nodes;
        bst.InOrder(CollectRecNode);
        g_traverseBuffer = nullptr;

        for(int i = 0; i < nodes.GetSize(); i++)
        {
            WeatherRec& rec = nodes[i].rec;
            S.Insert(S.GetSize(), rec.GetSpeed());
            T.Insert(T.GetSize(), rec.GetAmbAirTemp());
            R.Insert(R.GetSize(), rec.GetSolarRad());
        }
    }

    float ST = sPCC(S, T);
    float SR = sPCC(S, R);
    float TR = sPCC(T, R);

    cout << "Sample Pearson Correlation Coefficient for month " << month << endl;
    cout << "S_T: " << ST << endl;
    cout << "S_R: " << SR << endl;
    cout << "T_R: " << TR << endl;
}

float MeanAbsoluteDeviation(const Vector<float>& data, float mean)
{
    float mad = 0.0f;
    int n = data.GetSize();
    for(int i = 0; i < n; i++)
    {
        mad += fabs(data[i] - mean);
    }
    return (n > 0) ? (mad / n) : 0.0f;
}

void WeatherLog::DisplaySpeedTempSolarRadWithMAD(int year)
{
    ofstream file("WindTempSolar.csv");
    if(!file.is_open())
    {
        cout << "Failed to open CSV file for writing." << endl;
        return;
    }

    file << year << "\n";
    file << "Month,Average Wind Speed(stdev,mad),Average Ambient Temperature(stdev,mad),Total Solar Radiation\n";

    Map<int, Bst<RecNode>>& months = m_data[year];

    for(int month = 1; month <= 12; month++)
    {
        if(!months.Contains(month))
        {
            continue;
        }

        Bst<RecNode>& bst = months[month];
        Vector<RecNode> nodes;
        g_traverseBuffer = &nodes;
        bst.InOrder(CollectRecNode);
        g_traverseBuffer = nullptr;

        Vector<float> speeds, temps, solar;
        for(int i = 0; i < nodes.GetSize(); i++)
        {
            WeatherRec& rec = nodes[i].rec;
            speeds.Insert(speeds.GetSize(), rec.GetSpeed());
            temps.Insert(temps.GetSize(), rec.GetAmbAirTemp());
            solar.Insert(solar.GetSize(), rec.GetSolarRad() * 0.0001667f); // convert to kWh/m2
        }

        int n = speeds.GetSize();
        if(n == 0)
        {
            continue;
        }

        // Compute averages
        float sumSpeed = 0, sumTemp = 0, sumSolar = 0;
        for(int i = 0; i < n; i++)
        {
            sumSpeed += speeds[i];
            sumTemp += temps[i];
            sumSolar += solar[i];
        }
        float avgSpeed = sumSpeed / n;
        float avgTemp = sumTemp / n;
        float totalSolar = sumSolar;

        // Compute standard deviations
        float sumSqSpeed = 0, sumSqTemp = 0;
        for(int i = 0; i < n; i++)
        {
            sumSqSpeed += (speeds[i] - avgSpeed) * (speeds[i] - avgSpeed);
            sumSqTemp += (temps[i] - avgTemp) * (temps[i] - avgTemp);
        }
        float sdSpeed = (n > 1) ? sqrt(sumSqSpeed / (n - 1)) : 0.0f;
        float sdTemp = (n > 1) ? sqrt(sumSqTemp / (n - 1)) : 0.0f;

        // Compute MAD
        float madSpeed = MeanAbsoluteDeviation(speeds, avgSpeed);
        float madTemp = MeanAbsoluteDeviation(temps, avgTemp);

        // Print to CSV
        file << month << ","
             << avgSpeed << "(" << sdSpeed << "," << madSpeed << "),"
             << avgTemp << "(" << sdTemp << "," << madTemp << "),"
             << totalSolar << "\n";

        cout << "Month " << month
             << " | Avg Speed: " << avgSpeed << " (SD:" << sdSpeed << ", MAD:" << madSpeed << ")"
             << " | Avg Temp: " << avgTemp << " (SD:" << sdTemp << ", MAD:" << madTemp << ")"
             << " | Total Solar: " << totalSolar << endl;
    }

    file.close();
    cout << "Results written to WindTempSolar.csv" << endl;
}
