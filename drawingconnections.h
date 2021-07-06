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
        int Wight = 180;
        int Height = 50;

        for (int i = SystemBlocks.Blocks.size() - 2; i >= 0; i--){
            Height += 20;
            for (Shine TempBus: SystemBlocks.Blocks[i].ListShines){
                Height += 20;
                Wight -= 10;
            }
        }

        Wight -= 10;
        for (Shine TempBus: SystemBlocks.Blocks.last().ListShines){
            painter->drawLine(Wight, 50, Wight, Height);
            painter->drawLine(Wight, Height, 200, Height);
            Height += 20;
            Wight -= 10;
        }


    }
};

#endif // DRAWINGCONNECTIONS_H
