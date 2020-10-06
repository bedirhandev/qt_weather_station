#include "dbase.h"

#include <QMap>

struct measurement;

DBase::DBase(const QString& hostname, const QString& username, const QString& password, const QString& name)
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

void DBase::getRecentMeasurements()
{
    if(isOpen()) {
        QSqlQuery sql_query("SELECT * FROM measurement ORDER BY id DESC LIMIT 2;");

        qint16 measurementId = sql_query.record().indexOf("id");
        qint16 measurementType = sql_query.record().indexOf("type");
        qint16 measurementValue = sql_query.record().indexOf("value");
        qint16 measurementDate = sql_query.record().indexOf("date");

        qint16 index = 0;

        while (sql_query.next())
        {
            QString id, type, value, date;
            id = sql_query.value(measurementId).toString();
            type = sql_query.value(measurementType).toString();
            value = sql_query.value(measurementValue).toString();
            date = sql_query.value(measurementDate).toString();

            measurements[index] = { type, value, date };
            index++;
        }
    }
}

DBase::~DBase()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DBase::isOpen() const
{
    return m_db.isOpen();
}
