/*!
 * \file mainwindow.h
 * \brief The presentation layer.
 * \author Bedirhan Dincer
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTime>
#include <QLabel>

#include <wchart.h>
#include <dbase.h>

/*!
 *  \addtogroup Ui
 *  @{
 */
//! Used to differentiate between the ui class from the designer and the class that implements the functionality.
QT_BEGIN_NAMESPACE
namespace Ui {
//! The main window belongs to the class of the designer.
class MainWindow;
}
QT_END_NAMESPACE // End namespace Ui
/*! @} End of Doxygen Groups*/

/*! \class MainWindow mainwindow.h "mainwindow.h"
 *  \brief The presentation layer class.
 *
 *  In the presentation layer every aspect of the lifecycle of a widget is managed by this class.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /*! \fn MainWindow(QWidget *parent = nullptr)
     * \brief Creates the main window.
     * \details The constructor.
     * \return void
     */
    MainWindow(QWidget *parent = nullptr);
    /*! \fn ~MainWindow()
     * \brief Destroys the main window.
     * \details The destructor.
     * \return void
     */
    ~MainWindow();
private:
    /*! \fn const QString getDate()
     * \brief Gets the date from the dateInputField field.
     * \return const QString
     */
    const QString getDate();
    /*! \fn void setDate(const QString& date)
     * \brief Sets the date from a given string.
     * \param date
     * \return void
     */
    void setDate(const QString& date);
    /*! \fn void setupDatabase()
     * \brief Initializes a database connection.
     * \param hostname
     * \param username
     * \param password
     * \param name
     * \return void
     */
    void setupDatabase(const QString& hostname, const QString& username, const QString& password, const QString& name);
    /*! \fn void generateSampleData(unsigned amount)
     * \brief Generates fake sample data for the measurement tbl.
     * \param amount
     * \return void
     */
    void generateSampleData(unsigned amount);
    /*! \fn void setMeasurements(WChart& chart, const QString& date)
     * \brief Gets data from the measurement tbl and puts the data into the chart.
     * \pre The value of amount must not be negative
     * \param chart
     * \param date
     * \return void
     */
    void setMeasurements(WChart& chart, const QString& date);
    /*! \fn void setupChart()
     * \brief Initializes a database connection.
     * \param titleChart
     * \param type
     * \param titleXAxis
     * \param titleYAxis
     * \param minRangeY
     * \param maxRangeY
     * \return void
     */
    void setupChart(const QString& titleChart, const QString& type, const QString& titleXAxis, const QString& titleYAxis, qint16 minRangeY, qint16 maxRangeY);
    /*! \fn void updateChart(WChart* chart)
     * \brief Updates the chart with new data and renews the gridlayout.
     * \param chart
     * \return void
     */
    void updateChart(WChart* chart);
    /*! \fn void setupButton(const QString& name, const char* slot)
     * \brief Creates a button with an event trigger.
     * \param name
     * \param slot
     * \return void
     */
    void setupButton(const QString& name, const char* slot);
    /*! \fn void updateButtons()
     * \brief Updates the buttons depending on some states.
     * \return void
     */
    void updateButtons();
    /*! \fn void addItemToGridLayout(QWidget* item, unsigned posX, unsigned posY)
     * \brief Adds a new widget to the grid layout.
     * \param item
     * \param posX
     * \param posY
     * \return void
     */
    void addItemToGridLayout(QWidget* item, unsigned posX, unsigned posY);
    /*! \fn void removeItemFromGridLayout(unsigned posX, unsigned posY)
     * \brief Removes a widget from the grid layout based on the row and column of that item.
     * \param posX
     * \param posY
     * \return void
     */
    void removeItemFromGridLayout(unsigned posX, unsigned posY);
    /*! \fn void setupWindow(const QString& windowTitle, QWidget* centralWidget)
     * \brief Sets a window title and sets the central widget of the main window.
     * \param windowTitle
     * \param centralWidget
     * \return void
     */
    void setupWindow(const QString& windowTitle, QWidget* centralWidget);

private slots:
    /*! \fn refreshButton()
     * \brief Updates the charts, buttons and the gridlayout based on the page value.
     * \return void
     */
    void refreshButton();
    /*! \fn void prevButton()
     * \brief Updates the charts, buttons and the gridlayout based on the page value.
     * \return void
     */
    void prevButton();
    /*! \fn void nextButton()
     * \brief Updates the charts, buttons and the gridlayout based on the page value.
     * \return void
     */
    void nextButton();
private:
    /*! \var QString date
     * \brief Stores the current date or date that is coming from the input field.
     */
    QString date;
    /*! \var QLineEdit *dateInputField
     * \brief The widget which behaves as a user input field.
     * \details The user input field where a date could be specified.
     */
    QLineEdit *dateInputField;
    /*! \var QVector<WChart *> charts
     * \brief A vector type data stores the view of all charts and manages the life-cycle.
     */
    QVector<WChart *> charts;
    /*! \var QVector<QPushButton *> buttons
     * \brief A vector type data stores all buttons present and manages the life-cycle.
     */
    QVector<QPushButton *> buttons;
    /*! \var DBase *dbase
     * \brief The database class instance.
     * \details Manages all income/outcome traffic with the database server.
     */
    DBase *dbase;
    /*! \var Ui::MainWindow *ui
     * \brief The MainWindow class is used to store the mainwindow.ui class generated by the Qt.
     * \details Manages the design view of the application window.
     */
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
