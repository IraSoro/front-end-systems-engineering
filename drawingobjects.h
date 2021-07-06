//TODO: придумать что-то с типами шин, вывод связей сделать в другом классе
#ifndef DRAWINGOBJECTS_H
#define DRAWINGOBJECTS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QVector>
#include <QString>
#include <QFont>

#include "shine.h"


class DrawingObjects : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit DrawingObjects(){}
    ~DrawingObjects(){}

    QVector <Shine> Bus;
    QString NameBlock = "";
    bool Color = 0;

//    System SystemBlocks;

    QRectF boundingRect() const{
        return QRectF (0,0,500,800);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
        QPainterPath path1;
        int height = 0;
        int wight = 500;
        height = 20 + 20 * Bus.size();
        path1.addRect(0, 0, wight, height);

        if (Color){
            painter->setPen("#e6e6fa");
            painter->setBrush(QBrush("#e6e6fa"));
        }else{
            painter->setPen("#ffffff");
            painter->setBrush(QBrush("#ffffff"));
        }
        painter->drawPath(path1);

        painter->setPen("#000000");
        painter->drawLine(int(wight*0.4), 0, int(wight*0.4), height);
        painter->drawLine(int(wight*0.7), 0, int(wight*0.7), height);
        height = 0;


        painter->drawText( QRectF(wight*0.4 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, NameBlock);
        height += 20;
        QString Type[3] = {"Type1", "Type2", "Type3"}; //!!!!!!!!!!!!!!!!
        for (Shine VarBus: Bus) {
            painter->drawText( QRectF(wight*0.4 + 15, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, VarBus.NameShine);
            painter->drawText( QRectF(wight*0.7 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, Type[VarBus.TypeShine]);
            height += 20;
        }

    }
};


#endif // DRAWINGOBJECTS_H

