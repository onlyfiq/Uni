#ifndef WEATHERREC_H_INCLUDED
#define WEATHERREC_H_INCLUDED

#include "Date.h"
#include "Time.h"
#include "DateTimeKey.h"
#include <iostream>

using std::ostream;

/**
 * @class WeatherRec
 * @brief Represents a single weather observation.
 *
 * A WeatherRec object stores:
 *   - The date of observation
 *   - The time of observation
 *   - Wind speed (m/s)
 *   - Solar radiation (W/m²)
 *   - Ambient air temperature (°C)
 *
 * Each record can generate a DateTimeKey, which provides a unique
 * and fully sortable timestamp suitable for use as the key in a BST.
 */
class WeatherRec
{
public:

    /**
     * @brief Default constructor.
     *
     * Initializes:
     *   - Date and Time to their default-constructed values
     *   - Wind speed, solar radiation, and temperature to 0.0
     */
    WeatherRec();

    /**
     * @brief Parameterized constructor for creating a complete weather record.
     *
     * @param d Date of the observation.
     * @param t Time of the observation.
     * @param speed Wind speed in m/s.
     * @param solarRad Solar radiation in W/m².
     * @param ambAirTemp Ambient air temperature in °C.
     */
    WeatherRec(const Date& d, const Time& t, float speed, float solarRad, float ambAirTemp);

    /** @brief Returns the observation date. */
    const Date& GetDate() const;

    /** @brief Returns the observation time. */
    const Time& GetTime() const;

    /**
     * @brief Returns the month of the observation.
     * @return Integer in the range 1–12.
     */
    int GetMonth() const;

    /**
     * @brief Returns the year of the observation.
     */
    int GetYear() const;

    /** @brief Returns the wind speed in m/s. */
    float GetSpeed() const;

    /** @brief Returns the solar radiation in W/m². */
    float GetSolarRad() const;

    /** @brief Returns the ambient air temperature in °C. */
    float GetAmbAirTemp() const;

    /** @brief Sets the observation date. */
    void SetDate(const Date& d);

    /** @brief Sets the observation time. */
    void SetTime(const Time& t);

    /** @brief Sets the wind speed in m/s. */
    void SetSpeed(float speed);

    /** @brief Sets the solar radiation in W/m². */
    void SetSolarRad(float solarRad);

    /** @brief Sets the air temperature in °C. */
    void SetAmbAirTemp(float ambAirTemp);

    /**
     * @brief Generates a sortable key combining date and time.
     *
     * The DateTimeKey sorts in this order:
     *   1. Year
     *   2. Month
     *   3. Day
     *   4. Hour
     *   5. Minute
     *
     * @return A DateTimeKey object representing the timestamp of this record.
     */
    DateTimeKey GetDateTimeKey() const;

private:
    Date m_date;       /**< Observation date. */
    Time m_time;       /**< Observation time. */
    float m_speed;     /**< Wind speed (m/s). */
    float m_solarRad;  /**< Solar radiation (W/m²). */
    float m_airTemp;   /**< Ambient air temperature (°C). */
};

/**
 * @brief Stream insertion operator for WeatherRec.
 *
 * Outputs the record in a readable format for debugging, logs,
 * and text-based displays.
 *
 * @param os Output stream.
 * @param wr WeatherRec instance to print.
 * @return Reference to the modified output stream.
 */
ostream& operator<<(ostream& os, const WeatherRec& wr);

#endif // WEATHERREC_H_INCLUDED
