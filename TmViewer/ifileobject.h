#ifndef IFILEOBJECT_H
#define IFILEOBJECT_H

#include <QString>

class IFileObject
{
public:
    virtual ~IFileObject() {}
    virtual int serialize(QString &filePath) = 0;
    virtual int deserialize(QString &filePath) = 0;
};

#endif // IFILEOBJECT_H
