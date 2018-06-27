#ifndef SAVELOADWINDOW_H
#define SAVELOADWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>

class SaveLoadWindow : public QDialog
{
    Q_OBJECT
    QLineEdit *fileLE;
    QPushButton *closeBtn;
    QPushButton *loadBtn;
    QPushButton *saveBtn;
public:
    explicit SaveLoadWindow(QWidget *parent = nullptr);
    QString getFileName();

signals:

public slots:
    void loadSlot();
    void saveSlot();
};

#endif // SAVELOADWINDOW_H
