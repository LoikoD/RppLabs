#include "saveloadwindow.h"

SaveLoadWindow::SaveLoadWindow(QWidget *parent) : QDialog(parent)
{
    setModal(true);
    fileLE = new QLineEdit();
    closeBtn = new QPushButton("Закрыть");
    loadBtn = new QPushButton("Загрузить файл");
    saveBtn = new QPushButton("Сохранить файл");
    QLabel *fileLbl = new QLabel("Файл:");

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addStretch(1);
    topLayout->addWidget(fileLbl);
    topLayout->addWidget(fileLE);
    topLayout->setStretchFactor(fileLbl, 2);
    topLayout->setStretchFactor(fileLE, 7);

    QHBoxLayout *botLayout = new QHBoxLayout();
    botLayout->addWidget(closeBtn);
    botLayout->addWidget(loadBtn);
    botLayout->addWidget(saveBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(botLayout);

    connect(closeBtn, SIGNAL(clicked()), SLOT(close()));
    connect(loadBtn, SIGNAL(clicked()), SLOT(loadSlot()));
    connect(saveBtn, SIGNAL(clicked()), SLOT(saveSlot()));
}

QString SaveLoadWindow::getFileName()
{
    return fileLE->text();
}

void SaveLoadWindow::loadSlot()
{
    done(1);
}

void SaveLoadWindow::saveSlot()
{
    done(2);
}
