#include "mainwindowblock.h"
#include "ui_mainwindowblock.h"

#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

MainWindowBlock::MainWindowBlock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowBlock)
{
    ui->setupUi(this);

    ui->tableWidget_BusInBlock->setColumnCount(3);
    QStringList name_table;
    name_table << "Название" << "Тип" << "Разрядность";
    ui->tableWidget_BusInBlock->setHorizontalHeaderLabels(name_table);


}

MainWindowBlock::~MainWindowBlock()
{
    BusInBlock.clear();
    delete ui;
}

void MainWindowBlock::on_pushButton_2_clicked()
{
    if (ui->lineEdit_Block->text() == ""){
            QMessageBox msgBox;
            msgBox.setText("Вы ввели не все данные.");
            msgBox.exec();
            return;
    }
    this->close();
    emit firstWindow();
}

void MainWindowBlock::on_pushButton_AddBus_clicked()
{
    if (ui->lineEdit_NameBus->text() == ""){
            QMessageBox msgBox;
            msgBox.setText("Вы не ввели название шины.");
            msgBox.exec();
            return;
    }

    int CountRowInTable = ui->tableWidget_BusInBlock->rowCount();
    ui->tableWidget_BusInBlock->insertRow( CountRowInTable);

    QTableWidgetItem *itm = new QTableWidgetItem(ui->lineEdit_NameBus->text());
    ui->tableWidget_BusInBlock->setItem(CountRowInTable,0,itm);
    QTableWidgetItem *itm1 = new QTableWidgetItem(ui->comboBox_Type->currentText());
    ui->tableWidget_BusInBlock->setItem(CountRowInTable,1,itm1);
    QTableWidgetItem *itm2 = new QTableWidgetItem(ui->comboBox_Bitness->currentText());
    ui->tableWidget_BusInBlock->setItem(CountRowInTable,2,itm2);

    ui->tableWidget_BusInBlock->update();

    Shine temp;
    temp.NameShine = ui->lineEdit_NameBus->text();
    temp.TypeShine = ui->comboBox_Type->currentIndex();
    temp.Bitness = ui->comboBox_Bitness->currentText().toInt();
    BusInBlock.push_back(temp);

    qDebug()<<BusInBlock.size();

    delete itm;
    delete itm1;
    delete itm2;
}
