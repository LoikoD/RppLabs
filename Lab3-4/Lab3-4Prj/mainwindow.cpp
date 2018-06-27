#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    resize(1240,250);
    tableModel = new TableModel();
    tableView = new QTableView();
    tableView->setModel(tableModel);
    tableView->resizeColumnsToContents();
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    select = tableView->selectionModel();

    nameLE = new QLineEdit();
    teacherLE = new QLineEdit();
    controlCB = new QComboBox();
    controlLE = new QLineEdit();
    controlCB->addItems(tableModel->getListCB());
    depLE = new QLineEdit();
    fileBtn = new QPushButton("Файл");
    addBtn = new QPushButton("Добавить");
    deleteBtn = new QPushButton("Удалить");
    saveBtn = new QPushButton("Сохранить");
    controlLE->setEnabled(false);
    deleteBtn->setEnabled(false);
    saveBtn->setEnabled(false);

    QHBoxLayout *leftBtnLayout = new QHBoxLayout();
    leftBtnLayout->addWidget(fileBtn);
    leftBtnLayout->addStretch(2);
    leftBtnLayout->addWidget(addBtn);
    leftBtnLayout->setStretchFactor(fileBtn, 1);
    leftBtnLayout->setStretchFactor(addBtn, 1);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(tableView);
    leftLayout->addLayout(leftBtnLayout);
    leftLayout->setStretchFactor(tableView, 9);
    leftLayout->setStretchFactor(leftBtnLayout, 1);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Название дисциплины:", nameLE);
    formLayout->addRow(tr("ФИО преподавателя:"), teacherLE);
    formLayout->addRow(tr("Наименование кафедры:"), depLE);
    formLayout->addRow(tr("Форма контроля:"), controlCB);
    formLayout->addRow(tr(""), controlLE);
    formLayout->setVerticalSpacing(20);

    QHBoxLayout *rightBtnLayout = new QHBoxLayout();
    rightBtnLayout->addStretch(2);
    rightBtnLayout->addWidget(deleteBtn);
    rightBtnLayout->addWidget(saveBtn);
    rightBtnLayout->setStretchFactor(deleteBtn, 1);
    rightBtnLayout->setStretchFactor(saveBtn, 1);

    QHBoxLayout *rightMainLayout = new QHBoxLayout();
    rightMainLayout->addStretch(1);
    rightMainLayout->addLayout(formLayout);
    rightMainLayout->setStretchFactor(formLayout, 4);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addLayout(rightMainLayout);
    rightLayout->addStretch(1);
    rightLayout->addLayout(rightBtnLayout);
    rightLayout->setStretchFactor(rightMainLayout, 8);
    rightLayout->setStretchFactor(rightBtnLayout, 1);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);


    connect(select, SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), SLOT(selectedRow(const QItemSelection&)));
    connect(deleteBtn, SIGNAL(clicked()), SLOT(deleteRow()));
    connect(saveBtn, SIGNAL(clicked()), SLOT(saveRow()));
    connect(addBtn, SIGNAL(clicked()), SLOT(addRow()));
    connect(fileBtn, SIGNAL(clicked()), SLOT(fileAction()));
    connect(controlCB, SIGNAL(currentTextChanged(const QString&)), SLOT(changeControl(const QString&)));
}

void MainWindow::selectedRow(const QItemSelection& selected)
{
    if (select->selectedRows().size() == 1)
    {
        deleteBtn->setEnabled(true);
        saveBtn->setEnabled(true);
        QModelIndexList indexList = selected.indexes();
        nameLE->setText(indexList.at(0).data().toString());
        teacherLE->setText(indexList.at(1).data().toString());
        controlCB->setCurrentIndex(controlCB->findText(indexList.at(2).data().toString()));
        depLE->setText(indexList.at(3).data().toString());
        return;
    }
    deleteBtn->setEnabled(false);
    saveBtn->setEnabled(false);
}

void MainWindow::deleteRow()
{
    tableModel->removeRow(select->currentIndex().row());
}

void MainWindow::saveRow()
{
    QModelIndexList indexList = select->selectedIndexes();
    tableModel->setData(indexList.at(0), nameLE->text());
    tableModel->setData(indexList.at(1), teacherLE->text());
    tableModel->setData(indexList.at(3), depLE->text());
    if (controlLE->isEnabled())
    {
        tableModel->setData(indexList.at(2), controlLE->text());
        controlCB->insertItem(controlCB->count() - 1, controlLE->text());
    } else {
        tableModel->setData(indexList.at(2), controlCB->currentText());
    }
}

void MainWindow::addRow()
{
    tableModel->insertRow(tableModel->rowCount());
}

void MainWindow::fileAction()
{
    SaveLoadWindow *saveLoadWindow = new SaveLoadWindow();
    int result = saveLoadWindow->exec();
    switch (result)
    {
    case 1:
        tableModel->loadFile(saveLoadWindow->getFileName());
        controlCB->clear();
        controlCB->addItems(tableModel->getListCB());
        tableView->resizeColumnsToContents();
        return;
    case 2:
        tableModel->saveFile(saveLoadWindow->getFileName());
        return;
    }
}

void MainWindow::changeControl(const QString& text)
{
    if (text == "Другой вариант")
    {
        controlLE->setEnabled(true);
        return;
    }
    controlLE->setEnabled(false);
}

MainWindow::~MainWindow()
{

}
