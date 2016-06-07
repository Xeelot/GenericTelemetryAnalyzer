#include "fileserializer.h"

#include "constants.h"

int FileSerializer::Serialize(IFileObject *pObj, QString &filePath)
{
    // Ensure the object exists before reading from it
    if(pObj == NULL)
    {
        return Errors::ERR_MEMORY;
    }
    return pObj->serialize(filePath);
}

int FileSerializer::Deserialize(IFileObject *pObj, QString &filePath)
{
    // Ensure the object exists before writing to it
    if(pObj == NULL)
    {
        return Errors::ERR_MEMORY;
    }
    return pObj->deserialize(filePath);
}
