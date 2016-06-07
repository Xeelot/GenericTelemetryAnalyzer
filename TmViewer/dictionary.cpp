#include "dictionary.h"

#include <QFileInfo>

#include "constants.h"

Dictionary::Dictionary():
    dictVersion(""),
    dictTimeName(""),
    dictHeaderSize(0),
    dictFrameSize(0),
    dictIntlvCount(0),
    dictIntlvOffset(0),
    headerComplete(false)
{
    dictData = new QMap<int, DictItems>;
}

Dictionary::~Dictionary()
{

}

int Dictionary::serialize(QString &filePath)
{
    // May not be needed, currently here as a placeholder
    return Errors::ERR_NONE;
}

int Dictionary::deserialize(QString &filePath)
{
    // Check to make sure file exists
    QFileInfo check(filePath);
    if(check.exists() && check.isFile())
    {
        // Read file
        QFile dict(filePath);
        if(dict.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            // Clear out any previous entries and start
            dictData->clear();
            headerComplete = false;
            while(!dict.atEnd())
            {
                QString line = dict.readLine();

                // Check for Header information until complete
                if(!headerComplete)
                {
                    if(line.contains(DICT_VERSION))
                    {
                        QStringList temp = line.split(",");
                        dictVersion = temp.value(1);
                    }
                    else if(line.contains(DICT_HEADERSIZE, Qt::CaseInsensitive))
                    {
                        QStringList temp = line.split(",");
                        dictHeaderSize = temp.at(1).toInt();
                    }
                    else if(line.contains(DICT_FRAMESIZE, Qt::CaseInsensitive))
                    {
                        QStringList temp = line.split(",");
                        dictFrameSize = temp.at(1).toInt();
                    }
                    else if(line.contains(DICT_INTLVCOUNT, Qt::CaseInsensitive))
                    {
                        QStringList temp = line.split(",");
                        dictIntlvCount = temp.at(1).toInt();
                    }
                    else if(line.contains(DICT_INTLVOFFSET, Qt::CaseInsensitive))
                    {
                        QStringList temp = line.split(",");
                        dictIntlvOffset = temp.at(1).toInt();
                    }
                    else if(line.contains(DICT_TIMEVAR, Qt::CaseInsensitive))
                    {
                        QStringList temp = line.split(",");
                        dictTimeName = temp.at(1);
                    }
                    else if(line.contains(DICT_START, Qt::CaseInsensitive))
                    {
                        headerComplete = true;
                    }
                }
                else
                {
                    // Parsed beyond the header into data
                    QStringList temp = line.split(",");
                    // Make sure the line isn't blank otherwise assume data is present
                    if(temp.length() > 0)
                    {
                        DictItems item;
                        item.name = temp.at(1); // String
                        item.word = temp.at(2).toInt(); // Int
                        item.size = temp.at(3).toInt(); // Int
                        item.intlv = temp.at(4).toInt(); // Int
                        item.type = temp.at(5); // String
                        dictData->insert(temp.at(0).toInt(), item);
                    }
                }
            }
            // Close the dictionary after reading
            dict.close();
        }
    }
    else
    {
        return Errors::ERR_NOTEXIST;
    }
    return Errors::ERR_NONE;
}
