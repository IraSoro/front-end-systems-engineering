//TODO: убрать три цикла
#ifndef DRAWINGCONNECTIONS_H
#define DRAWINGCONNECTIONS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QVector>
#include <QString>
#include <QFont>

#include "system.h"

class DrawingConnections : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

private:
    int const stepWight = 15;
    int const stepHeight = 20;
    int const diameterConnectionEllipse = 10;

public:
    explicit DrawingConnections(System systemBlock);
    ~DrawingConnections();

    System systemBlocks;
    QVector <Coordinate> coordinate;
    QVector <Connection> connections;


    QVector <Connection> getLastCoordinate();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);


};

#endif // DRAWINGCONNECTIONS_H
