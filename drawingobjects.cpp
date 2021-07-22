#include "drawingobjects.h"

DrawingObjects::DrawingObjects(QString nameBlock, QVector <Bus> bus, int index): bus(bus), nameBlock(nameBlock){
    if (index%2 == 0){
        color = true;
    }else{
        color = false;
    }
}

DrawingObjects::~DrawingObjects(){
    bus.clear();
}

QRectF DrawingObjects::boundingRect() const{
    return QRectF (0,0,600,800);
}

void DrawingObjects::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QPainterPath path1;
    int height = 0;
    int wight = 600;
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
    painter->drawLine(int(wight*0.52), 0, int(wight*0.52), height);
    painter->drawLine(int(wight*0.64), 0, int(wight*0.64), height);
    painter->drawLine(int(wight*0.76), 0, int(wight*0.76), height);
    painter->drawLine(int(wight*0.88), 0, int(wight*0.88), height);
    height = 0;


    painter->drawText( QRectF(wight*0.4 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, nameBlock);
    height += 20;
    for (Bus VarBus: bus) {
        painter->drawText( QRectF(wight*0.4 + 15, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, VarBus.getNameBus());
        painter->drawText( QRectF(wight*0.52 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, g_typeBus[VarBus.getTypeBus()]);
        painter->drawText( QRectF(wight*0.64 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, QString::number(VarBus.getBitness()));
        painter->drawText( QRectF(wight*0.76 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, VarBus.getStartAddress());
        painter->drawText( QRectF(wight*0.88 + 3, height, 100, 20), Qt::TextWordWrap | Qt::AlignVCenter, VarBus.getFinishAddress());
        height += 20;
    }

}
