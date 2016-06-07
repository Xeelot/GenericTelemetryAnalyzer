#ifndef CONSTANTS
#define CONSTANTS

#include <QString>
#include <QStringList>

// Files the program cares about
enum FileType
{
    FILE_ALL = 0,
    FILE_DICT,
    FILE_TM,
    FILE_REQ,
    FILE_TMPL,
    FILE_OUTPUT,
    NUM_FILE_TYPES
};

// Errors
enum Errors
{
    ERR_NONE = 0,
    ERR_NOTEXIST,
    ERR_MEMORY,
    ERR_NODICT,
    ERR_UNIMPLEMENTED,
    ERR_BADDICT
};

// Sizes
const int TM_BYTE = 8;
const int TM_WORD = 16;

// Expected variable types
const QString VAR_UINT64("uint64");
const QString VAR_UINT32("uint32");
const QString VAR_UINT16("uint16");
const QString VAR_UINT8("uint8");
const QString VAR_INT64("int64");
const QString VAR_INT32("int32");
const QString VAR_INT16("int16");
const QString VAR_INT8("int8");
const QString VAR_FLOAT64("float64");
const QString VAR_FLOAT32("float32");
const QString VAR_CHAR("char");
const QString VAR_BOOL("bool");

// Status Timers
const int STAT_DEFAULT = 3000;
const int STAT_ERROR = 6000;
const int STAT_QUICK = 1500;

// Dictionary Strings
const QString DICT_VERSION("Version,");
const QString DICT_HEADERSIZE("Header Size,");
const QString DICT_FRAMESIZE("Frame Size,");
const QString DICT_INTLVCOUNT("Interleave Count,");
const QString DICT_INTLVOFFSET("Interleave Offset,");
const QString DICT_TIMEVAR("Time Variable,");
const QString DICT_START("Variable Name,");

// Dictionary Model Strings
const QString DICT_NAME("Name");
const QString DICT_TYPE("Type");
const QString DICT_INTLV("Intlv");
const QString DICT_SIZE("BitSize");
const QString DICT_WORD("Word");
const int DICT_ITEM_SIZE(5);

#endif // CONSTANTS

