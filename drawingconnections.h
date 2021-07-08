//TODO: убрать три цикла
#ifndef DRAWINGCONNECTIONS_H
#define DRAWINGCONNECTIONS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QVector>
#include <QString>
#include <QFont>

#include "system.h"

class DrawingConnections : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    int stepWight = 15;
    int stepHeight = 20;
    int diameterConnectionEllipse = 10;

public:
    //explicit DrawingConnections(){}
    explicit DrawingConnections(System systemBlock): systemBlocks(systemBlock){}
    ~DrawingConnections(){
        coordinate.clear();
    }

    System systemBlocks;
    QVector <Coordinate> coordinate;
    QVector <Connection> connections;


    QVector <Connection> getLastCoordinate(){
        coordinate.clear();
        int wight = 180;
        int height = stepHeight;

        for (int i = systemBlocks.Blocks.size() - 2; i >= 0; i--){
            height += stepHeight;
            for (Shine TempBus: systemBlocks.Blocks[i].ListShines){
                height += stepHeight;
                if (TempBus.ConnectionOnID.size() > 0){
                    wight -= stepWight;
                }
            }
        }

        height += stepHeight/2;
        int height1 = stepHeight;
        int SizeBus = systemBlocks.Blocks.last().ListShines.size();

        for (int i = 0; i < SizeBus; i++){
            wight -= stepWight;
            height += stepHeight;
            for (ConnectionBus TempConnection: systemBlocks.Blocks.last().ListShines[i].ConnectionOnID){
                height1 += (TempConnection.IdBus + 1)*stepHeight;
                for (int j = 0; j < TempConnection.IdBlock; j++){
                    height1 += stepHeight + systemBlocks.Blocks[j].ListShines.size() * stepHeight;
                }
                Coordinate tempCoord;
                tempCoord.x = wight-5;
                tempCoord.y = height1+5;
                coordinate.push_back(tempCoord);

                Connection tempConn;
                tempConn.coordinates = tempCoord;
                tempConn.connectionBusStart.IdBlock = systemBlocks.Blocks.size()-1;
                tempConn.connectionBusStart.IdBus = i;
                tempConn.connectionBusFinish = TempConnection;
                connections.push_back(tempConn);

                height1 = stepHeight;
            }
        }

        return connections;
    }

    QRectF boundingRect() const{
        return QRectF (0,0,200,800);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

        if (systemBlocks.Blocks.size() == 0){
            return;
        }

        coordinate.clear();
        int wight = 180;
        int height = stepHeight;

        for (int i = systemBlocks.Blocks.size() - 2; i >= 0; i--){
            height += stepHeight;
            for (Shine TempBus: systemBlocks.Blocks[i].ListShines){
                height += stepHeight;
                if (TempBus.ConnectionOnID.size() > 0){
                    wight -= stepWight;
                }
            }
        }

        height += stepHeight/2;
        int height1 = stepHeight;
        int SizeBus = systemBlocks.Blocks.last().ListShines.size();

        painter->setPen(Qt::gray);
        for (int i = 0; i < SizeBus; i++){
            wight -= stepWight;
            height += stepHeight;
            for (ConnectionBus TempConnection: systemBlocks.Blocks.last().ListShines[i].ConnectionOnID){
                height1 += (TempConnection.IdBus + 1)*stepHeight;
                for (int j = 0; j < TempConnection.IdBlock; j++){
                    height1 += stepHeight + systemBlocks.Blocks[j].ListShines.size() * stepHeight;
                }
                painter->drawLine(wight, height, wight, height1+10);
                painter->drawLine(wight, height, 200, height);
                painter->drawLine(wight, height1+10, 200, height1+10);

                Coordinate tempCoord;
                tempCoord.x = wight-5;
                tempCoord.y = height1+5;
                coordinate.push_back(tempCoord);

                height1 = stepHeight;
            }
        }

        for (Connection tempCoordinate: systemBlocks.connection){
            if (tempCoordinate.mark == 1){
                painter->setBrush(Qt::black);
                painter->setPen(Qt::black);
            }
            else{
                painter->setBrush(Qt::white);
                painter->setPen(Qt::black);
            }
            painter->drawEllipse(tempCoordinate.coordinates.x, tempCoordinate.coordinates.y, diameterConnectionEllipse, diameterConnectionEllipse);
        }

        painter->setBrush(Qt::white);
        painter->setPen(Qt::black);
        for (Coordinate tempCoordinate: coordinate){
            painter->drawEllipse(tempCoordinate.x, tempCoordinate.y, diameterConnectionEllipse, diameterConnectionEllipse);
        }

    }


};

#endif // DRAWINGCONNECTIONS_H
