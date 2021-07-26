//TODO: ТЕКУЩЕЕ РАСПОЛОЖЕНИЕ БЛОКА (КООРДИНАТА Y) СДЕЛАТЬ ПОЛЕМ КЛАССА SYSTEM

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

    DrawingSystem();

    point = new ClickPoint();
    connect(point,SIGNAL(signal1()),this, SLOT(slotFromPoint()));
    connect(point,SIGNAL(signalClickBlock()),this, SLOT(slotFromBlock()));
    scene->addItem(point);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteSystem(){
    heightDrawing = 20;
    counterIdBus = 0;
    busInBlock.clear();
    system.deleteSystem();
    point->clearPoint();
    //ui->graphicsView->items().clear();
    ui->graphicsView->scene()->clear();


    point = new ClickPoint();
    connect(point,SIGNAL(signal1()),this, SLOT(slotFromPoint()));
    connect(point,SIGNAL(signalClickBlock()),this, SLOT(slotFromBlock()));
    scene->addItem(point);


}

void MainWindow::on_pushButton_AddBus_clicked(){

//    if (ui->lineEdit_NameBus->text() == ""){
//            QMessageBox msgBox;
//            msgBox.setText("Вы не ввели название шины.");
//            msgBox.exec();
//            return;
//    }

//    if (ui->lineEdit_StartAddress->text() == "" || ui->lineEdit_FinishAddress->text() == ""){
//            QMessageBox msgBox;
//            msgBox.setText("Вы не ввели адрес шины.");
//            msgBox.exec();
//            return;
//    }


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
    Bus addingBus(ui->lineEdit_NameBus->text(), indexTypeAddingBus, bitnessAddingBus, counterIdBus, ui->lineEdit_StartAddress->text(), ui->lineEdit_FinishAddress->text());
    counterIdBus++;
    /*
     * тут формируются связи
     * |
     * V
    */
    int sizeBlock = system.getSizeBlocks();
    if (sizeBlock > 0){
        for (int i = 0; i < sizeBlock; i++){
            int sizeListBus = system.getSizeBusInBlock(i);
            for (int j = 0; j < sizeListBus; j++){
                if (system.ruleCheckConnection(i, j, indexTypeAddingBus, bitnessAddingBus)){
                    ConnectionBus connection;
                    connection.idBus = j;
                    connection.idBlock = i;
                    addingBus.addConnection(connection);
                }
            }
        }
    }
    busInBlock.push_back(addingBus);

    //ui->lineEdit_NameBus->clear();
    //ui->lineEdit_StartAddress->clear();
    //ui->lineEdit_FinishAddress->clear();
    ui->comboBox_Type->update();
    ui->comboBox_Bitness->update();

}

void MainWindow::on_pushButton_AddBlock_clicked(){

//    if (ui->lineEdit_Block->text() == ""){
//            QMessageBox msgBox;
//            msgBox.setText("Вы не ввели название блока.");
//            msgBox.exec();
//            return;
//    }


    while (ui->tableWidget_BusInBlock->rowCount() > 0){
        ui->tableWidget_BusInBlock->removeRow(0);
    }

    while (ui->tableWidget_BusInBlock->rowCount() > 0){
        ui->tableWidget_BusInBlock->removeRow(0);
    }

    Coordinate addingBlockCoordinate;
    addingBlockCoordinate.x = 0;
    addingBlockCoordinate.y = heightDrawing;
    IpBlock block(ui->lineEdit_Block->text(), busInBlock, addingBlockCoordinate);
    system.addBlock(block);
    point->addBlock(block);

    DrawingBlock(0, heightDrawing, system.getSizeBlocks()-1);
    if (system.getSizeBlocks() > 1){
        DrawingConnection(system.getSizeBlocks()-1);
    }

    heightDrawing += step * busInBlock.size() + step;
    counterIdBus = 0;
    busInBlock.clear();

    displayTaggedLinks();
}

void MainWindow::DrawingBlock(int x, int y, int index){
    QString nameBlock = system.getBlock(system.getSizeBlocks()-1).getNameBlock();
    DrawingObjects* item = new DrawingObjects(nameBlock, system.getBlock(index).getListBuses(), index);
    item->setPos(x,y);

    scene->addItem(item);
}

void MainWindow::DrawingConnection(int index){
    DrawingConnections* item = new DrawingConnections(system, index);
    item->setPos(0,0);
    scene->addItem(item);

    for (Connection temp: item->getLastCoordinate()){
        system.addConnection(temp);
        point->addConnection(temp);
    }

    item->clearDrawingConnection();

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

void MainWindow::slotFromPoint(){
    for (int i = 0; i < system.getSizeConnections(); i++){
        system.setMarkConnection(i, false);
    }
    for (int temp: point->getMarkConnectons()){
        system.setMarkConnection(temp, true);
    }

    displayTaggedLinks();
}

void MainWindow::slotFromBlock(){
    windowBlock = new MainWindowBlock();
    windowBlock->show();

}

void MainWindow::displayTaggedLinks(){    
    ClickConnection *temp = new ClickConnection(system);
    temp->setPos(0,0);
    scene->addItem(temp);
}


void MainWindow::on_action_triggered(){
    system.writtingToFile();
}

void MainWindow::on_action_2_triggered()
{
    deleteSystem();
    system.readFile();
    for (int i = 0; i < system.getSizeBlocks(); i++){
        point->addBlock(system.getBlock(i));
        DrawingBlock(0, system.getBlock(i).getCoordinate().y, i);
        if (i > 0){
            DrawingConnection(i);
        }
    }
    system.markToFile();
    for (int i = 0; i < system.getSizeConnections(); i++){
        if (system.getConnection(i).mark == true){
            point->addMarkConnection(i);
        }
    }
    displayTaggedLinks();
    heightDrawing = system.getHeightDrawingReadFile();
}

void MainWindow::on_action_4_triggered()
{
    deleteSystem();
}
