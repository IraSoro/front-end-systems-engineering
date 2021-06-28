#include "mainwindowblock.h"
#include "ui_mainwindowblock.h"

#include <QStringList>

MainWindowBlock::MainWindowBlock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowBlock)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(3);
    QStringList name_table;
    name_table << "Название" << "Тип" << "Разрядность";
    ui->tableWidget->setHorizontalHeaderLabels(name_table);


}

MainWindowBlock::~MainWindowBlock()
{
    delete ui;
}

void MainWindowBlock::on_pushButton_2_clicked()
{
    this->close();
    emit firstWindow();
}
