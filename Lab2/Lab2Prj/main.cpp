#include <QApplication>
#include <QTableView>
#include "tablemodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    TableModel model(0);
    tableView.setModel(&model);
    tableView.resizeColumnsToContents();
    tableView.resizeRowsToContents();
    tableView.resize(680,500);
    tableView.show();
    return a.exec();
}
