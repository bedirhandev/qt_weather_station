#include "wchart.h"

WChart::WChart(QWidget *parent) : QWidget(parent)
{
    barAxisX = new QtCharts::QBarCategoryAxis();
    barAxisX->setTitleText("");
    barAxisX->insert(0, "");

    valueAxisY = new QtCharts::QValueAxis();
    valueAxisY->setTitleText("");
    valueAxisY->setRange(0, 0);

    series = new QtCharts::QBarSeries();

    chart = new QtCharts::QChart();
    chart->addSeries(series);

    chart->addAxis(barAxisX, Qt::AlignBottom);
    chart->addAxis(valueAxisY, Qt::AlignLeft);
    chart->setTitle("");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    series->attachAxis(barAxisX);
    series->attachAxis(valueAxisY);

    barSet = new QtCharts::QBarSet("");
    barSet->insert(0, 0.0);

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void WChart::setBar(qreal value)
{
    barSet->insert(0, value);
    series->insert(0, barSet);
}

void WChart::setAxisX(const QString& value)
{
    barAxisX->insert(0, value);
}

void WChart::setMainTitle(const QString &value)
{
    chart->setTitle(value);
    barSet->setLabel(value);
}

void WChart::setTitleAxisX(const QString &value)
{
    barAxisX->setTitleText(value);
}

void WChart::setTitleAxisY(const QString &value)
{
    valueAxisY->setTitleText(value);
}

void WChart::setRange(qint16 min, qint16 max)
{
    valueAxisY->setRange(min, max);
}

WChart::~WChart()
{
    delete barAxisX;
    delete valueAxisY;
    delete barSet;
    delete series;
    delete chart;
    delete chartView;
}
