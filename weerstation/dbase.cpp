#include "dbase.h"

#include <QMap>

struct measurement;

// create the connection with the database
DBase::DBase(const QString& hostname, const QString& username, const QString& password, const QString& name) : totalMeasurements(0), page(0)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(hostname);
    m_db.setDatabaseName(name);
    m_db.setUserName(username);
    m_db.setPassword(password);

    if(!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

double DBase::fRand(double fMin, double fMax)
{
    // Random number between low and high
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double DBase::round(double var)
{
    // 37.66666 * 100 =3766.66
    // 3766.66 + .5 =3767.16    for rounding off value
    // then type cast to int so value is 3767
    // then divided by 100 so the value converted into 37.67
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
}

void DBase::generateSampleData(unsigned int amount)
{
    if(isOpen())
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();

        std::string tempDateTime;
        QString formattedDateTime;

        QTime time = QTime::currentTime();
        srand((uint)time.msec());

        double lux, temperature, humidity;

        // sample data measurement per minute.
        for(unsigned i = 0; i < amount; i++)
        {
            tempDateTime = currentDateTime.addSecs(60 * i).toString(Qt::ISODate).toStdString();
            formattedDateTime = QString::fromStdString(tempDateTime.replace(tempDateTime.find("T"), 1, " "));

            temperature = round(fRand(20.0, 30.0));
            lux = round(fRand(150.0, 350.0));
            humidity = round(fRand(50.0, 80.0));

            QString query = QString("INSERT INTO measurement (type, value, date) VALUES ('%1', '%2', '%3')")
                    .arg("lux", QString::number(lux), formattedDateTime);
            QSqlQuery sql_query(query);

            query = QString("INSERT INTO measurement (type, value, date) VALUES ('%1', '%2', '%3')")
                    .arg("temperature", QString::number(temperature), formattedDateTime);
            QSqlQuery sql_query_2(query);

            query = QString("INSERT INTO measurement (type, value, date) VALUES ('%1', '%2', '%3')")
                    .arg("humidity", QString::number(humidity), formattedDateTime);
            QSqlQuery sql_query_3(query);
        }
    }
}

// get the measurements with a prefined query
void DBase::getRecentMeasurements(const QString& filter, const QString& date)
{
    if(isOpen()) {
        for(int i = 0; i < 60; i++) measurements[i] = {};

        QDate Date = QDate::fromString(date, "yyyy-MM-dd");

        QSqlQuery sql_query_count("SELECT COUNT(*) FROM measurement WHERE type = '" + filter +
                                  "' AND cast(date as date) = '" + Date.toString("yyyy-MM-dd") + "';");

        if(sql_query_count.next()) totalMeasurements = sql_query_count.value(0).toInt();

        if(totalMeasurements == 0) return;

        if(page > 0) page = 0;
        if((totalMeasurements + (page * 60)) <= 0) page++;

        int maxRange = 0;
        maxRange += totalMeasurements + (page * 60);
        int minRange = (maxRange < 60) ? 0 : maxRange - 60;

        range = maxRange - minRange;

        QSqlQuery sql_query("SELECT * FROM measurement WHERE type = '" + filter +
                            "' AND cast(date as date) = '" + Date.toString("yyyy-MM-dd") +
                            "' ORDER BY id LIMIT " + QString::number(minRange) + ", " + QString::number(maxRange) + ";");

        qint16 measurementId = sql_query.record().indexOf("id");
        qint16 measurementType = sql_query.record().indexOf("type");
        qint16 measurementValue = sql_query.record().indexOf("value");
        qint16 measurementDate = sql_query.record().indexOf("date");

        qint16 index = 0;
        QString id, type, value, date;
        std::string tempDate;

        while (sql_query.next())
        {
            id = sql_query.value(measurementId).toString();
            type = sql_query.value(measurementType).toString();
            value = sql_query.value(measurementValue).toString();
            date = sql_query.value(measurementDate).toString();

            tempDate = date.toStdString();
            date.replace(tempDate.find("T"), 1, " ");

            if(index < 60) measurements[index] = { type, value, date };
            index++;
        }
    }
}

// close the connection when this object gets deleted
DBase::~DBase()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

// check if db is still open
bool DBase::isOpen() const
{
    return m_db.isOpen();
}
