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

/*!
 * \brief класс, который отображает возможные связи последнего добавленого блока с имеющимися блоками
 */
class DrawingConnections : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

private:
    int const stepWight = 15;
    int const stepHeight = 20;
    int const diameterConnectionEllipse = 10;    

    System systemBlocks;
    QVector <Coordinate> coordinate;
    QVector <Connection> connections;
    int indexBlock = 0;

public:
    /*!
     * \brief конструктор с параметром
     * \param systemBlock - элемент типа System: имеющаяся система с блоками и связями
     * \param index - индекс последнего блока, который добавлен в систему
     */
    explicit DrawingConnections(System systemBlock, int index);
    ~DrawingConnections();

    /*!
     * \brief возвращает вектор элементов типа Connection
     * \details формирует и просчитывает новые элементы типа Connection, получаемые из последнего добавленного блока:
     *          1. добавляет начальный и конечный ConnectionBus (две связанные шины)
     *          2. добавляет координаты элипса, нажатие на который обозначает данную связь
     * \return
     */
    QVector <Connection> getLastCoordinate();

    /*!
     * \brief переопределенная функция базового класса QGraphicsItem
     * \details определяет внешние границы элемента в виде прямоугольника; всё рисование должно быть ограничено внутри этого прямоугольника
     */
    QRectF boundingRect() const;

    /*!
     * \brief переопределенная функция базового класса QGraphicsItem
     * \details отрисовывает возможные связи между элементами в локальных координатах
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    /*!
     * \brief очищение объекта
     */
    void clearDrawingConnection();


};

#endif // DRAWINGCONNECTIONS_H
