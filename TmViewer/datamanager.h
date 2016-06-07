#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>

#include "constants.h"
#include "dictionary.h"
#include "telemetry.h"

class DataManager
{
public:
    DataManager();
    inline QMap<int, DictItems>* getDictionaryData() { return dictData->getData(); }
    inline QMap<int, DictItems>* getEmptyDictionaryData() { return emptyDict; }
    int loadFileData(QString filePath, FileType type);

    Telemetry *tmData;
private:
    // Quick check variables for files loaded
    bool dictLoaded;
    bool tmLoaded;
    // Path to the current files loaded
    QString dictPath;
    QString tmPath;
    // Data structures for files
    Dictionary *dictData;
    // Empty structure for display purposes
    QMap<int, DictItems> *emptyDict;
};

#endif // DATAMANAGER_H
