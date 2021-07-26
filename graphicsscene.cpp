#include "graphicsscene.h"

GraphicsScene::GraphicsScene()
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    point = new ClickPoint();
    QObject::connect(point,SIGNAL(signal1()),this, SLOT(slotFromPoint()));
    QObject::connect(point,SIGNAL(signalClickBlock()),this, SLOT(slotFromBlock()));
    scene->addItem(point);
}


void GraphicsScene::deleteSystem(){
    counterIdBus = 0;
    busInBlock.clear();
    system.deleteSystem();
    point->clearPoint();

    point = new ClickPoint();
    QObject::connect(point,SIGNAL(signal1()),this, SLOT(slotFromPoint()));
    QObject::connect(point,SIGNAL(signalClickBlock()),this, SLOT(slotFromBlock()));
    scene->addItem(point);


}

void GraphicsScene::addBus(QString nameBus, int typeBus, int bitness, QString startAddress, QString finishAddress){

    Bus addingBus(nameBus, typeBus, bitness, counterIdBus, startAddress, finishAddress, system.installAllConnection(typeBus, bitness));

    busInBlock.push_back(addingBus);
    counterIdBus++;
}

void GraphicsScene::addBlock(QString nameBlock){
    Coordinate addingBlockCoordinate;
    addingBlockCoordinate.x = 0;
    addingBlockCoordinate.y = system.getHeightBlockForDrawing();
    IpBlock block(nameBlock, busInBlock, addingBlockCoordinate);
    system.addBlock(block);
    point->addBlock(block);

    DrawingBlock(addingBlockCoordinate.x, addingBlockCoordinate.y, system.getSizeBlocks()-1);
    if (system.getSizeBlocks() > 1){
        DrawingConnection(system.getSizeBlocks()-1);
    }


    displayTaggedLinks();

    counterIdBus = 0;
    busInBlock.clear();
}


void GraphicsScene::DrawingBlock(int x, int y, int index){
    QString nameBlock = system.getBlock(system.getSizeBlocks()-1).getNameBlock();
    DrawingObjects* item = new DrawingObjects(nameBlock, system.getBlock(index).getListBuses(), index);
    item->setPos(x,y);

    scene->addItem(item);
}

void GraphicsScene::DrawingConnection(int index){
    DrawingConnections* item = new DrawingConnections(system, index);
    item->setPos(0,0);
    scene->addItem(item);

    for (Connection temp: item->getLastCoordinate()){
        system.addConnection(temp);
        point->addConnection(temp);
    }

    item->clearDrawingConnection();

}

void GraphicsScene::DrawingSystem(){

}

void GraphicsScene::displayTaggedLinks(){
    ClickConnection *temp = new ClickConnection(system);
    temp->setPos(0,0);
    scene->addItem(temp);
}
void GraphicsScene::slotFromPoint(){
    for (int i = 0; i < system.getSizeConnections(); i++){
        system.setMarkConnection(i, false);
    }
    for (int temp: point->getMarkConnectons()){
        system.setMarkConnection(temp, true);
    }

    displayTaggedLinks();
}

void GraphicsScene::slotFromBlock(){
    windowBlock = new MainWindowBlock();
    windowBlock->show();

}



void GraphicsScene::writtingToFile(){
    system.writtingToFile();
}

void GraphicsScene::readingFile()
{
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
    system.updateHeightBlockForDrawing();
}
