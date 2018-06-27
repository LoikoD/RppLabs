#include "data.h"

Data::Data()
{
    readFile();
}

void Data::readFile()
{
    QFile file("data.csv");
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

    for (int i = 0; i < string.size(); i++)
    {
        QChar current = string.at(i);

        if (state == Normal)
        {
            if (current == ',')
            {
                fields.append(value);
                value.clear();
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
