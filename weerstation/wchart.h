#ifndef WCHART_H
#define WCHART_H

#include <QWidget>
#include <QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>
#include <QDateTimeAxis>

class WChart : public QWidget
{
    Q_OBJECT
public:
    explicit WChart(QWidget *parent = nullptr, const QString& titleChart = "", const QString& titleXAxis = "", const QString& titleYAxis = "");
    ~WChart();
    void render();
    void setRangeYAxis(qint16 min, qint16 max);
    void setAxesTickCount(qint16 amount);
    void setData(const qreal& x, const qreal& y);
    void setType(const QString& type);
    const QString& getType();
    const QString& getTitleChart();
    const QString& getTitleXAxis();
    const QString& getTitleYAxis();
    const qint16& getMinRange();
    const qint16& getMaxRange();

public:
    QtCharts::QChartView *chartView;
private:
    QtCharts::QValueAxis *valueAxisY;
    QtCharts::QDateTimeAxis *valueAxisX;
    QtCharts::QChart *chart;
    QtCharts::QLineSeries *series;
    QString type, titleChart, titleXAxis, titleYAxis;
    qint16 minRange, maxRange;
};

#endif // WCHART_H
