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

//        QFontMetrics fm(font);
//        int textWidth = fm.width(text);

//        painter->translate(0, 0);
//        painter->drawText(-textWidth/2, 0, text);

        QPainterPath path1;
        int height = 0;
        height = 20 + 20 * CountBus;
        path1.addRect(0, 0, 500, height);
        path1.addRect(200, 0, 0, height);
        path1.addRect(350, 0, 0, height);
        path1.addRect(500, 0, 0, height);

        painter->setBrush(QBrush("#e6e6fa"));
        painter->drawPath(path1);

//        painter->setBrush(QBrush("#c56c00"));
//        painter->drawRect(10, 15, 90, 60);

        }
};


#endif // DRAWINGOBJECTS_H

