#ifndef CLICKCONNECTION_H
#define CLICKCONNECTION_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QVector>

#include "system.h"

class ClickConnection: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit ClickConnection(QObject *parent = nullptr);
    ~ClickConnection();

    void setSystem(System system);

private:
    System system;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    int getStartCoordinate(Connection connect);

};

#endif // CLICKCONNECTION_H
