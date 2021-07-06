#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

#include "drawingobjects.h"
#include "drawingconnections.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->tableWidget_BusInBlock->setColumnCount(3);
    QStringList name_table;
    name_table << "Название" << "Тип" << "Разрядность";
    ui->tableWidget_BusInBlock->setHorizontalHeaderLabels(name_table);

    DrawingSystem();
}

MainWindow::~MainWindow()
{
    BusInBlock.clear();
    delete ui;
}

void MainWindow::on_pushButton_AddBus_clicked()
{
    /*
    if (ui->lineEdit_NameBus->text() == ""){
            QMessageBox msgBox;
            msgBox.setText("Вы не ввели название шины.");
            msgBox.exec();
            return;
    }
    */

    int CountRowInTable = ui->tableWidget_BusInBlock->rowCount();
    ui->tableWidget_BusInBlock->insertRow( CountRowInTable);

    QTableWidgetItem *itm = new QTableWidgetItem(ui->lineEdit_NameBus->text());
    ui->tableWidget_BusInBlock->setItem(CountRowInTable,0,itm);
    QTableWidgetItem *itm1 = new QTableWidgetItem(ui->comboBox_Type->currentText());
    ui->tableWidget_BusInBlock->setItem(CountRowInTable,1,itm1);
    QTableWidgetItem *itm2 = new QTableWidgetItem(ui->comboBox_Bitness->currentText());
    ui->tableWidget_BusInBlock->setItem(CountRowInTable,2,itm2);

    ui->tableWidget_BusInBlock->update();

    Shine AddingBus;
    //AddingBus.NameShine = ui->lineEdit_NameBus->text();
    AddingBus.NameShine = "Name Bus";
    AddingBus.TypeShine = ui->comboBox_Type->currentIndex();
    AddingBus.Bitness = ui->comboBox_Bitness->currentText().toInt();
    AddingBus.ID = counterIdBus;
    counterIdBus++;

    int SizeBlock = System.Blocks.size();
    if (SizeBlock > 0){
        for (int i = 0; i < SizeBlock; i++){
            int SizeListBus = System.Blocks[i].ListShines.size();
            for (int j = 0; j < SizeListBus; j++){
                ConnectionBus Connection;
                Connection.IdBus = j;
                Connection.IdBlock = i;
                AddingBus.ConnectionOnID.push_back(Connection);
//                qDebug()<<"ID Block = "<<Connection.IdBlock;
//                qDebug()<<"ID Bis = "<<Connection.IdBus;
            }
        }
    }
    BusInBlock.push_back(AddingBus);

    ui->lineEdit_NameBus->clear();
    ui->comboBox_Type->update();
    ui->comboBox_Bitness->update();

}

void MainWindow::on_pushButton_AddBlock_clicked()
{
    /*
    if (ui->lineEdit_Block->text() == ""){
            QMessageBox msgBox;
            msgBox.setText("Вы не ввели название блока.");
            msgBox.exec();
            return;
    }
    */

    while (ui->tableWidget_BusInBlock->rowCount() > 0){
        ui->tableWidget_BusInBlock->removeRow(0);
    }

    while (ui->tableWidget_BusInBlock->rowCount() > 0){
        ui->tableWidget_BusInBlock->removeRow(0);
    }


    IpBlock block;
    //block.NameBlock = ui->lineEdit_Block->text();
    block.NameBlock = "Name Block";
    block.ListShines = BusInBlock;

    System.Blocks.push_back(block);

    DrawingBlock(0, HeightDrawing);
    if (System.Blocks.size() > 1){
        DrawingConnection();
    }

    HeightDrawing += Step * BusInBlock.size() + Step;
    counterIdBus = 0;
    BusInBlock.clear();
}

void MainWindow::DrawingBlock(int x, int y){
    DrawingObjects* item = new DrawingObjects();
    item->setPos(x,y);
    item->NameBlock = System.Blocks[System.Blocks.size()-1].NameBlock;
    item->Bus = System.Blocks[System.Blocks.size()-1].ListShines;

    if (System.Blocks.size()%2 == 0){
        item->Color = 0;
    }else{
        item->Color = 1;
    }

    scene->addItem(item);

}

void MainWindow::DrawingConnection(){
    DrawingConnections* item = new DrawingConnections();
    item->setPos(0,0);
    item->SystemBlocks = System;

    scene->addItem(item);
}

void MainWindow::DrawingSystem(){
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->resize(WIDTH,HEIGHT);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0,0,WIDTH,HEIGHT);

}
