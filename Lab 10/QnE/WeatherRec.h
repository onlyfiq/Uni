#ifndef WEATHERREC_H_INCLUDED
#define WEATHERREC_H_INCLUDED

#include "Date.h"
#include "Time.h"
#include <iostream>

using std::ostream;

/**
 * @class WeatherRec
 * @brief Represents a single weather record including date, time, wind speed, solar radiation, and air temperature.
 */
class WeatherRec
{
public:
    /**
     * @brief Default constructor.
     *
     * Initializes all numeric values to 0 and date/time to default.
     */
    WeatherRec();

    /**
     * @brief Parameterized constructor.
     * @param d Date of the record.
     * @param t Time of the record.
     * @param speed Wind speed in m/s.
     * @param solarRad Solar radiation in W/m^2.
     * @param ambAirTemp Ambient air temperature in degrees Celsius.
     */
    WeatherRec(const Date& d, const Time& t, float speed, float solarRad, float ambAirTemp);

    /**
     * @brief Retrieves the date of the record.
     * @return Reference to the Date object.
     */
    const Date& GetDate() const;

    /**
     * @brief Retrieves the time of the record.
     * @return Reference to the Time object.
     */
    const Time& GetTime() const;

    /**
     * @brief Retrieves the month of the record.
     * @return Month number (1-12).
     */
    int GetMonth() const;

    /**
     * @brief Retrieves the year of the record.
     * @return Year.
     */
    int GetYear() const;

    /**
     * @brief Retrieves the wind speed.
     * @return Wind speed in m/s.
     */
    float GetSpeed() const;

    /**
     * @brief Retrieves the solar radiation.
     * @return Solar radiation in W/m^2.
     */
    float GetSolarRad() const;

    /**
     * @brief Retrieves the ambient air temperature.
     * @return Air temperature in degrees Celsius.
     */
    float GetAmbAirTemp() const;

    /**
     * @brief Sets the date of the record.
     * @param d Date object to set.
     */
    void SetDate(const Date& d);

    /**
     * @brief Sets the time of the record.
     * @param t Time object to set.
     */
    void SetTime(const Time& t);

    /**
     * @brief Sets the wind speed.
     * @param speed Wind speed in m/s.
     */
    void SetSpeed(float speed);

    /**
     * @brief Sets the solar radiation.
     * @param solarRad Solar radiation in W/m^2.
     */
    void SetSolarRad(float solarRad);

    /**
     * @brief Sets the ambient air temperature.
     * @param ambAirTemp Air temperature in degrees Celsius.
     */
    void SetAmbAirTemp(float ambAirTemp);

    /**
     * @brief Generates a DateTimeKey for BST insertion.
     */
    DateTimeKey GetDateTimeKey() const;

private:
    Date m_date;       /**< Date of the record */
    Time m_time;       /**< Time of the record */
    float m_speed;     /**< Wind speed in m/s */
    float m_solarRad;  /**< Solar radiation in W/m^2 */
    float m_airTemp;   /**< Ambient air temperature in Celsius */
};

/**
 * @brief Outputs a WeatherRec object to a stream.
 * @param os Output stream.
 * @param wr WeatherRec object to output.
 * @return Reference to the output stream.
 */
ostream& operator<<(ostream& os, const WeatherRec& wr);

#endif // WEATHERREC_H_INCLUDED
