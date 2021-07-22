#include "drawingconnections.h"

DrawingConnections::DrawingConnections(System systemBlock, int index): systemBlocks(systemBlock), indexBlock(index){}

DrawingConnections::~DrawingConnections(){
        coordinate.clear();
    }

QVector <Connection> DrawingConnections::getLastCoordinate(){
    coordinate.clear();
    int wight = int(600*0.4 *0.9);
    int height = stepHeight;

    for (int i = indexBlock - 1; i >= 0; i--){
        height += stepHeight;
        for (Bus TempBus: systemBlocks.getBlock(i).getListBuses()){
            height += stepHeight;
            if (TempBus.getConnectionOnID().size() > 0){
                wight -= stepWight;
            }
        }
    }

    height += stepHeight/2;
    int height1 = stepHeight;
    int SizeBus = systemBlocks.getBlock(indexBlock).getListBuses().size();

    for (int i = 0; i < SizeBus; i++){
        wight -= stepWight;
        height += stepHeight;
        for (ConnectionBus TempConnection: systemBlocks.getBlock(indexBlock).getListBuses()[i].getConnectionOnID()){
            height1 += (TempConnection.idBus + 1)*stepHeight;
            for (int j = 0; j < TempConnection.idBlock; j++){
                height1 += stepHeight + systemBlocks.getBlock(j).getListBuses().size() * stepHeight;
            }
            Coordinate tempCoord;
            tempCoord.x = wight-5;
            tempCoord.y = height1+5;
            coordinate.push_back(tempCoord);

            Connection tempConn;
            tempConn.coordinates = tempCoord;
            tempConn.connectionBusStart.idBlock = systemBlocks.getSizeBlocks()-1;
            tempConn.connectionBusStart.idBus = i;
            tempConn.connectionBusFinish = TempConnection;
            connections.push_back(tempConn);

            height1 = stepHeight;
        }
    }

    return connections;
}

QRectF DrawingConnections::boundingRect() const{
    return QRectF (0,0,int(600*0.4),800);
}


void DrawingConnections::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){


    if (indexBlock < 1){
        return;
    }
    coordinate.clear();
    int wight = int(600*0.4 * 0.9);
    int height = stepHeight;

    for (int i = indexBlock - 1; i >= 0; i--){
        height += stepHeight;
        for (Bus TempBus: systemBlocks.getBlock(i).getListBuses()){
            height += stepHeight;
            if (TempBus.getConnectionOnID().size() > 0){            //!!!!!!!!!!!!!
                wight -= stepWight;
            }
        }
    }


    height += stepHeight/2;
    int height1 = stepHeight;
    int SizeBusInLastBlock = systemBlocks.getBlock(indexBlock).getListBuses().size();//!!!!!!!!!!

    painter->setPen(Qt::gray);
    for (int i = 0; i < SizeBusInLastBlock; i++){
        wight -= stepWight;
        height += stepHeight;
        for (ConnectionBus TempConnection: systemBlocks.getBlock(indexBlock).getListBuses()[i].getConnectionOnID()){
            height1 += (TempConnection.idBus + 1)*stepHeight;
            for (int j = 0; j < TempConnection.idBlock; j++){
                height1 += stepHeight + systemBlocks.getBlock(j).getListBuses().size() * stepHeight;
            }
            painter->drawLine(wight, height, wight, height1+10);
            painter->drawLine(wight, height, int(600*0.4), height);
            painter->drawLine(wight, height1+10, int(600*0.4), height1+10);

            Coordinate tempCoord;
            tempCoord.x = wight-5;
            tempCoord.y = height1+5;
            coordinate.push_back(tempCoord);

            height1 = stepHeight;
        }
    }

    for (int i = 0; i < systemBlocks.getSizeConnections(); i++){
        if (systemBlocks.getMarkConnection(i) == true){
            painter->setBrush(Qt::black);
            painter->setPen(Qt::black);
        }else{
            painter->setBrush(Qt::white);
            painter->setPen(Qt::gray);
        }
        painter->drawEllipse(systemBlocks.getXCoordinate(i), systemBlocks.getYCoordinate(i), diameterConnectionEllipse, diameterConnectionEllipse);
    }

    painter->setBrush(Qt::white);
    painter->setPen(Qt::gray);
    for (Coordinate tempCoordinate: coordinate){
        painter->drawEllipse(tempCoordinate.x, tempCoordinate.y, diameterConnectionEllipse, diameterConnectionEllipse);
    }

}
