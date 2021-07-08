#ifndef CLICKPOINT_H
#define CLICKPOINT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QVector>

#include "system.h"

class ClickPoint: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ClickPoint(QObject *parent = nullptr);
    ~ClickPoint();

    void addConnection(Connection connect);
    QVector <Connection> connection;
    //System system;

signals:
    void signal1();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    bool click(Coordinate coordinate, QPointF currentPoint);

};


#endif // CLICKPOINT_H
