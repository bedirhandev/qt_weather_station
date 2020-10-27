/*!
 * \file wchart.h
 * \brief The logic layer.
 * \author Bedirhan Dincer
*/
#ifndef WCHART_H
#define WCHART_H

#include <QWidget>
#include <QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>
#include <QDateTimeAxis>

/*! \class WChart wchart.h "wchart.h"
 *  \brief The logic layer class.
 *
 *  In the logic layer all logic of the created charts and life-cycle are managed by this class.
 */
class WChart : public QWidget
{
    Q_OBJECT
public:
    /*! \fn WChart(QWidget *parent = nullptr, const QString& titleChart = "", const QString& titleXAxis = "", const QString& titleYAxis = "")
     * \brief Creates a basic chart.
     * \details The constructor.
     * \param parent
     * \param titleChart
     * \param titleXAxis
     * \param titleYAxis
     * \return void
     */
    explicit WChart(QWidget *parent = nullptr, const QString& titleChart = "", const QString& titleXAxis = "", const QString& titleYAxis = "");
    /*! \fn ~WChart()
     * \brief Destroys the chart widget.
     * \details The destructor.
     * \return void
     */
    ~WChart();
    /*! \fn void render()
     * \brief Renders the widget.
     * \details All aditional part of the widget like updates are managed my this method.
     * \return void
     */
    void render();
    /*! \fn void setRangeYAxis(qint16 min, qint16 max)
     * \brief Sets the range of Y-axis.
     * \return void
     */
    void setRangeYAxis(unsigned min, unsigned max);
    /*! \fn void setAxesTickCount(qint16 amount)
     * \brief Sets the amount of steps in the x-axis and y-axis.
     * \return void
     */
    void setAxesTickCount(unsigned amount);
    /*! \fn void setData(const qreal& x, const qreal& y)
     * \brief Sets the data points on the graph.
     * \return void
     */
    void setData(const qreal& x, const qreal& y);
    /*! \fn void setType(const QString& type)
     * \brief Sets the type.
     * \details This type is important because the method getRecentMeasurements(const QString& filter, const QString& date) database needs this as a filter input to get the corresponding data.
     * \note Needs a valid type which occurs in the table of the database in order to retreive data from the database.
     * \param type
     * \return void
     */
    void setType(const QString& type);
    /*! \fn const QString& getType()
     * \brief Gets the type.
     * \return const QString&
     */
    const QString& getType();
    /*! \fn const QString& getTitleChart()
     * \brief Gets the main title.
     * \return const QString&
     */
    const QString& getTitleChart();
    /*! \fn const QString& getTitleXAxis()
     * \brief Gets the title of x-axis.
     * \return const QString&
     */
    const QString& getTitleXAxis();
    /*! \fn const QString& getTitleYAxis()
     * \brief Gets the title of y-axis.
     * \return const QString&
     */
    const QString& getTitleYAxis();
    /*! \fn const qint16& getMinRangeYAxis
     * \brief Gets the starting range of the y-axis.
     * \return const qint16&
     */
    const qint16& getMinRangeYAxis();
    /*! \fn const qint16& getMaxRangeYAxis
     * \brief Gets the ending range of the y-axis.
     * \return const qint16&
     */
    const qint16& getMaxRangeYAxis();

public:
    /*! \var QtCharts::QChartView *chartView
     * \brief The layer of the widget that is going to be rendered on the screen.
     */
    QtCharts::QChartView *chartView;
private:
    /*! \var QtCharts::QValueAxis *valueAxisY
     * \brief The layer that is responsible for showing the data on the Y-axis.
     */
    QtCharts::QValueAxis *valueAxisY;
    /*! \var QtCharts::QValueAxis *valueAxisX
     * \brief The layer that is responsible for showing the data on the X-axis.
     */
    QtCharts::QDateTimeAxis *valueAxisX;
    /*! \var QtCharts::QChart *chart
     * \brief The chart stores and keeps track of all data.
     */
    QtCharts::QChart *chart;
    /*! \var QtCharts::QLineSeries *series
     * \brief Series stores all data points that is going to be presented by valueAxisX and valueAxisY.
     */
    QtCharts::QLineSeries *series;
    /*! \var QString type
     * \brief Stores the type.
     */
    /*! \var QString titleChart
     * \brief Stores the main title.
     */
    /*! \var QString titleXAxis
     * \brief Stores the title of the x-axis.
     */
    /*! \var QString titleYAxis
     * \brief Stores the title of the y-axis.
     */
    QString type, titleChart, titleXAxis, titleYAxis;
    /*! \var qint16 minRange
     * \brief Stores the minimum range of the y-axis.
     */
    /*! \var qint16 maxRange
     * \brief Stores the maximum range of the y-axis.
     */
    qint16 minRange, maxRange;
};

#endif // WCHART_H
