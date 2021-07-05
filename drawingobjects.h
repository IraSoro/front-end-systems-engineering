#ifndef DRAWINGOBJECTS_H
#define DRAWINGOBJECTS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QVector>
#include <QString>
#include <QFont>
#include <QFontMetrics>

#include "shine.h"


class DrawingObjects : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit DrawingObjects(){}
    ~DrawingObjects(){}

    QVector <Shine> Bus;
    QString NameBlock = "";
    int CountBus = 0;
    bool Color = 0;

    QRectF boundingRect() const{
        return QRectF (0,0,500,800);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
//        painter->setPen(Qt::black);

//        QPainterPath path1;
//        path1.addEllipse(boundingRect());
//        painter->drawPath(path1);

//        painter->setPen(qRgb(0,0,0));
//        QFont font("Courier", 16, QFont::DemiBold);

//        QString text = "1";
//        QFontMetrics fm(font);
//        int textWidth = fm.width(text);

//        painter->translate(0, 0);
//        painter->drawText(-textWidth/2, 0, text);

        QPainterPath path1;
        int height = 0;
        int wight = 500;
        height = 20 + 20 * CountBus;
        path1.addRect(0, 0, wight, height);
        path1.addRect(wight*0.4, 0, 0, height);
        path1.addRect(wight*0.7, 0, 0, height);
        path1.addRect(wight, 0, 0, height);
        height = 0;

        if (Color){
            painter->setBrush(QBrush("#e6e6fa"));
        }else{
            painter->setBrush(QBrush("#ffffff"));
        }
        painter->drawPath(path1);

        painter->drawText( QRectF(wight*0.4 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, NameBlock);
        height += 20;
        QString Type[3] = {"Type1", "Type2", "Type3"}; //!!!!!!!!!!!!!!!!
        for (Shine VarBus: Bus) {
            painter->drawText( QRectF(wight*0.4 + 15, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, VarBus.NameShine);
            painter->drawText( QRectF(wight*0.7 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, Type[VarBus.TypeShine]);
            height += 20;
        }



        //painter->drawText( QRectF(210, 0, 1000, 20), Qt::TextWordWrap | Qt::AlignVCenter, "label" );


        }
};


#endif // DRAWINGOBJECTS_H

