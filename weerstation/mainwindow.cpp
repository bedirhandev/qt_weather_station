#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>
#include <QMapIterator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tChart = new WChart();
    tChart->setMainTitle("Temperature");
    tChart->setTitleAxisX("Date");
    tChart->setRange(-50, 50);
    tChart->setTitleAxisY("Temperature [&deg;C]");

    hChart = new WChart();
    hChart->setMainTitle("Humidity");
    hChart->setTitleAxisX("Date");
    hChart->setRange(0, 100);
    hChart->setTitleAxisY("Humidity [%]");

    ui->gridLayout->addWidget(tChart->chartView, 0, 0);
    ui->gridLayout->addWidget(hChart->chartView, 0, 1);

    this->setWindowTitle("Avans weatherstation - 2020");

    m_button = new QPushButton("&Fetch", this);
    m_button->setGeometry(670, 510, 101, 31);
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

    dbase = new DBase("35.204.32.200", "root", "jwtFrfzOKfdnlsf2", "weather_station");
    dbase->getRecentMeasurements();

    hChart->setAxisX(dbase->measurements[0].date);
    hChart->setBar(dbase->measurements[0].value.toDouble());

    tChart->setAxisX(dbase->measurements[1].date);
    tChart->setBar(dbase->measurements[1].value.toDouble());
}

void MainWindow::handleButton()
{
    dbase->getRecentMeasurements();

    hChart->setAxisX(dbase->measurements[0].date);
    hChart->setBar(dbase->measurements[0].value.toDouble());

    tChart->setAxisX(dbase->measurements[1].date);
    tChart->setBar(dbase->measurements[1].value.toDouble());

    qDebug() << "Data has been fetched successfully from the cloud server";
}

MainWindow::~MainWindow()
{
    delete tChart;
    delete hChart;
    delete dbase;
    delete m_button;
    delete ui;
}

