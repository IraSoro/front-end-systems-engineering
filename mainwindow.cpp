#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->tableWidget_BusInBlock->setColumnCount(3);
    QStringList name_table;
    name_table << "Название" << "Тип" << "Разрядность";
    ui->tableWidget_BusInBlock->setHorizontalHeaderLabels(name_table);


}

MainWindow::~MainWindow()
{
    BusInBlock.clear();
    delete ui;
}

void MainWindow::on_pushButton_AddBus_clicked()
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

    ui->lineEdit_NameBus->clear();
    ui->comboBox_Type->update();
    ui->comboBox_Bitness->update();

}

void MainWindow::on_pushButton_AddBlock_clicked()
{
    BusInBlock.clear();
    qDebug()<<BusInBlock.size();
}
