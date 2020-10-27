/*!
 * \file dbase.h
 * \brief The data layer.
 * \author Bedirhan Dincer
*/
#ifndef DBASE_H
#define DBASE_H

#include <QtSql>

/*! \class DBase dbase.h "dbase.h"
 *  \brief The data layer class.
 *
 *  In the data layer every aspect of communication with the database is managed by this class.
 */
class DBase
{
public:
    /*! \var struct measurement { QString type, value, date; } measurements[60]
     * \brief Holds 60 samples of measurement data
     * \details The data is stored in this array before it is passed down to the chart widget.
     */
    struct measurement
    {
        /*! \var QString type
         * \brief Stores the type of the measurement data.
        */
        QString type;
        /*! \var QString value
         \brief Stores the value of the measurement data.
         */
        QString value;
        /*! \var QString date
         \brief Stores the date of the measurement data.
         */
        QString date;
    } measurements[60];
    /*! \var int totalMeasurements
     * \brief Holds the data of the total amount of measurements that is currently available.
     */
    int totalMeasurements;
    /*! \var int page
     * \brief Holds the current page the view layer has to show.
     * \details The page indicates that 60 measurements may be shown by the view layer.
     */
    int page;
    /*! \var int range
     * \brief As the data shrinks less measurements are available. The page calculates how many measurements on the page are allowed to show.
     */
    int range;
private:
    /*! \var QSqlDatabase m_db
     * \brief The database variable which deals with the database server.
     */
    QSqlDatabase m_db;
public:
    /*! \fn DBase(const QString& hostname, const QString& username, const QString& password, const QString& name)
     * \brief Creates the database connection.
     * \details The constructor.
     * \return void
     */
    DBase(const QString& hostname, const QString& username, const QString& password, const QString& name);
    /*! \fn ~DBase()
     * \brief Destroys the database connection.
     * \details The destructor.
     * \return void
     */
    ~DBase();
    /*! \fn bool isOpen() const
     * \brief Checks if the connection is made with the database server.
     * \return boolean
     */
    bool isOpen() const;
    /*! \fn void getRecentMeasurements(const QString& filter, const QString& date)
     * \brief Gets the measurements from the database based on the type and date values.
     * \return void
     */
    void getRecentMeasurements(const QString& filter, const QString& date);
    /*! \fn void generateSampleData(unsigned amount)
     * \brief Generates fake sample data to work with some data.
     * \warning Only for testing purposes.
     * \pre Date must be a valid date in the format ex: 2020-10-25.
     * \param amount
     * \return void
     */
    void generateSampleData(unsigned amount);
    /*! \fn double fRand(double fMin, double fMax)
     * \brief Generates random value between fMin and fMax.
     * \warning Only for testing purposes.
     * \pre Date must be a valid date in the format of for e.g.: 2020-10-25.
     * \param fMin
     * \param fMax
     * \return void
     */
    double fRand(double fMin, double fMax);

    /*! \fn double round(double var)
     * \brief Round-up a double value.
     * \param var
     * \return double
     */
    double round(double var);
};

#endif // DBASE_H
