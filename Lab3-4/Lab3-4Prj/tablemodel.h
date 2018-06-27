#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "data.h"
#include <QDebug>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    Data myData;
public:
    TableModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    void loadFile(QString fileName);
    void saveFile(QString fileName);
    QStringList getListCB();
};

#endif // TABLEMODEL_H
