#ifndef CLICKPOINT_H
#define CLICKPOINT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QVector>

#include "system.h"

/*!
 * \brief класс обрабатывает события нажатия мыши на сцене
 */
class ClickPoint: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit ClickPoint(QObject *parent = nullptr);
    ~ClickPoint();
    /*!
     * \brief добавление нового соединения
     * \param connect - элемент типа Connection
     */
    void addConnection(Connection connect);

    /*!
     * \brief добавление блока
     * \param элемент типа IpBlock
     */
    void addBlock(IpBlock block);

    /*!
     * \brief получение индексов связей, которые пометил пользователь
     * \return вектор индектов
     */
    QVector <int> getMarkConnectons();
    /*!
     * \brief очищение элементов класса
     */
    void clear();
    /*!
     * \brief возвращает количество связей
     * \return целое число - количество связей
     */
    int getSizeConnection();

    /*!
     * \brief возвращает количество блоков
     * \return целое число - количество блоков
     */
    int getSizeBlocks();

    void addMarkConnection(int readMarkConnection);

signals:
    /*!
     * \brief сиглал, возникающий после нажатия на элипс - связь блоков
     */
    void signal1();
    /*!
     * \brief сигнал, возникающий после нажатия на строку с именем блока
     */
    void signalClickBlock();

protected:
    /*!
     * \brief обработчик событий нажатия мыши
     * \param параметр event описывает нажатие мыши
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QVector <IpBlock> blocks;
    QVector <Connection> connection;
    QVector <int> markConnectons;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    /*!
     * \brief проверяет нажатие на элипс - связь
     * \param координаты связи
     * \param координаты нажатия мыши
     * \return если произошло нажатие по связи - true, иначе - false
     */
    bool click(Coordinate coordinate, QPointF currentPoint);
    /*!
     * \brief проверяет нажатие на блок
     * \param координаты связи
     * \param координаты нажатия мыши
     * \return если произошло нажатие по блоку - true, иначе - false
     */
    bool clickBlock(Coordinate coordinate, QPointF currentPoint);
    /*!
     * \brief удаление элементов вектора markConnection
     * \details вызывается в случае, если уже на помеченную связь нажали еще раз, после чего она становится непомеченной
     */
    void removeEl(int var);

};


#endif // CLICKPOINT_H
