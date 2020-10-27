/*!
 * \file mainwindow.cpp
 * \brief Presentation layer. The view is created here and updated.
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /*! \fn const QString getDate()
     * \brief Gets the date from the dateInputField field.
     * \param none
     * \return const QString
     */
    const QString getDate();
    /*! \fn void setDate(const QString& date)
     * \brief Sets the date from a given string.
     * \param const QString& date
     * \return void
     */
    void setDate(const QString& date);
    /*! \fn void setupDatabase()
     * \brief Initializes a database connection.
     * \param none
     * \return void
     */
    void setupDatabase(const QString& hostname, const QString& username, const QString& password, const QString& name);
    void generateSampleData(unsigned amount);
    void setMeasurements(WChart& chart, const QString& date);
    void setupChart(const QString& titleChart, const QString& type, const QString& titleXAxis, const QString& titleYAxis, qint16 minRangeY, qint16 maxRangeY);
    void updateChart(WChart* chart);
    void setupButton(const QString& name, const char* slot);
    void updateButtons();
    void addItemToGridLayout(QWidget* item, unsigned posX, unsigned posY);
    void removeItemFromGridLayout(unsigned posX, unsigned posY);
    void setupWindow(const QString& windowTitle, QWidget* centralWidget);

private slots:
    void refreshButton();
    void prevButton();
    void nextButton();

private:
    QString date;
    QLineEdit *dateInputField;
    QVector<WChart *> charts;
    QVector<QPushButton *> buttons;
    DBase *dbase;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
