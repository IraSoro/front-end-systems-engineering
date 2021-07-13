#include "drawingobjects.h"

DrawingObjects::DrawingObjects(){
    nameBlock = "";
    color = 0;
}

DrawingObjects::~DrawingObjects(){
    bus.clear();
}

void DrawingObjects::setColor(bool color){
    this->color = color;
}

QRectF DrawingObjects::boundingRect() const{
    return QRectF (0,0,500,800);
}

void DrawingObjects::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QPainterPath path1;
    int height = 0;
    int wight = 500;
    height = 20 + 20 * bus.size();
    path1.addRect(0, 0, wight, height);

    if (color){
        painter->setPen("#e6e6fa");
        painter->setBrush(QBrush("#e6e6fa"));
    }else{
        painter->setPen("#ffffff");
        painter->setBrush(QBrush("#ffffff"));
    }
    painter->drawPath(path1);

    painter->setPen("#000000");
    painter->drawLine(int(wight*0.4), 0, int(wight*0.4), height);
    painter->drawLine(int(wight*0.7), 0, int(wight*0.7), height);
    height = 0;


    painter->drawText( QRectF(wight*0.4 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, nameBlock);
    height += 20;
    QString Type[3] = {"Type1", "Type2", "Type3"}; //!!!!!!!!!!!!!!!!
    for (Bus VarBus: bus) {
        painter->drawText( QRectF(wight*0.4 + 15, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, VarBus.nameBus);
        painter->drawText( QRectF(wight*0.7 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, Type[VarBus.typeBus]);
        height += 20;
    }

}
