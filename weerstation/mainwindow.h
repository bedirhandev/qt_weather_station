#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTime>
#include <QLabel>

#include <wchart.h>
#include <dbase.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    const QString getDate();
    void setDate(const QString& date);
    void setupDatabase();
    void setupCharts();
    void setupUiElements();
    void setupWindow();
    void setMeasurements(const QVector<WChart*>& charts, const QString& date);
    void setButtons(qint16 index, bool active);
    void updateCharts();
    void clearCharts();

private slots:
    void refreshButton();
    void prevButton();
    void nextButton();
    void updateButtons();

private:
    QString date;
    QLineEdit *dateInputField;
    QVector<WChart *> charts;
    QVector<QPushButton *> buttons;
    DBase *dbase;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
