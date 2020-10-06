#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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

private slots:
    void handleButton();

private:
    WChart *tChart;
    WChart *hChart;
    DBase *dbase;
    Ui::MainWindow *ui;
    QPushButton *m_button;
};
#endif // MAINWINDOW_H
