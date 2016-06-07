#include "telemetry.h"

#include <QDataStream>
#include <QFileInfo>

#include "constants.h"

Telemetry::Telemetry()
{
    dict = NULL;
    data = new QMap<int, QVector<QVariant> >;
    //data = new QVector<QVector<quint64> >;
    //data = new QMap<int, quint64>;
}

Telemetry::~Telemetry()
{

}

void Telemetry::setDictionary(Dictionary *dictInput)
{
    dict = dictInput;
}

int Telemetry::serialize(QString &filePath)
{
    // May not be needed, currently here as a placeholder
    return Errors::ERR_NONE;
}

int Telemetry::deserialize(QString &filePath)
{
    // Check to make sure file exists
    QFileInfo check(filePath);
    if(check.exists() && check.isFile())
    {
        // Check to ensure dictionary is available
        if(dict != NULL)
        {
            // Read file
            QFile tm(filePath);
            if(tm.open(QIODevice::ReadOnly))
            {
                quint8 *buffer = new quint8[dict->getFrameSize()];
                QDataStream stream(&tm);
                quint8 byte;
                int count = 0;

                // Skip past the header
                for(int i = 0; i < dict->getHeaderSize(); ++i)
                {
                    stream >> byte;
                }
                // Read the rest of the file
                while(!stream.atEnd())
                {
                    // Read a single frame of bytes
                    for(int i = 0; i < dict->getFrameSize(); ++i)
                    {
                        stream >> buffer[i];
                    }
                    // Parse frame in sub-function
                    parseFrameData(buffer, count);
                    // Increment frame counter
                    count++;
                }
            }
        }
        else
        {
            return Errors::ERR_NODICT;
        }
    }
    else
    {
        return Errors::ERR_NOTEXIST;
    }
    return Errors::ERR_NONE;
}

int Telemetry::parseFrameData(const quint8 *frame, const int frameCount)
{
    // We now have a single frame, a frame number, and a dictionary
    //TODO: Take interleave into account in iterator for efficiency
    int status = Errors::ERR_NONE;
    QMap<int, DictItems>::iterator iter;
    for(iter = dict->getData()->begin(); iter != dict->getData()->end(); ++iter)
    {
        //TODO: Lots of ways to do this.. had trouble with QMap of Qvectors, ended up processing variable
        // types on a byte-by-byte process rather than doing something smarter like declaring a QDataStream
        // to read the value out of the stream directly...
        // Another viable approach would be to read out bitSize as uintXX and static_cast based on type.
        QString type = iter.value().type;
        int interleave = iter.value().intlv;
        // Verify interleave before continuing (0 = all interleaves, interleave is 1-based, frameCount is 0-based)
        if((interleave == 0) || (interleave == (((frameCount * dict->getIntlvOffset()) % dict->getIntlvCount()) + 1)))
        {
            if(type.contains(VAR_UINT64, Qt::CaseInsensitive))
            {
                // Process a uint64 for variable
                quint64 temp = frame[(iter.value().word * 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 1)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 3)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 4)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 5)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 6)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 7)];
                insertData(iter.key(), temp);
            }
            else if(type.contains(VAR_UINT32, Qt::CaseInsensitive))
            {
                // Process a uint32 for variable
                quint32 temp = frame[(iter.value().word * 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 1)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 3)];
                insertData(iter.key(), temp);
            }
            else if(type.contains(VAR_UINT16, Qt::CaseInsensitive))
            {
                // Process a uint16 for variable
                quint16 temp = frame[(iter.value().word * 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 1)];
                insertData(iter.key(), temp);
            }
            else if(type.contains(VAR_UINT8, Qt::CaseInsensitive))
            {
                // Process a uint8 for variable
                quint8 temp = frame[(iter.value().word * 2)];
                insertData(iter.key(), temp);
            }
            else if(type.contains(VAR_INT64, Qt::CaseInsensitive))
            {
                // Process a int64 for variable
                qint64 temp = frame[(iter.value().word * 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 1)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 3)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 4)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 5)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 6)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 7)];
                insertData(iter.key(), temp);
            }
            else if(type.contains(VAR_INT32, Qt::CaseInsensitive))
            {
                // Process a int32 for variable
                qint32 temp = frame[(iter.value().word * 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 1)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 3)];
                insertData(iter.key(), temp);
            }
            else if(type.contains(VAR_INT16, Qt::CaseInsensitive))
            {
                // Process a int16 for variable
                qint16 temp = frame[(iter.value().word * 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 1)];
                insertData(iter.key(), temp);
            }
            else if(type.contains(VAR_INT8, Qt::CaseInsensitive))
            {
                // Process a int8 for variable
                qint8 temp = frame[(iter.value().word * 2)];
                insertData(iter.key(), temp);
            }
            else if(type.contains(VAR_FLOAT64, Qt::CaseInsensitive))
            {
                // Process a double precision float for variable
                quint64 temp = frame[(iter.value().word * 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 1)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 3)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 4)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 5)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 6)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 7)];
                double ftemp = static_cast<double>(temp);
                insertData(iter.key(), ftemp);
            }
            else if(type.contains(VAR_FLOAT32, Qt::CaseInsensitive))
            {
                // Process a single precision float for variable
                quint32 temp = frame[(iter.value().word * 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 1)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 2)];
                temp = (temp << TM_BYTE) + frame[(iter.value().word * 2 + 3)];
                float ftemp = static_cast<float>(temp);
                insertData(iter.key(), ftemp);
            }
            else if(type.contains(VAR_CHAR, Qt::CaseInsensitive))
            {
                // Process a single character for variable
                char temp = frame[(iter.value().word * 2)];
                insertData(iter.key(), temp);
            }
            else
            {
                if(iter.value().size != 0)
                {

                }
                else
                {
                    // No type or size specified, error
                    status = Errors::ERR_BADDICT;
                }
            }
        }
    }
    return status;
}

int Telemetry::insertData(int key, QVariant piece)
{
    // Find the element given the key
    QMap<int, QVector<QVariant> >::iterator i = data->find(key);
    if(i == data->end())
    {
        // Element does not exist yet, create a new QVector
        QVector<QVariant> newVector;
        newVector.append(piece);
        data->insert(key, newVector);
    }
    else
    {
        // Element exists, append to current QVector
        i->append(piece);
    }
    return Errors::ERR_NONE;
}
