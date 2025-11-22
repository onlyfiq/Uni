#include "Time.h"
#include <iomanip>

using std::setw;
using std::setfill;

// Default constructor: initialize
Time::Time()
{
    m_hour = 0;
    m_minutes = 0;
}

// Constructor with specified hour and minutes
Time::Time(int hour, int minutes)
{
    SetTime(hour, minutes);
}

// Retrieve the hours
int Time::GetHours() const
{
    return m_hour;
}

// Retrieve the minutes
int Time::GetMinutes() const
{
    return m_minutes;
}

// Set the time with validation
// Invalid values are reset to 0
void Time::SetTime(int hour, int minutes)
{
    if(hour >= 0 && hour < 24)
    {
        m_hour = hour;
    }
    else
    {
        m_hour = 0;
    }

    if(minutes >= 0 && minutes < 60)
    {
        m_minutes = minutes;
    }
    else
    {
        m_minutes = 0;
    }
}

// Output operator: prints time as HH:MM with leading zeros
ostream& operator<<(ostream& os, const Time& t)
{
    os << setw(2) << setfill('0') << t.GetHours() << ":"
       << setw(2) << setfill('0') << t.GetMinutes();
    return os;
}

// Input operator: reads time in HH:MM format
istream& operator>>(istream& input, Time& t)
{
    int h, m;
    char colon;
    input >> h >> colon >> m;  // Expect format HH:MM
    t.SetTime(h, m);           // Validate and store
    return input;
}
