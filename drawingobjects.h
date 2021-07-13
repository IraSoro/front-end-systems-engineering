//TODO: придумать что-то с типами шин
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

#include "bus.h"

class DrawingObjects : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit DrawingObjects();
    ~DrawingObjects();

    QVector <Bus> bus;
    QString nameBlock = "";
    bool color = 0;

    void setColor(bool color);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};


#endif // DRAWINGOBJECTS_H

