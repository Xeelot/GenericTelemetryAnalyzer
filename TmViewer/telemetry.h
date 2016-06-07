#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QMap>
#include <QString>
#include <QVariant>
#include <QVector>

#include "dictionary.h"
#include "ifileobject.h"

class Telemetry : public IFileObject
{
public:
    Telemetry();
    virtual ~Telemetry();
    virtual int serialize(QString &filePath);
    virtual int deserialize(QString &filePath);
    void setDictionary(Dictionary *dictInput);

    QMap<int, QVector<QVariant> > *data;
private:
    Dictionary *dict;
    int parseFrameData(const quint8 *frame, const int frameCount);
    int insertData(int key, QVariant piece);
};

#endif // TELEMETRY_H
