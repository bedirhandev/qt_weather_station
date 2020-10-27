#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>
#include <QMapIterator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    setupDatabase();
    setupCharts();
    setupUiElements();
    setupWindow();
}

void MainWindow::setupDatabase()
{
    dbase = new DBase("35.204.32.200", "root", "jwtFrfzOKfdnlsf2", "weather_station");
    //dbase->generateSampleData(123);
}

void MainWindow::setupCharts()
{
    charts.insert(0, new WChart(nullptr, "Temperature", "Time [m]", "Temperature [c]"));
    charts[0]->setType("temperature");
    charts[0]->setRangeYAxis(0, 40);

    charts.insert(1, new WChart(nullptr, "Humidity", "Time [m]", "Humidity [%]"));
    charts[1]->setType("humidity");
    charts[1]->setRangeYAxis(0, 100);

    charts.insert(2, new WChart(nullptr, "Lux", "Time [m]", "Lux [lx]"));
    charts[2]->setType("lux");
    charts[2]->setRangeYAxis(0, 1000);

    setMeasurements(charts, getDate());

    ui->gridLayout->addWidget(charts[0]->chartView, 0, 0);
    ui->gridLayout->addWidget(charts[1]->chartView, 0, 1);
    ui->gridLayout->addWidget(charts[2]->chartView, 1, 0);

    ui->gridLayout->parentWidget()->show();
}

void MainWindow::setupUiElements()
{
    buttons.append(new QPushButton("&Back", this));
    buttons.append(new QPushButton("&Next", this));
    buttons.append(new QPushButton("&Update", this));

    connect(buttons[0], SIGNAL (released()), this, SLOT (prevButton()));
    connect(buttons[1], SIGNAL (released()), this, SLOT (nextButton()));
    connect(buttons[2], SIGNAL (released()), this, SLOT (refreshButton()));

    ui->gridLayout->addWidget(buttons[0], 2, 0);
    ui->gridLayout->addWidget(buttons[1], 2, 1);
    ui->gridLayout->addWidget(buttons[2], 3, 0);

    for(int i = 0; i < 2; i++) setButtons(i, false);

    dateInputField = new QLineEdit();
    dateInputField->setText(date);

    ui->gridLayout->addWidget(dateInputField, 3, 1);

    updateButtons();
}

void MainWindow::refreshButton()
{
    dbase->page = 0;
    clearCharts();
    setupCharts();
    updateButtons();
}

void MainWindow::prevButton()
{
    dbase->page -= 1;
    clearCharts();
    setupCharts();
    updateButtons();
}

void MainWindow::nextButton()
{
    dbase->page += 1;
    clearCharts();
    setupCharts();
    updateButtons();
}

void MainWindow::updateButtons()
{
    if(dbase->page < 0) for(int i = 0; i < 2; i++) setButtons(i, true);
    if(dbase->page == 0) for(int i = 0; i < 2; i++) setButtons(i, !i);
    if((dbase->totalMeasurements + ((dbase->page - 1) * 60)) <= 0) setButtons(0, false);
}

void MainWindow::setButtons(qint16 index, bool active)
{
    if(active) buttons[index]->show();
    else buttons[index]->hide();
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

void MainWindow::setupWindow()
{
    setCentralWidget(ui->gridLayoutWidget);
    setWindowTitle("Weather station");
}

void MainWindow::clearCharts()
{
    ui->gridLayout->parentWidget()->hide();

    QVector<QLayoutItem *> gridLayoutItems =
    {
        ui->gridLayout->itemAtPosition(0, 0),
        ui->gridLayout->itemAtPosition(0, 1),
        ui->gridLayout->itemAtPosition(1, 0),
    };

    for(int i = 0; i < gridLayoutItems.length(); i++)
    {
        ui->gridLayout->removeItem(gridLayoutItems[i]);
        delete gridLayoutItems[i]->widget();
    }

    gridLayoutItems.clear();
    charts.clear();
}

void MainWindow::setMeasurements(const QVector<WChart*>& charts, const QString& date)
{
    qint16 nMeasurements, rangeAxes = 0;
    QDateTime datetime;

    for(int i = 0; i < charts.length(); i++)
    {
        dbase->getRecentMeasurements(charts[i]->getType(), date);

        nMeasurements = dbase->range;
        rangeAxes = (nMeasurements < 15) ? nMeasurements : 15;
        charts[i]->setAxesTickCount(rangeAxes);

        for(int j = 0; j < nMeasurements; j++)
        {
            datetime = QDateTime::fromString(dbase->measurements[j].date, "yyyy-MM-dd HH:mm:ss.zzz");
            charts[i]->setData(datetime.toMSecsSinceEpoch(), dbase->measurements[j].value.toDouble());
        }

        charts[i]->render();
    }
}

MainWindow::~MainWindow()
{
    delete dbase;
    delete ui;
    delete dateInputField;
}

