#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTableView>

#include "constants.h"
#include "dictmodel.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TM Viewer Alpha");
    ui->statusBar->showMessage(QString("Welcome to TM Viewer!"));

    // Initialize the data manager instance
    dataMgr = new DataManager;

    // Create the Dictionary tab in Control Panel
    dictModel = new DictModel;
    dictModel->setMap(dataMgr->getEmptyDictionaryData());
    ctlPanelDictTab = new QTableView;
    ctlPanelDictTab->verticalHeader()->setVisible(false);
    ctlPanelDictTab->setAlternatingRowColors(true);
    ctlPanelDictTab->setModel(dictModel);
    ctlPanelDictTab->resizeRowsToContents();
    ctlPanelDictTab->resizeColumnsToContents();
    ctlPanelDictTab->setSelectionBehavior(QAbstractItemView::SelectRows);
    ctlPanelDictTab->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ctlPanelDictTab->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->controlPanelTabs->insertTab(0, ctlPanelDictTab, QString("Dictionary"));
    connect(ctlPanelDictTab, SIGNAL(clicked(QModelIndex)), this, SLOT(tempGraph(QModelIndex)));

    // Initialize a custom plot for the main window
    ui->testPlot->addGraph();
    ui->testPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->testPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Dictionary_triggered()
{
    // Request to load a Dictionary file made
    ui->statusBar->showMessage(QString("Loading Dictionary..."));
    // Make call to generic load function
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Dictionary"), QDir::currentPath(), tr("CSV Files (*.csv)"));
    // Load and parse the file
    int status = dataMgr->loadFileData(filename, FileType::FILE_DICT);
    // Update the status
    updateStatusByError(status);
    // Update the view with the new Dictionary
    dictModel->setMap(dataMgr->getDictionaryData());
}

void MainWindow::on_actionLoad_Telemetry_triggered()
{
    // Request to load a Telemetry file made
    ui->statusBar->showMessage(QString("Loading Telemetry..."));
    // Make call to generic load function
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Telemetry"), QDir::currentPath(), tr("BIN Files (*.bin)"));
    // Load and parse the file
    int status = dataMgr->loadFileData(filename, FileType::FILE_TM);
    // Update the status
    updateStatusByError(status);
}

void MainWindow::on_actionExit_triggered()
{
    // User has selected to exit, pop up with a chance to save telmplate,
    // exit and lose changes, or cancel the exit
}

void MainWindow::tempGraph(const QModelIndex &index)
{
    // Test plot
    QVector<double> data;
    QVector<double> time;
    for(auto iter : dataMgr->tmData->data->value(index.row()))
    {
        data.append(iter.toDouble());
    }
    for(auto iter : dataMgr->tmData->data->value(1))
    {
        time.append(iter.toDouble());
    }
    ui->testPlot->graph(0)->setData(time, data);
    ui->testPlot->xAxis->setLabel(dataMgr->getDictionaryData()->value(1).name);
    ui->testPlot->yAxis->setLabel(dataMgr->getDictionaryData()->value(index.row()).name);
    ui->testPlot->replot();
}

void MainWindow::updateStatusByError(int error)
{
    // Generic switch statement based on errors to update status bar
    switch(error)
    {
    case Errors::ERR_NONE:
        ui->statusBar->showMessage("Success!", STAT_DEFAULT);
        break;
    case Errors::ERR_NOTEXIST:
        ui->statusBar->showMessage("File did not exist!", STAT_ERROR);
        break;
    case Errors::ERR_MEMORY:
        ui->statusBar->showMessage("Memory error occurred", STAT_ERROR);
        break;
    case Errors::ERR_NODICT:
        ui->statusBar->showMessage("Load Dictionary to parse Telemetry", STAT_ERROR);
        break;
    case Errors::ERR_UNIMPLEMENTED:
        ui->statusBar->showMessage("Reached unimplemented code somehow...", STAT_ERROR);
        break;
    case Errors::ERR_BADDICT:
        ui->statusBar->showMessage("Issue with dictionary file", STAT_ERROR);
        break;
    default:
        ui->statusBar->showMessage("Unknown error occurred", STAT_ERROR);
        break;
    }
}
