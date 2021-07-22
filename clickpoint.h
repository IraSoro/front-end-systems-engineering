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
    Q_INTERFACES(QGraphicsItem)
public:
    explicit ClickPoint(QObject *parent = nullptr);
    ~ClickPoint();

    void addConnection(Connection connect);
    void addBlock(IpBlock block);
    void setConnection(Connection connect);
    QVector <int> getMarkConnectons();

    QVector <Connection> connection;                //сделать private
    QVector <int> markConnectons;
    void clear();
    int getSizeConnection();
    int getSizeBlocks();

signals:
    void signal1();
    void signalClickBlock();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QVector <IpBlock> blocks;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    bool click(Coordinate coordinate, QPointF currentPoint);
    bool clickBlock(Coordinate coordinate, QPointF currentPoint);
    void removeEl(int var);

};


#endif // CLICKPOINT_H
