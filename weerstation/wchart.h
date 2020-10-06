#ifndef WCHART_H
#define WCHART_H

#include <QWidget>
#include <QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>

class WChart : public QWidget
{
    Q_OBJECT
public:
    explicit WChart(QWidget *parent = nullptr);
    ~WChart();

    void setBar(qreal value);
    void setTitleAxisX(const QString& value);
    void setTitleAxisY(const QString& value);
    void setMainTitle(const QString& value);
    void setRange(qint16 min, qint16 max);
    void setAxisX(const QString& value);

public:
    QtCharts::QChartView *chartView;

private:
    QtCharts::QValueAxis* valueAxisY;
    QtCharts::QBarCategoryAxis* barAxisX;
    QtCharts::QBarSet* barSet;
    QtCharts::QChart *chart;
    QtCharts::QBarSeries* series;
};

#endif // WCHART_H
