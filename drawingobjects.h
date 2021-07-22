#ifndef DRAWINGOBJECTS_H
#define DRAWINGOBJECTS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QVector>
#include <QString>
#include <QFont>

#include "bus.h"

/*!
 * \brief класс, который отрисовывает один блок
 * \details выделяет блок цветом, отображает характеристики блока и характеристики всех шин, из которых блок состоит
 */
class DrawingObjects : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
private:
    QVector <Bus> bus;
    QString nameBlock = "";
    bool color = 0;

public:
    /*!
     * \brief конструктор с параметрами
     * \param nameBlock название блока
     * \param bus вектор шин
     * \param index идентификатор блока: по него вычисляет каким цветом будет изображен блок
     */
    explicit DrawingObjects(QString nameBlock, QVector <Bus> bus, int index);
    ~DrawingObjects();

    /*!
     * \brief переопределенная функция базового класса QGraphicsItem
     * \details определяет внешние границы элемента в виде прямоугольника; всё рисование должно быть ограничено внутри этого прямоугольника
     */
    QRectF boundingRect() const;
    /*!
     * \brief переопределенная функция базового класса QGraphicsItem
     * \details отрисовывает содержимое элементов в локальных координатах
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};


#endif // DRAWINGOBJECTS_H

