#include "clickpoint.h"

ClickPoint::ClickPoint(QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

ClickPoint::~ClickPoint()
{
    markConnectons.clear();
    connection.clear();
}

QRectF ClickPoint::boundingRect() const
{
    return QRectF(0,0,200,800);
}

void ClickPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    for (Connection temp:connection){
//        if (temp.mark == true){
//            painter->setBrush(Qt::black);
//            painter->setPen(Qt::black);
//            painter->drawEllipse(temp.coordinates.x, temp.coordinates.y, 10, 10);
//        }else{
//            painter->setBrush(Qt::white);
//            painter->setPen(Qt::gray);
//            painter->drawEllipse(temp.coordinates.x, temp.coordinates.y, 10, 10);
//        }
//    }
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)

}

void ClickPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point;
    point = event->pos();
//    qDebug()<<point;

    for (int i = 0; i < connection.size(); i++){
        if (click(connection[i].coordinates, point)){
            if (connection[i].mark == false){
                connection[i].mark = true;
                markConnectons.push_back(i);
            }else{
                connection[i].mark = false;
                removeEl(i);
            }

            emit signal1();
            QGraphicsItem::mousePressEvent(event);
            break;

        }
    }    

}

void ClickPoint::removeEl(int var){
    QMutableVectorIterator<int> i(markConnectons);
        while(i.hasNext()) {
          int currentValue=i.next();
          if(currentValue == var)
          i.remove();
        }
}

bool ClickPoint::click(Coordinate coordinate, QPointF currentPoint){
    if (abs(coordinate.x + 5 - int(currentPoint.x())) <= 5 &&  abs(coordinate.y + 5 - int(currentPoint.y())) <= 5){
        return true;
    }else{
        return false;
    }
}

void ClickPoint::addConnection(Connection connect){
    this->connection.push_back(connect);
}

QVector <int> ClickPoint::getMarkConnectons(){
    return markConnectons;
}

