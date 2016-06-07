#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QMap>
#include <QString>

#include "ifileobject.h"

struct DictItems
{
    QString name;
    QString type;
    int word;
    int size;
    int intlv;
};

class Dictionary : public IFileObject
{
public:
    Dictionary();
    virtual ~Dictionary();
    virtual int serialize(QString &filePath);
    virtual int deserialize(QString &filePath);

    inline QMap<int, DictItems>* getData() { return dictData; }
    inline int getHeaderSize() { return dictHeaderSize; }
    inline int getFrameSize() { return dictFrameSize; }
    inline int getIntlvCount() { return dictIntlvCount; }
    inline int getIntlvOffset() { return dictIntlvOffset; }

private:
    QString dictVersion;
    QString dictTimeName;
    int dictHeaderSize; // Bytes
    int dictFrameSize; // Bytes
    int dictIntlvCount;
    int dictIntlvOffset;

    QMap<int, DictItems> *dictData;

    bool headerComplete;
};

#endif // DICTIONARY_H
