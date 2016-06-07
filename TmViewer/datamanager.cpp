#include "datamanager.h"

#include "fileserializer.h"

DataManager::DataManager():
    dictLoaded(false),
    tmLoaded(false),
    dictPath(""),
    tmPath("")
{
    // Initialize main structures
    dictData = new Dictionary;
    tmData = new Telemetry;
    // Create empty structure for display purposes
    emptyDict = new QMap<int, DictItems>;
    DictItems empty;
    empty.name = "Load Dictionary";
    empty.word = 0;
    empty.intlv = 0;
    empty.type = QString("NULL");
    empty.size = 0;
    emptyDict->insert(0, empty);
}

int DataManager::loadFileData(QString filePath, FileType type)
{
    int status = Errors::ERR_NONE;
    switch(type)
    {
    case FileType::FILE_DICT:
        // Parse Dictionary and save if no errors occurred
        status = FileSerializer::Deserialize(dictData, filePath);
        if(status == Errors::ERR_NONE)
        {
            // No errors, save the path and load variable
            dictPath = filePath;
            dictLoaded = true;
            // Check to see if TM is loaded and re-parse if needed
            tmData->setDictionary(dictData);
            if(tmLoaded)
            {
                status = FileSerializer::Deserialize(tmData, tmPath);
            }
        }
        break;
    case FileType::FILE_TM:
        // Parse Telemetry and save if no errors occurred
        status = FileSerializer::Deserialize(tmData, filePath);
        if(status == Errors::ERR_NONE || status == Errors::ERR_NODICT)
        {
            // No error or no dictionary is acceptable
            // Parsing will be handled once dictionary is loaded
            tmPath = filePath;
            tmLoaded = true;
        }
        break;
    case FileType::FILE_ALL:
    default:
        // Should never get here, unimplemented
        status = Errors::ERR_UNIMPLEMENTED;
        break;
    }
    return status;
}
