#include "clickconnection.h"

ClickConnection::ClickConnection(System system, QObject *parent)
    : QObject(parent), QGraphicsItem(), system(system)
{

}

ClickConnection::~ClickConnection()
{

}

QRectF ClickConnection::boundingRect() const
{
    return QRectF(0,0,int(600*0.4),800);
}

void ClickConnection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    for (int i = 0; i < system.getSizeConnections(); i++){
        if (system.getMarkConnection(i) == false){
            int y = getStartCoordinate(system.getConnection(i));
            painter->setPen(Qt::gray);
            painter->drawLine(system.getXCoordinate(i), system.getYCoordinate(i)+5, int(600*0.4), system.getYCoordinate(i)+5);
            painter->drawLine(system.getXCoordinate(i)+5, y+10, int(600*0.4), y+10);
            painter->drawLine(system.getXCoordinate(i)+5, system.getYCoordinate(i)+5, system.getXCoordinate(i)+5, y+10);

        }
    }

    for (int i = 0; i < system.getSizeConnections(); i++){
        if (system.getMarkConnection(i) == true){
            int y = getStartCoordinate(system.getConnection(i));
            painter->setPen(Qt::black);
            painter->drawLine(system.getXCoordinate(i), system.getYCoordinate(i)+5, int(600*0.4), system.getYCoordinate(i)+5);
            painter->drawLine(system.getXCoordinate(i)+5, y+10, int(600*0.4), y+10);
            painter->drawLine(system.getXCoordinate(i)+5, system.getYCoordinate(i)+5, system.getXCoordinate(i)+5, y+10);

        }
    }

    for (int i = 0; i < system.getSizeConnections(); i++){
        if (system.getMarkConnection(i) == true){
            painter->setPen(Qt::black);
            painter->setBrush(Qt::black);
        }else{
            painter->setPen(Qt::gray);
            painter->setBrush(Qt::white);
        }
        painter->drawEllipse(system.getXCoordinate(i), system.getYCoordinate(i), 10, 10);
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)

}

int ClickConnection::getStartCoordinate(Connection connect){
    int height = 0;
    const int step = 20;

    for (int i = 0; i < connect.connectionBusStart.idBlock; i++){  //!!!!!!!!!!!!!!1
        height += step;
        for (int j = 0; j < system.getBlock(i).getListBuses().size(); j++){
            height += step;
        }
    }
    height += step + step*(connect.connectionBusStart.idBus+1);

    return height;
}


