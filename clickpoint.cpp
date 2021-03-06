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

void ClickPoint::clearPoint(){
    markConnectons.clear();
    connection.clear();
    blocks.clear();
}

QRectF ClickPoint::boundingRect() const
{
    return QRectF(0,0,600,800);
}

void ClickPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)

}

void ClickPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point;
    point = event->pos();

    for (int i = 0; i < blocks.size(); i++){
        if (clickBlock(blocks[i].getCoordinate(), point)){
            emit signalClickBlock();
            QGraphicsItem::mousePressEvent(event);
            return;
        }
    }

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
            return;

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

bool ClickPoint::clickBlock(Coordinate coordinate, QPointF currentPoint){
    if (coordinate.y < currentPoint.y() && coordinate.y + 20 > currentPoint.y()){
        return true;
    }else{
        return false;
    }
}

int ClickPoint::getSizeConnection(){
    return connection.size();
}

int ClickPoint::getSizeBlocks(){
    return blocks.size();
}

void ClickPoint::addConnection(Connection connect){
    this->connection.push_back(connect);
}

void ClickPoint::addBlock(IpBlock block){
    this->blocks.push_back(block);
}

QVector <int> ClickPoint::getMarkConnectons(){
    return markConnectons;
}

void ClickPoint::addMarkConnection(int readMarkConnection){
    markConnectons.push_back(readMarkConnection);
}

