#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;

/**
 * @class Date
 * @brief Encapsulates a calendar date (day, month, year).
 *
 * The Date class provides methods for setting and retrieving individual
 * date components, comparing dates, and formatted input/output through
 * stream operators.
 */
class Date
{
public:
    /**
     * @brief Constructs a Date with a default value.
     *
     * Initializes the date to 1 January 1900.
     */
    Date();

    /**
     * @brief Constructs a Date with specified values.
     *
     * @param day   Day of the month (1–31).
     * @param month Month of the year (1–12).
     * @param year  Year (> 0).
     */
    Date(int day, int month, int year);

    /**
     * @brief Sets the date to the specified values.
     *
     * @param day   Day of the month (1–31).
     * @param month Month of the year (1–12).
     * @param year  Year (> 0).
     *
     * @throws std::invalid_argument If any component is outside its valid range.
     */
    void SetDate(int day, int month, int year);

    /**
     * @brief Returns the day of the month.
     * @return Integer representing the day.
     */
    int GetDay() const;

    /**
     * @brief Returns the month number.
     * @return Integer between 1 and 12.
     */
    int GetMonth() const;

    /**
     * @brief Returns the year.
     * @return Integer representing the year.
     */
    int GetYear() const;

    /**
     * @brief Returns the full month name.
     * @return A string such as "January".
     */
    string GetMonthNames() const;

    /**
     * @brief Compares two dates chronologically.
     *
     * @param other The Date to compare with.
     * @return True if this date occurs earlier than @p other.
     */
    bool operator<(const Date& other) const;

    /**
     * @brief Checks if two dates are identical.
     *
     * @param other The Date to compare with.
     * @return True if both dates have the same day, month, and year.
     */
    bool operator==(const Date& other) const;

private:
    int m_day;    ///< Day of the month.
    int m_month;  ///< Month number (1–12).
    int m_year;   ///< Year value.
};

/**
 * @brief Extracts a Date from an input stream.
 *
 * Expected input format:
 * @code
 * day month year
 * @endcode
 *
 * @param input Stream to read from.
 * @param date  Date object to populate.
 * @return Reference to the input stream.
 */
istream& operator>>(istream& input, Date& date);

/**
 * @brief Inserts a formatted Date into an output stream.
 *
 * Output format:
 * @code
 * day MonthName year
 * // Example: 3 March 2025
 * @endcode
 *
 * @param os    Stream to write to.
 * @param date  Date object to output.
 * @return Reference to the output stream.
 */
ostream& operator<<(ostream& os, const Date& date);

#endif // DATE_H_INCLUDED
