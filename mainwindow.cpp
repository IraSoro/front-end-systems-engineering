#include "mainwindow.h"
#include "ui_mainwindow.h"



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

    point = new ClickPoint();
    connect(point,SIGNAL(signal1()),this, SLOT(slotFromPoint()));
    scene->addItem(point);
}

MainWindow::~MainWindow()
{
    busInBlock.clear();
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

    Bus addingBus("Name Bus", ui->comboBox_Type->currentIndex(), ui->comboBox_Bitness->currentText().toInt(), counterIdBus);
    //AddingBus.NameShine = ui->lineEdit_NameBus->text();
    counterIdBus++;

    int sizeBlock = system.blocks.size();
    if (sizeBlock > 0){
        for (int i = 0; i < sizeBlock; i++){
            int sizeListBus = system.blocks[i].getListBuses().size();
            for (int j = 0; j < sizeListBus; j++){
                ConnectionBus connection;
                connection.idBus = j;
                connection.idBlock = i;
                addingBus.addConnection(connection);
            }
        }
    }
    busInBlock.push_back(addingBus);

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


    IpBlock block("Name Block", busInBlock);
    //block.NameBlock = ui->lineEdit_Block->text();

    system.blocks.push_back(block);

    DrawingBlock(0, heightDrawing);
    if (system.blocks.size() > 1){
        DrawingConnection();
    }

    heightDrawing += step * busInBlock.size() + step;
    counterIdBus = 0;
    busInBlock.clear();

    displayTaggedLinks();
}

void MainWindow::DrawingBlock(int x, int y){
    DrawingObjects* item = new DrawingObjects();
    item->setPos(x,y);
    item->nameBlock = system.blocks[system.blocks.size()-1].getNameBlock();
    item->bus = system.blocks[system.blocks.size()-1].getListBuses();

    if (system.blocks.size()%2 == 0){
        item->setColor(0);
    }else{
        item->setColor(1);
    }

    scene->addItem(item);

}

void MainWindow::DrawingConnection(){
    DrawingConnections* item = new DrawingConnections(system);
    item->setPos(0,0);
    scene->addItem(item);

    for (Connection temp: item->getLastCoordinate()){
        system.connection.push_back(temp);
        point->addConnection(temp);
    }


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

void MainWindow::slotFromPoint()
{
    for (int i = 0; i < system.connection.size(); i++){
        system.connection[i].mark = false;
    }
    for (int temp: point->getMarkConnectons()){
        system.connection[temp].mark = true;
    }

    displayTaggedLinks();
}

void MainWindow::displayTaggedLinks(){    
    ClickConnection *temp = new ClickConnection();
    temp->setPos(0,0);
    temp->setSystem(system);
    scene->addItem(temp);
}


void MainWindow::on_action_triggered()
{
    system.WrittingToFile();
}
