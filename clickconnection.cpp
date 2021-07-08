#include "clickconnection.h"

ClickConnection::ClickConnection(QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

ClickConnection::~ClickConnection()
{

}

QRectF ClickConnection::boundingRect() const
{
    return QRectF(0,0,200,800);
}

void ClickConnection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->setPen(Qt::black);
    for (Connection temp:connection){
        if (temp.mark == 1){
            painter->drawEllipse(temp.coordinates.x, temp.coordinates.y, 10, 10);
        }
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)

}


void ClickConnection::addConnection(Connection connect){
    this->connection.push_back(connect);
}

