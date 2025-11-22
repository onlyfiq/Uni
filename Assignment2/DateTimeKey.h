#ifndef DATETIMEKEY_H_INCLUDED
#define DATETIMEKEY_H_INCLUDED

#include "Date.h"
#include "Time.h"

/**
 * @struct DateTimeKey
 * @brief A sortable key combining Date and Time for BST indexing.
 *
 * This structure converts a Date and Time into a strict ordering key
 * used by the BST when inserting or searching for weather records.
 *
 * Ordering priority:
 *   1. Year
 *   2. Month
 *   3. Day
 *   4. Hour
 *   5. Minute
 *
 * This provides a unique chronological ordering for every WeatherRec entry,
 * ensuring deterministic placement inside the binary search tree.
 */
struct DateTimeKey
{
public:
    int year;    ///< Year component
    int month;   ///< Month component (1–12)
    int day;     ///< Day component (1–31)
    int hour;    ///< Hour component (0–23)
    int minute;  ///< Minute component (0–59)

    /**
     * @brief Default constructor.
     *
     * Initializes all fields to zero. Primarily used for placeholder keys.
     */
    DateTimeKey()
        : year(0), month(0), day(0), hour(0), minute(0)
    {
    }

    /**
     * @brief Constructs a key directly from a Date and Time object.
     * @param d Date component.
     * @param t Time component.
     */
    DateTimeKey(const Date& d, const Time& t)
        : year(d.GetYear()),
          month(d.GetMonth()),
          day(d.GetDay()),
          hour(t.GetHours()),
          minute(t.GetMinutes())
    {
    }

    /**
     * @brief Strict weak ordering based on chronological time.
     *
     * Used by the BST to determine left/right placement.
     *
     * @param other Key to compare with.
     * @return True if this key is chronologically earlier than @p other.
     */
    bool operator<(const DateTimeKey& other) const
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
     * @brief Reverse chronological comparison.
     * @param other Key to compare with.
     * @return True if this key is later than @p other.
     */
    bool operator>(const DateTimeKey& other) const
    {
        return other < *this;
    }

    /**
     * @brief Equality comparison.
     * @param other Key to compare with.
     * @return True if all date/time components match exactly.
     */
    bool operator==(const DateTimeKey& other) const
    {
        return year   == other.year &&
               month  == other.month &&
               day    == other.day &&
               hour   == other.hour &&
               minute == other.minute;
    }
};

#endif // DATETIMEKEY_H_INCLUDED
