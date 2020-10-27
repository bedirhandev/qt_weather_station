#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>
#include <QMapIterator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    setupDatabase("35.204.32.200", "root", "jwtFrfzOKfdnlsf2", "weather_station");
    //generateSampleData(123);

    ui->gridLayout->parentWidget()->hide();

    setupChart("Temperature", "temperature", "Time [m]", "Temperature [c]", 0, 40);
    setupChart("Humidity", "humidity", "Time [m]", "Humidity [%]", 0, 100);
    setupChart("Lux", "lux", "Time [m]", "Lux [lx]", 0, 1000);

    addItemToGridLayout(charts[0]->chartView, 0, 0);
    addItemToGridLayout(charts[1]->chartView, 0, 1);
    addItemToGridLayout(charts[2]->chartView, 1, 0);

    setupButton("Back", SLOT(prevButton()));
    setupButton("Next", SLOT(nextButton()));
    setupButton("Update", SLOT(refreshButton()));

    addItemToGridLayout(buttons[0], 2, 0);
    addItemToGridLayout(buttons[1], 2, 1);
    addItemToGridLayout(buttons[2], 3, 0);

    dateInputField = new QLineEdit();
    dateInputField->setText(date);

    addItemToGridLayout(dateInputField, 3, 1);

    updateButtons();

    ui->gridLayout->parentWidget()->show();

    setupWindow("Weather station", ui->gridLayoutWidget);
}

void MainWindow::setupWindow(const QString& windowTitle, QWidget* centralWidget)
{
    setCentralWidget(centralWidget);
    setWindowTitle(windowTitle);
}

void MainWindow::setupDatabase(const QString& hostname, const QString& username, const QString& password, const QString& name)
{
    dbase = new DBase(hostname, username, password, name);
}

void MainWindow::generateSampleData(unsigned amount)
{
    dbase->generateSampleData(amount);
}

void MainWindow::addItemToGridLayout(QWidget* chart, unsigned posX, unsigned posY)
{
    ui->gridLayout->addWidget(chart, posX, posY);
}

void MainWindow::removeItemFromGridLayout(unsigned posX, unsigned posY)
{
    QLayoutItem* item = ui->gridLayout->itemAtPosition(posX, posY);
    ui->gridLayout->removeItem(item);
    delete item->widget();
}

void MainWindow::setupChart(const QString& titleChart, const QString& type, const QString& titleXAxis, const QString& titleYAxis, qint16 minRangeY, qint16 maxRangeY)
{
    charts.append(new WChart(nullptr, titleChart, titleXAxis, titleYAxis));
    charts.back()->setType(type);
    charts.back()->setRangeYAxis(minRangeY, maxRangeY);
    setMeasurements(*charts.back(), getDate());
}

void MainWindow::setupButton(const QString& name, const char* slot) // unsigned posX, unsigned posY,
{
    buttons.append(new QPushButton("&" + name, this));
    connect(buttons.back(), SIGNAL (released()), this, slot);
    buttons.back()->hide();
}

void MainWindow::refreshButton()
{
    dbase->page = 0;

    for(int i = 0; i < charts.length(); i++)
    {
        updateChart(charts[i]);
    }

    updateButtons();
}

void MainWindow::prevButton()
{
    dbase->page -= 1;

    for(int i = 0; i < charts.length(); i++)
    {
        updateChart(charts[i]);
    }

    updateButtons();
}

void MainWindow::nextButton()
{
    dbase->page += 1;

    for(int i = 0; i < charts.length(); i++)
    {
        updateChart(charts[i]);
    }

    updateButtons();
}

void MainWindow::updateChart(WChart* chart)
{
    ui->gridLayout->parentWidget()->hide();
    WChart* tempChart = new WChart(nullptr, chart->getTitleChart(), chart->getTitleXAxis(), chart->getTitleYAxis());
    tempChart->setType(chart->getType());
    tempChart->setRangeYAxis(chart->getMinRangeYAxis(), chart->getMaxRangeYAxis());
    setMeasurements(*tempChart, getDate());
    ui->gridLayout->replaceWidget(chart->chartView, tempChart->chartView);
    std::replace (charts.begin(), charts.end(), chart, tempChart);
    ui->gridLayout->parentWidget()->show();
    delete chart;
}

void MainWindow::updateButtons()
{
    if(dbase->page < 0)
    {
        buttons[0]->show();
        buttons[1]->show();
    }

    if(dbase->page == 0)
    {
        buttons[0]->show();
        buttons[1]->hide();
        buttons[2]->show();
    }

    if((dbase->totalMeasurements + ((dbase->page - 1) * 60)) <= 0)
    {
        buttons[0]->hide();
    }
}

const QString MainWindow::getDate()
{
    if(dateInputField && !dateInputField->text().isEmpty()) date = dateInputField->text();
    return date;
}

void MainWindow::setDate(const QString& date)
{
    this->date = date;
}

void MainWindow::setMeasurements(WChart& chart, const QString& date)
{
    qint16 nMeasurements, rangeAxes = 0;
    QDateTime datetime;

    dbase->getRecentMeasurements(chart.getType(), date);

    nMeasurements = dbase->range;
    rangeAxes = (nMeasurements < 15) ? nMeasurements : 15;
    chart.setAxesTickCount(rangeAxes);

    for(int j = 0; j < nMeasurements; j++)
    {
        datetime = QDateTime::fromString(dbase->measurements[j].date, "yyyy-MM-dd HH:mm:ss.zzz");
        chart.setData(datetime.toMSecsSinceEpoch(), dbase->measurements[j].value.toDouble());
    }

    chart.render();
}

MainWindow::~MainWindow()
{
    delete dbase;
    delete ui;
    delete dateInputField;
}

