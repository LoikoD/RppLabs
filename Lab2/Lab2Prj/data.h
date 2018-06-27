#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <QDebug>
#include <QVector>
#include <QStringList>

class Data
{
public:
    QVector<QStringList> rows;
    Data();
    void readFile();
    QStringList parseCSV(const QString &string);
};

#endif // DATA_H
