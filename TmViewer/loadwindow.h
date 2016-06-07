#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <QDialog>

#include <QFileSystemModel>
#include <QStatusBar>

#include "constants.h"

namespace Ui {
class LoadWindow;
}

class LoadWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadWindow(QDialog *parent = 0);
    ~LoadWindow();
    void setLoadType(FileType fileType);

signals:
    void loadFile(const QString &filePath, const FileType fileType);

private slots:
    void processDirClick(QModelIndex index);
    void processFileClick(QModelIndex index);
    void processFileEdit();
    void processLoadButton();

private:
    Ui::LoadWindow *ui;
    QStatusBar *status;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    FileType currentType;
};

#endif // LOADWINDOW_H
