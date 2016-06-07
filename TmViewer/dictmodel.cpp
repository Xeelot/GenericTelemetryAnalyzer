#include "dictmodel.h"

#include <QBrush>

#include "constants.h"

DictModel::DictModel(QObject *parent):
    QAbstractTableModel(parent)
{
    // Ensure the pointer is constructed as NULL
    _map = NULL;
}

void DictModel::setMap(QMap<int, DictItems> *map)
{
    _map = map;
    this->beginResetModel();
    this->endResetModel();
}

int DictModel::rowCount(const QModelIndex &parent) const
{
    // If the map is assigned, output the row count
    if(_map)
    {
        return _map->count();
    }
    return 0;
}

int DictModel::columnCount(const QModelIndex &parent) const
{
    // If the map is assigned, output the column count
    if(_map)
    {
        return DICT_ITEM_SIZE;
    }
    return 0;
}

QVariant DictModel::data(const QModelIndex &index, int role) const
{
    // If the map is NULL, return a blank QVariant
    if(!_map)
    {
        return QVariant();
    }
    // If the parent is requesting alignment, set to centered for all but the first column
    if((index.column() != 0) && (role == Qt::TextAlignmentRole))
    {
        return Qt::AlignCenter;
    }
    // If the parent is requesting data outside the bounds of the map, return a blank QVariant
    if((index.row() < 0) || (index.row() >= _map->count()) || role != Qt::DisplayRole)
    {
        return QVariant();
    }
    // Switch over Dictionary columns, this determines how the data is displayed
    switch(index.column())
    {
    case 0:
        return _map->values().at(index.row()).name;
        break;
    case 1:
        return _map->values().at(index.row()).word;
        break;
    case 2:
        return _map->values().at(index.row()).intlv;
        break;
    case 3:
        return _map->values().at(index.row()).type;
        break;
    case 4:
        return _map->values().at(index.row()).size;
        break;
    default:
        // Should not reach here
        return QVariant();
        break;
    }
    // Should not reach here either
    return QVariant();
}

QVariant DictModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if((role == Qt::DisplayRole) && (orientation == Qt::Horizontal))
    {
        // Given a horizontal display request, send the appropriate header string
        switch(section)
        {
        case 0:
            return QVariant(DICT_NAME);
            break;
        case 1:
            return QVariant(DICT_WORD);
            break;
        case 2:
            return QVariant(DICT_INTLV);
            break;
        case 3:
            return QVariant(DICT_TYPE);
            break;
        case 4:
            return QVariant(DICT_SIZE);
            break;
        default:
            // Should not reach here
            return QVariant();
            break;
        }
    }
    else if((role == Qt::BackgroundRole) && (orientation == Qt::Horizontal))
    {
        return QVariant(QBrush(QColor(Qt::gray), Qt::SolidPattern));
    }
    // Should not reach here
    return QVariant();
}
