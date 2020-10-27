#ifndef DBASE_H
#define DBASE_H

#include <QtSql>

class DBase
{
public:
    struct measurement { QString type, value, date; } measurements[60];
    int totalMeasurements, page, range;
private:
    QSqlDatabase m_db;
public:
    DBase(const QString& hostname, const QString& username, const QString& password, const QString& name);
    ~DBase();
    bool isOpen() const;
    void getRecentMeasurements(const QString& filter, const QString& date);
    void generateSampleData(unsigned amount);
    double fRand(double fMin, double fMax);
    double round(double var);
};

#endif // DBASE_H
