#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;

/**
 * @class Date
 * @brief Represents a calendar date (day, month, year).
 *
 * The Date class provides getters and setters for the day, month,
 * and year. It also supports input/output stream operations.
 */
class Date
{
public:
    /**
     * @brief Default constructor.
     *
     * Initializes the date to 1/1/1900.
     */
    Date();

    /**
     * @brief Parameterized constructor.
     *
     * @param m_day Day of the month (1-31).
     * @param m_month Month (1-12).
     * @param m_year Year (>0).
     */
    Date(int day, int month, int year);

    /**
     * @brief Sets the date.
     *
     * @param day Day of the month (1-31).
     * @param month Month (1-12).
     * @param year Year (>0).
     *
     * @throws invalid_argument if day, month, or year are out of valid range.
     */
    void SetDate(int day, int month, int year);

    /**
     * @brief Retrieves the day.
     * @return Day of the month.
     */
    int GetDay() const;

    /**
     * @brief Retrieves the month.
     * @return Month number.
     */
    int GetMonth() const;

    /**
     * @brief Retrieves the year.
     * @return Year.
     */
    int GetYear() const;

    /**
     * @brief Retrieves the month name.
     * @return Name of the month (e.g., "January").
     */
    string GetMonthNames() const;

    bool operator<(const Date& other) const;

    bool operator==(const Date& other) const;

private:
    int m_day;   ///< Day of the month
    int m_month; ///< Month (1-12)
    int m_year;  ///< Year
};

/**
 * @brief Reads a Date object from an input stream.
 *
 * Expected format:
 * day month year
 *
 * @param input Input stream to read from.
 * @param date Date object to populate.
 * @return Reference to the input stream.
 */
istream &operator>>(istream &input, Date &date);

/**
 * @brief Writes a Date object to an output stream.
 *
 * Output format: day MonthName year (e.g., 3 March 2025)
 *
 * @param os Output stream to write to.
 * @param date Date object to output.
 * @return Reference to the output stream.
 */
ostream &operator<<(ostream &os, const Date &date);

#endif // DATE_H_INCLUDED
