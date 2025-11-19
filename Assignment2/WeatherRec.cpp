#include "WeatherRec.h"
#include <iomanip>

using std::ostream;
using std::setw;
using std::setfill;

// Default constructor: initializes all numeric fields to 0
WeatherRec::WeatherRec()
{
    m_speed = 0.0f;
    m_solarRad = 0.0f;
    m_airTemp = 0.0f;
}

// Constructor with specified values
WeatherRec::WeatherRec(const Date& d, const Time& t, float speed, float solarRad, float ambAirTemp)
{
    m_date = d;
    m_time = t;
    m_speed = speed;
    m_solarRad = solarRad;
    m_airTemp = ambAirTemp;
}

// Accessors
const Date& WeatherRec::GetDate() const
{
    return m_date;
}

const Time& WeatherRec::GetTime() const
{
    return m_time;
}

int WeatherRec::GetMonth() const
{
    return m_date.GetMonth();
}

int WeatherRec::GetYear() const
{
    return m_date.GetYear();
}

float WeatherRec::GetSpeed() const
{
    return m_speed;
}

float WeatherRec::GetSolarRad() const
{
    return m_solarRad;
}

float WeatherRec::GetAmbAirTemp() const
{
    return m_airTemp;
}

// Mutators
void WeatherRec::SetDate(const Date& d)
{
    m_date = d;
}

void WeatherRec::SetTime(const Time& t)
{
    m_time = t;
}

void WeatherRec::SetSpeed(float speed)
{
    m_speed = speed;
}

void WeatherRec::SetSolarRad(float solarRad)
{
    m_solarRad = solarRad;
}

void WeatherRec::SetAmbAirTemp(float ambAirTemp)
{
    m_airTemp = ambAirTemp;
}

DateTimeKey WeatherRec::GetDateTimeKey() const
{
    return DateTimeKey(m_date, m_time);
}

// Output operator: prints the weather record neatly
ostream& operator<<(ostream& os, const WeatherRec& wr)
{
    os << wr.GetDate() << " " << wr.GetTime()
       << " | Speed: " << wr.GetSpeed() << " m/s"
       << " | Solar Radiation: " << wr.GetSolarRad() << " W/m^2"
       << " | Air Temp: " << wr.GetAmbAirTemp() << " C";
    return os;
}
