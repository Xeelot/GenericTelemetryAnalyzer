#include "loadwindow.h"
#include "ui_loadwindow.h"

// TODO: This entire class could probably go away and become more robust by making
// a generic QFileDialog class in the main window, this was done more as an exercise
// toward the beginning of development, but does provide more customization

LoadWindow::LoadWindow(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::LoadWindow)
{
    ui->setupUi(this);

    // TODO: load previous root directory from configuration file
    QString defaultPath = QDir::currentPath();
    currentType = FileType::FILE_ALL;

    // Append the status bar to the window so we can see how badly this class works
    status = new QStatusBar(this);
    ui->vertWindowLayout->addWidget(status, 1);

    // Initialize the directory model
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    QModelIndex index = dirModel->setRootPath(defaultPath);
    ui->dirTreeView->setModel(dirModel);

    // Open the default path in the tree
    ui->dirTreeView->expand(index);
    ui->dirTreeView->scrollTo(index);
    ui->dirTreeView->resizeColumnToContents(0);

    // Initialize the file model
    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(defaultPath);
    ui->fileListView->setModel(fileModel);

    // Set keyboard actions on buttons
    ui->loadButton->setShortcut(Qt::Key_Enter);
    ui->cancelButton->setShortcut(Qt::Key_Escape);

    // Make connections for button actions
    // Cancel button will close this popup window
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    // Load button will generate a signal
    connect(ui->loadButton, SIGNAL(clicked(bool)), this, SLOT(processLoadButton()));
    // When a directory is clicked, update the file view for the new folder
    connect(ui->dirTreeView, SIGNAL(clicked(QModelIndex)), this, SLOT(processDirClick(QModelIndex)));
    // When a file is clicked, update the file line edit for the new file
    connect(ui->fileListView, SIGNAL(clicked(QModelIndex)), this, SLOT(processFileClick(QModelIndex)));
}

LoadWindow::~LoadWindow()
{
    delete ui;
}

// TODO: save multiple addresses for dict, tm, etc so they can be set with load type here

void LoadWindow::setLoadType(FileType fileType)
{
    // Window is about to be opened, parent class can set the file type
    currentType = fileType;
    // First, clear out the combo box items
    ui->extensionComboBox->clear();
    QStringList newFilters;

    // Next, determine the type from what was passed in
    switch(fileType)
    {
    case FileType::FILE_DICT:
    case FileType::FILE_REQ:
        // Set filters for Dictionary/Requirement type
        newFilters << EXT_CSV << EXT_ALL;
        status->showMessage(QString("Load CSV File..."));
        break;
    case FileType::FILE_TM:
        // Set filters for Telemetry type
        newFilters << EXT_BIN << EXT_ALL;
        status->showMessage(QString("Load Binary Image..."));
        break;
    case FileType::FILE_TMPL:
        // Set filters for Template type
        newFilters << EXT_JSON << EXT_ALL;
        status->showMessage(QString("Load JSON Template..."));
        break;
    case FileType::FILE_ALL:
    default:
        // Currently should not arrive here, set default
        newFilters << EXT_ALL;
        status->showMessage(QString("Goofy: Load any file..."));
        break;
    }

    // Add the items to the combo box and set to 1st index
    ui->extensionComboBox->addItems(newFilters);
    ui->extensionComboBox->setCurrentIndex(0);

    // Update the filter on the file list
    fileModel->setNameFilters(QStringList(ui->extensionComboBox->currentText()));
}

void LoadWindow::processDirClick(QModelIndex index)
{
    // Directory has been clicked, check for valid index
    if(index.isValid())
    {
        // Update the file view to show the new folder
        ui->fileListView->setRootIndex(fileModel->setRootPath(dirModel->fileInfo(index).absoluteFilePath()));

        // Expand the column to fit the name in the dir model
        ui->dirTreeView->resizeColumnToContents(0);
        status->showMessage(QString("Processed directory successfully..."), 1000);
    }
    else
    {
        status->showMessage(QString("Warning: Bad directory selected..."), 2000);
    }
}

void LoadWindow::processFileClick(QModelIndex index)
{
    // File has been clicked, check for valid index
    if(index.isValid())
    {
        // Update the line edit to show the full path of the file
        ui->fileLineEdit->setText(fileModel->fileInfo(index).absoluteFilePath());
        status->showMessage(QString("Processed file successfully..."), 1000);
    }
    else
    {
        status->showMessage(QString("Warning: Bad file selected..."), 2000);
    }
}

void LoadWindow::processLoadButton()
{
    // Load has been clicked, check for file
    if(ui->fileListView->currentIndex().isValid())
    {
        status->showMessage(QString("Loading file!"));
        // File is valid, broadcast signal for higher classes
        QModelIndex index = ui->fileListView->currentIndex();
        QString filePath = fileModel->fileInfo(index).absoluteFilePath();
        emit loadFile(filePath, currentType);
    }
    else
    {
        status->showMessage(QString("Error: No file selected..."), 2000);
    }
}

void LoadWindow::processFileEdit()
{
    // User has manually edited the line and hit enter or changed focus
    // Attempt to find the directory and file
    QString edit = ui->fileLineEdit->text();
    QFileInfo *editFile = new QFileInfo(edit);

    // Check for directory existing first
    if(editFile->absoluteDir().exists())
    {
        // Directory exists, update the directory model
        QModelIndex index = dirModel->setRootPath(editFile->absoluteDir().absolutePath());
        ui->dirTreeView->expand(index);
        ui->dirTreeView->scrollTo(index);
        ui->dirTreeView->resizeColumnToContents(0);
        // Call slot to update file model
        processDirClick(index);

        // Check for file existence
        if(editFile->exists())
        {
            // File exists, update the file model selection
            status->showMessage(QString("Input file found!"), 1000);

        }
        else
        {
            status->showMessage(QString("Warning: Input directory found, file not found..."), 2000);
        }
    }
    else
    {
        status->showMessage(QString("Warning: Input directory not found..."), 2000);
    }
}
