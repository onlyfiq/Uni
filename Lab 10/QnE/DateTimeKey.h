#ifndef DATETIMEKEY_H_INCLUDED
#define DATETIMEKEY_H_INCLUDED

#include "Date.h"
#include "Time.h"

/**
 * @struct DateTimeKey
 * @brief Combines Date and Time into a single sortable key
 *        for use inside the BST.
 *
 * Sorting priority:
 *   1. Year
 *   2. Month
 *   3. Day
 *   4. Hour
 *   5. Minute
 *
 * This guarantees unique ordering for every WeatherRec entry.
 */
struct DateTimeKey
{
    int year;
    int month;
    int day;
    int hour;
    int minute;

    DateTimeKey() :
        year(0), month(0), day(0), hour(0), minute(0)
    {
    }

    DateTimeKey(const Date &d, const Time &t) :
        year(d.GetYear()),
        month(d.GetMonth()),
        day(d.GetDay()),
        hour(t.GetHour()),
        minute(t.GetMinute())
    {
    }

    /**
     * @brief Comparison operator for BST ordering
     */
    bool operator<(const DateTimeKey &other) const
    {
        if (year != other.year)
        {
            return year < other.year;
        }
        if (month != other.month)
        {
            return month < other.month;
        }
        if (day != other.day)
        {
            return day < other.day;
        }
        if (hour != other.hour)
        {
            return hour < other.hour;
        }
        return minute < other.minute;
    }

    /**
     * @brief Equality operator (optional, but useful)
     */
    bool operator==(const DateTimeKey &other) const
    {
        return year == other.year &&
               month == other.month &&
               day == other.day &&
               hour == other.hour &&
               minute == other.minute;
    }
};

#endif // DATETIMEKEY_H_INCLUDED
