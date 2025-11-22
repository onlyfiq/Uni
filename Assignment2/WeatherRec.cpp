#include "WeatherRec.h"
#include <iomanip>

using std::ostream;
using std::setw;
using std::setfill;

// Default constructor: initializes all numeric fields to 0 and date/time to default
WeatherRec::WeatherRec()
{
    m_speed = 0.0f;
    m_solarRad = 0.0f;
    m_airTemp = 0.0f;
}

// Constructor with specified values for date, time, wind speed, solar radiation, and air temperature
WeatherRec::WeatherRec(const Date& d, const Time& t, float speed, float solarRad, float ambAirTemp)
{
    m_date = d;
    m_time = t;
    m_speed = speed;
    m_solarRad = solarRad;
    m_airTemp = ambAirTemp;
}

// Returns the date of the weather record
const Date& WeatherRec::GetDate() const
{
    return m_date;
}

// Returns the time of the weather record
const Time& WeatherRec::GetTime() const
{
    return m_time;
}

// Returns the month of the weather record
int WeatherRec::GetMonth() const
{
    return m_date.GetMonth();
}

// Returns the year of the weather record
int WeatherRec::GetYear() const
{
    return m_date.GetYear();
}

// Returns the recorded wind speed
float WeatherRec::GetSpeed() const
{
    return m_speed;
}

// Returns the recorded solar radiation
float WeatherRec::GetSolarRad() const
{
    return m_solarRad;
}

// Returns the ambient air temperature
float WeatherRec::GetAmbAirTemp() const
{
    return m_airTemp;
}

// Sets the date of the record
void WeatherRec::SetDate(const Date& d)
{
    m_date = d;
}

// Sets the time of the record
void WeatherRec::SetTime(const Time& t)
{
    m_time = t;
}

// Sets the wind speed of the record
void WeatherRec::SetSpeed(float speed)
{
    m_speed = speed;
}

// Sets the solar radiation of the record
void WeatherRec::SetSolarRad(float solarRad)
{
    m_solarRad = solarRad;
}

// Sets the ambient air temperature of the record
void WeatherRec::SetAmbAirTemp(float ambAirTemp)
{
    m_airTemp = ambAirTemp;
}

// Returns a DateTimeKey object for this record (useful for BST sorting)
DateTimeKey WeatherRec::GetDateTimeKey() const
{
    return DateTimeKey(m_date, m_time);
}

// Output stream operator: prints the weather record in a readable format
ostream& operator<<(ostream& os, const WeatherRec& wr)
{
    os << wr.GetDate() << " " << wr.GetTime()
       << " | Speed: " << wr.GetSpeed() << " m/s"
       << " | Solar Radiation: " << wr.GetSolarRad() << " W/m^2"
       << " | Air Temp: " << wr.GetAmbAirTemp() << " C";
    return os;
}
