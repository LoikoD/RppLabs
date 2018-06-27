#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "tablemodel.h"
#include "saveloadwindow.h"
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QPushButton>
#include <QItemSelectionModel>
#include <QDebug>

class MainWindow : public QWidget
{
    Q_OBJECT
    TableModel *tableModel;
    QTableView *tableView;
    QItemSelectionModel *select;
    QLineEdit *nameLE;
    QLineEdit *teacherLE;
    QComboBox *controlCB;
    QLineEdit *controlLE;
    QLineEdit *depLE;
    QPushButton *fileBtn;
    QPushButton *addBtn;
    QPushButton *deleteBtn;
    QPushButton *saveBtn;
public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:

public slots:
    void selectedRow(const QItemSelection& selected);
    void deleteRow();
    void saveRow();
    void addRow();
    void fileAction();
    void changeControl(const QString& text);
};

#endif // MAINWINDOW_H
