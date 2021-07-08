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
public:
    explicit ClickConnection(QObject *parent = nullptr);
    ~ClickConnection();

    void addConnection(Connection connect);

    QVector <Connection> connection;


private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};

#endif // CLICKCONNECTION_H
