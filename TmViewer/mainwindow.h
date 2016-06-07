#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>

#include "datamanager.h"
#include "dictmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_Dictionary_triggered();
    void on_actionLoad_Telemetry_triggered();
    void on_actionExit_triggered();

    void tempGraph(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    DataManager *dataMgr;
    void updateStatusByError(int error);
    QTableView *ctlPanelDictTab;
    DictModel *dictModel;
};

#endif // MAINWINDOW_H
