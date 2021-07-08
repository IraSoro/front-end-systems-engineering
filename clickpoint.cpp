#include "clickpoint.h"

ClickPoint::ClickPoint(QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

ClickPoint::~ClickPoint()
{

}

QRectF ClickPoint::boundingRect() const
{
    return QRectF(0,0,200,800);
}

void ClickPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    //painter->drawEllipse(QRectF(0,0,200,800));
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void ClickPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point;
    point = event->pos();
    qDebug()<<point;

    for (Connection tempCoordinate: connection){
        if (click(tempCoordinate.coordinates, point)){
            emit signal1();
            QGraphicsItem::mousePressEvent(event);
        }
    }

//    if (point.x() > 100 && point.y() > 100){
//        emit signal1();
//        QGraphicsItem::mousePressEvent(event);
//    }
}

bool ClickPoint::click(Coordinate coordinate, QPointF currentPoint){
    if (abs(coordinate.x - int(currentPoint.x())) <= 10 &&  abs(coordinate.y - int(currentPoint.y())) <= 10){
        return true;
    }else{
        return false;
    }
}

void ClickPoint::addConnection(Connection connect){
    this->connection.push_back(connect);
}

