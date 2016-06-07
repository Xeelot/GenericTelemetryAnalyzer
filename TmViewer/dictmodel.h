#ifndef DICTMODEL_H
#define DICTMODEL_H

#include <QAbstractTableModel>
#include <QMap>

#include "dictionary.h"

class DictModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    // Constructor
    explicit DictModel(QObject *parent = 0);
    // Overloaded functions for row and column counts
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    // Overloaded function for retrieving data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    // Overloaded function for setting the model header
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    // Function for setting the model data
    void setMap(QMap<int, DictItems>* map);

private:
    QMap<int, DictItems>* _map;
};

#endif // DICTMODEL_H
