#include "wchart.h"

WChart::WChart(QWidget *parent, const QString& titleChart, const QString& titleXAxis, const QString& titleYAxis) : QWidget(parent)
{
    this->titleChart = titleChart;
    this->titleXAxis = titleXAxis;
    this->titleYAxis = titleYAxis;

    valueAxisY = new QtCharts::QValueAxis();
    valueAxisY->setTitleText(titleYAxis);

    valueAxisX = new QtCharts::QDateTimeAxis();
    valueAxisX->setTitleText(titleXAxis);
    valueAxisX->setFormat("HH:mm");

    series = new QtCharts::QLineSeries();
    chart = new QtCharts::QChart();
    chart->setTitle(titleChart);

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void WChart::setRangeYAxis(unsigned min, unsigned max)
{
    minRange = min;
    maxRange = max;

    valueAxisY->setRange(minRange, maxRange);
}

void WChart::setType(const QString& type)
{
    this->type = type;
}

const QString& WChart::getType()
{
    return type;
}

const QString& WChart::getTitleChart()
{
    return titleChart;
}

const QString& WChart::getTitleXAxis()
{
    return titleXAxis;
}

const QString& WChart::getTitleYAxis()
{
    return titleYAxis;
}

const qint16& WChart::getMinRangeYAxis()
{
    return minRange;
}

const qint16& WChart::getMaxRangeYAxis()
{
    return maxRange;
}


void WChart::setAxesTickCount(unsigned amount)
{
    valueAxisX->setTickCount(amount);
    valueAxisY->setTickCount(amount);
}

void WChart::setData(const qreal& x, const qreal& y)
{
    series->append(x, y);
}

void WChart::render()
{
    chart->addSeries(series);

    chart->addAxis(valueAxisX, Qt::AlignBottom);
    chart->addAxis(valueAxisY, Qt::AlignLeft);

    series->attachAxis(valueAxisX);
    series->attachAxis(valueAxisY);

    chart->legend()->hide();

    chart->update();
    chartView->update();
}

WChart::~WChart()
{
    delete valueAxisX;
    delete valueAxisY;
    delete series;
    delete chart;
    delete chartView;
}
