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
public:
    explicit DrawingConnections(){}
    ~DrawingConnections(){}

    System SystemBlocks;


    QRectF boundingRect() const{
        return QRectF (0,0,200,800);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
//        int Wight = 180;
//        int Height = 50;

//        for (int i = SystemBlocks.Blocks.size() - 2; i >= 0; i--){
//            Height += 20;
//            for (Shine TempBus: SystemBlocks.Blocks[i].ListShines){
//                Height += 20;
//                Wight -= 10;
//            }
//        }

//        Wight -= 10;
//        for (Shine TempBus: SystemBlocks.Blocks.last().ListShines){
//            painter->drawLine(Wight, 50, Wight, Height);
//            painter->drawLine(Wight, Height, 200, Height);
//            Height += 20;
//            Wight -= 10;
//        }

        int Wight = 180;
        int Height = 20;

        for (int i = SystemBlocks.Blocks.size() - 2; i >= 0; i--){
            Height += 20;
            for (Shine TempBus: SystemBlocks.Blocks[i].ListShines){
                Height += 20;
                if (TempBus.ConnectionOnID.size() > 0){
                    Wight -= 10;
                }
            }
        }
        Height += 10;
        int Height1 = 20;
        int SizeBus = SystemBlocks.Blocks.last().ListShines.size();
        for (int i = 0; i < SizeBus; i++){
            Wight -= 10;
            Height += 20;
            for (ConnectionBus TempConnection: SystemBlocks.Blocks.last().ListShines[i].ConnectionOnID){
                Height1 += (TempConnection.IdBus + 1)*20;
                for (int j = 0; j < TempConnection.IdBlock; j++){
                    Height1 += 20 + SystemBlocks.Blocks[j].ListShines.size() * 20;
                }
                painter->drawLine(Wight, Height, Wight, Height1+10);
                painter->drawLine(Wight, Height, 200, Height);
                painter->drawLine(Wight, Height1+10, 200, Height1+10);
                Height1 = 20;
            }
        }



    }
};

#endif // DRAWINGCONNECTIONS_H
