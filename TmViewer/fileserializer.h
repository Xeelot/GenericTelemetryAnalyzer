#ifndef FILESERIALIZER_H
#define FILESERIALIZER_H

#include <QString>

#include "ifileobject.h"

class FileSerializer
{
public:
    static int Serialize(IFileObject* pObj, QString &filePath);
    static int Deserialize(IFileObject* pObj, QString &filePath);

private:
    FileSerializer() {}
};

#endif // FILESERIALIZER_H
