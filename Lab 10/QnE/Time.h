#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>

using std::ostream;
using std::istream;

/**
 * @class Time
 * @brief Represents a specific time of day in hours and minutes.
 *
 * Provides methods to retrieve and set time, and supports I/O streaming.
 */
class Time
{
public:
    /**
     * @brief Default constructor. Initializes time to 00:00.
     */
    Time();

    /**
     * @brief Parameterized constructor.
     * @param hour The hour component (0-23).
     * @param minutes The minute component (0-59).
     */
    Time(int hour, int minutes);

    /**
     * @brief Retrieves the hour component of the time.
     * @return The hour (0-23).
     */
    int GetHours() const;

    /**
     * @brief Retrieves the minute component of the time.
     * @return The minutes (0-59).
     */
    int GetMinutes() const;

    /**
     * @brief Sets the time.
     * @param hour The hour to set (0-23).
     * @param minutes The minutes to set (0-59).
     */
    void SetTime(int hour, int minutes);

private:
    int m_hour;    /**< Hour component (0-23) */
    int m_minutes; /**< Minute component (0-59) */
};

/**
 * @brief Outputs a Time object to a stream.
 * @param out The output stream.
 * @param t The Time object to output.
 * @return Reference to the output stream.
 */
ostream& operator<<(ostream& out, const Time& t);

/**
 * @brief Inputs a Time object from a stream.
 * @param in The input stream.
 * @param t The Time object to populate.
 * @return Reference to the input stream.
 */
istream& operator>>(istream& in, Time& t);

#endif // TIME_H_INCLUDED
