#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <QDebug>
#include <QVector>
#include <QStringList>

class Data
{
    QString fileName;
public:
    QVector<QStringList> rows;
    Data();
    void readFile();
    QStringList parseCSV(const QString &string);
    void setFileName(QString &name);
    void writeFile(QString &name);
};

#endif // DATA_H
