#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->tableWidget_BusInBlock->setColumnCount(5);
    QStringList name_table;
    name_table << "Название" << "Тип" << "Разрядность"<<"Начальный адрес"<<"Конечный адрес";
    ui->tableWidget_BusInBlock->setHorizontalHeaderLabels(name_table);

    drawingSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteSystem(){
    ui->graphicsView->scene()->clear();
    graphScene.deleteSystem();
}

void MainWindow::drawingSystem(){
    ui->graphicsView->resize(WIDTH,HEIGHT);
    ui->graphicsView->setScene(graphScene.scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    graphScene.scene->setSceneRect(0,0,WIDTH,HEIGHT);
}

void MainWindow::on_pushButton_AddBus_clicked(){

    if (ui->lineEdit_NameBus->text() == ""){
            QMessageBox msgBox;
            msgBox.setText("Вы не ввели название шины.");
            msgBox.exec();
            return;
    }

    if (ui->lineEdit_StartAddress->text() == "" || ui->lineEdit_FinishAddress->text() == ""){
            QMessageBox msgBox;
            msgBox.setText("Вы не ввели адрес шины.");
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
    QTableWidgetItem *itm3 = new QTableWidgetItem(ui->lineEdit_StartAddress->text());
    ui->tableWidget_BusInBlock->setItem(CountRowInTable,3,itm3);
    QTableWidgetItem *itm4 = new QTableWidgetItem(ui->lineEdit_FinishAddress->text());
    ui->tableWidget_BusInBlock->setItem(CountRowInTable,4,itm4);

    ui->tableWidget_BusInBlock->update();

    int indexTypeAddingBus = ui->comboBox_Type->currentIndex();
    int bitnessAddingBus = ui->comboBox_Bitness->currentText().toInt();
    graphScene.addBus(ui->lineEdit_NameBus->text(), indexTypeAddingBus, bitnessAddingBus, ui->lineEdit_StartAddress->text(), ui->lineEdit_FinishAddress->text());


    ui->lineEdit_NameBus->clear();
    ui->lineEdit_StartAddress->clear();
    ui->lineEdit_FinishAddress->clear();
    ui->comboBox_Type->update();
    ui->comboBox_Bitness->update();

}

void MainWindow::on_pushButton_AddBlock_clicked(){

    if (ui->lineEdit_Block->text() == ""){
            QMessageBox msgBox;
            msgBox.setText("Вы не ввели название блока.");
            msgBox.exec();
            return;
    }


    while (ui->tableWidget_BusInBlock->rowCount() > 0){
        ui->tableWidget_BusInBlock->removeRow(0);
    }

    while (ui->tableWidget_BusInBlock->rowCount() > 0){
        ui->tableWidget_BusInBlock->removeRow(0);
    }

    graphScene.addBlock(ui->lineEdit_Block->text());

}

void MainWindow::on_action_triggered(){
    graphScene.writtingToFile();
}

void MainWindow::on_action_2_triggered()
{
    deleteSystem();
    graphScene.readingFile();
}

void MainWindow::on_action_4_triggered()
{
    deleteSystem();
}
