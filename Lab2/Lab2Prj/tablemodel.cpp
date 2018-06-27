#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int TableModel::rowCount(const QModelIndex &) const
{
    return myData.rows.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return 5;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return myData.rows.at(index.row()).at(index.column());
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Название дисциплины");
            case 1:
                return QString("ФИО преподавателя");
            case 2:
                return QString("Кол-во часов");
            case 3:
                return QString("Форма контроля");
            case 4:
                return QString("Наименование кафедры");
            }
        }
        if (orientation == Qt::Vertical) {
            return QString("%1").arg(section+1);
        }
    }
    return QVariant();
}

