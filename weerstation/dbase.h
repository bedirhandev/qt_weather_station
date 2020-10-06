#ifndef DBASE_H
#define DBASE_H

#include <QtSql>

class DBase
{
public:
    struct measurement { QString type, value, date; } measurements[2];
private:
    QSqlDatabase m_db;
public:
    DBase(const QString& hostname, const QString& username, const QString& password, const QString& name);
    ~DBase();
    bool isOpen() const;
    void getRecentMeasurements();
};

#endif // DBASE_H
