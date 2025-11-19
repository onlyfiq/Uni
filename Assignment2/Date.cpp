#include "Date.h"
#include <stdexcept>

using std::invalid_argument;

// Array of month names used for output
static const string MonthNames[12] =
{
    "January","February","March","April","May","June",
    "July","August","September","October","November","December"
};

// Default constructor: initialize to 1 January 1900
Date::Date()
{
    m_day = 1;
    m_month = 1;
    m_year = 1900;
}

// Constructor with specified day, month, and year
// Validates values using SetDate
Date::Date(int day, int month, int year)
{
    SetDate(day, month, year);
}

// Set the date after validating day, month, and year
void Date::SetDate(int day, int month, int year)
{
    if (day < 1 || day > 31)
    {
        throw invalid_argument("Day must be between 1 and 31");
    }

    if (month < 1 || month > 12)
    {
        throw invalid_argument("Month must be between 1 and 12");
    }

    if (year <= 0)
    {
        throw invalid_argument("Year cannot be 0");
    }

    m_day = day;
    m_month = month;
    m_year = year;
}

// Retrieve the day
int Date::GetDay() const
{
    return m_day;
}

// Retrieve the month
int Date::GetMonth() const
{
    return m_month;
}

// Retrieve the year
int Date::GetYear() const
{
    return m_year;
}

string Date::GetMonthNames() const
{
    return MonthNames[m_month - 1];
}

bool Date::operator<(const Date& other) const
{
    if (m_year != other.m_year)
    {
        return m_year < other.m_year;
    }
    if (m_month != other.m_month)
    {
        return m_month < other.m_month;
    }
    return m_day < other.m_day;
}

bool Date::operator==(const Date& other) const
{
    return m_day == other.m_day &&
           m_month == other.m_month &&
           m_year == other.m_year;
}

// Read date from input stream (format: day month year)
istream &operator>>(istream &input, Date &date)
{
    int d, m, y;
    input >> d >> m >> y;
    date.SetDate(d, m, y);
    return input;
}

// Write date to output stream (format: day MonthName year)
ostream &operator<<(ostream &os, const Date &date)
{
    os << date.GetDay() << " " << MonthNames[date.GetMonth() - 1] << " " << date.GetYear();
    return os;
}
