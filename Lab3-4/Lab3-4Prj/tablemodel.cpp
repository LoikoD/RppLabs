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
    QList<int> colSize;
    int rowSize = rowCount();
    for (int i = 0; i < rowSize; ++i)
    {
        colSize << myData.rows.at(i).size();
    }
    int max = *std::max_element(colSize.begin(), colSize.end());
    return max;
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
                return QString("Форма контроля");
            case 3:
                return QString("Наименование кафедры");
            }
        }
        if (orientation == Qt::Vertical) {
            return QString("%1").arg(section+1);
        }
    }
    return QVariant();
}
bool TableModel::removeRows(int row, int count, const QModelIndex&parent)
{
    beginRemoveRows(parent, row, row+count-1);
    myData.rows.remove(row, count);
    endRemoveRows();
    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        myData.rows[index.row()][index.column()] = value.toString();
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    QStringList asd;
    asd << " " << " " << " " << " ";
    beginInsertRows(parent, row, row + count - 1);
    myData.rows.insert(row,count,asd);
    endInsertRows();
    return true;
}

void TableModel::loadFile(QString fileName)
{
    beginResetModel();
    myData.setFileName(fileName);
    endResetModel();
}

void TableModel::saveFile(QString fileName)
{
    myData.writeFile(fileName);
}

QStringList TableModel::getListCB()
{
    QStringList list;
    for (int i = 0; i < rowCount(); ++i)
    {
        list.append(myData.rows.at(i).at(2));
    }
    list.append("Другой вариант");
    list.removeDuplicates();
    return list;
}
