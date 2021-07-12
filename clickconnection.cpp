//TODO: сделать диаметр глобальной (?) константной переменной; вместо setSystem сделать конструктор с параметром
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
    for (int i = 0; i < system.connection.size(); i++){
        if (system.connection[i].mark == false){
            int y = getStartCoordinate(system.connection[i]);
            painter->setPen(Qt::gray);
            painter->drawLine(system.connection[i].coordinates.x, system.connection[i].coordinates.y+5, 200, system.connection[i].coordinates.y+5);
            painter->drawLine(system.connection[i].coordinates.x+5, y+10, 200, y+10);
            painter->drawLine(system.connection[i].coordinates.x+5, system.connection[i].coordinates.y+5, system.connection[i].coordinates.x+5, y+10);

        }
    }

    for (int i = 0; i < system.connection.size(); i++){
        if (system.connection[i].mark == true){
            int y = getStartCoordinate(system.connection[i]);
            painter->setPen(Qt::black);
            painter->drawLine(system.connection[i].coordinates.x, system.connection[i].coordinates.y+5, 200, system.connection[i].coordinates.y+5);
            painter->drawLine(system.connection[i].coordinates.x+5, y+10, 200, y+10);
            painter->drawLine(system.connection[i].coordinates.x+5, system.connection[i].coordinates.y+5, system.connection[i].coordinates.x+5, y+10);

        }
    }

    for (int i = 0; i < system.connection.size(); i++){
        if (system.connection[i].mark == true){
            painter->setPen(Qt::black);
            painter->setBrush(Qt::black);
        }else{
            painter->setPen(Qt::gray);
            painter->setBrush(Qt::white);
        }
        painter->drawEllipse(system.connection[i].coordinates.x, system.connection[i].coordinates.y, 10, 10);
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)

}

int ClickConnection::getStartCoordinate(Connection connect){
    int height = 0;
    const int step = 20;

    for (int i = 0; i < connect.connectionBusStart.IdBlock; i++){
        height += step;
        for (int j = 0; j < system.Blocks[i].ListShines.size(); j++){
            height += step;
        }
    }
    height += step + step*(connect.connectionBusStart.IdBus+1);

    return height;
}

void ClickConnection::setSystem(System system){
    this->system = system;
}

