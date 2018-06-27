#include "data.h"

Data::Data()
{
    fileName = "data.csv";
    readFile();
}

void Data::readFile()
{
    rows.clear();
    QFile file(fileName);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "File not exists";
    } else {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            rows.append(parseCSV(in.readLine()));
        }
    }
    file.close();
}

QStringList Data::parseCSV(const QString &string)
{
    enum State {Normal, Quote} state = Normal;
    QStringList fields;
    QString value;

    for (int i = 0; i < string.size(); ++i)
    {
        QChar current = string.at(i);

        if (state == Normal)
        {
            if (current == ',')
            {
                if (value == "")
                {
                    fields.append(" ");
                } else {
                    fields.append(value);
                }
                value.clear();
                if (i == string.size() - 1)
                {
                    fields.append(" ");
                }
            }

            else if (current == '"')
                state = Quote;

            else
                value += current;
        }

        else if (state == Quote)
        {
            if (current == '"')
            {
                if (i+1 < string.size())
                {
                    QChar next = string.at(i+1);

                    if (next == '"')
                    {
                        value += '"';
                        i++;
                    }
                    else
                        state = Normal;
                }
            }

            else
                value += current;
        }
    }
    if (!value.isEmpty())
        fields.append(value);

    return fields;
}

void Data::setFileName(QString &name)
{
    fileName = name;
    readFile();
}

void Data::writeFile(QString &name)
{
    QFile file(name);
    if ( !file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Can't open file!";
    } else {
        QTextStream stream(&file);
        for (int i = 0; i < rows.size(); ++i)
        {
            stream << rows.at(i).at(0);
            for (int j = 1; j < rows.at(i).size(); ++j)
            {

                stream << "," << rows.at(i).at(j);
            }
            stream << "\r\n";
        }
    }
    file.close();

}
