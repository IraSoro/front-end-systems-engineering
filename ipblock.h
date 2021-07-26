#ifndef IPBLOCK_H
#define IPBLOCK_H

#include <QString>
#include <QVector>

#include "bus.h"
/*!
 * \brief структура, которая хранит начальные координаты расположения блока на сцене
 */
struct Coordinate{
    Coordinate(){}
    Coordinate(int x, int y): x(x), y(y){}
    int x = 0;
    int y = 0;
};
/*!
 * \brief класс, описывающий блок
 */
class IpBlock
{

private:
    QString nameBlock = "";
    QVector <Bus> listBuses;
    Coordinate coordinate;
public:
    IpBlock();
    IpBlock(QString nameBlock, QVector <Bus> listBuses);
    IpBlock(QString nameBlock, QVector <Bus> listBuses, Coordinate coordinate);
    ~IpBlock();
    /*!
     * \brief возвращает название блока
     * \return строка-название блока
     */
    QString getNameBlock();
    /*!
     * \brief возвращает вектор шин в блоке
     * \return вектор из элементов типа Bus
     */
    QVector <Bus> getListBuses();
    /*!
     * \brief возвращает один элемент из вектора шин
     * \param index индекс элемента, который нужно получить
     * \return
     */
    Bus getBusOnIndex(int index);
    /*!
     * \brief возвращает тип шины - тип одного элемента из вектора шин
     * \param index индекс элемента, тип которого нужно получить
     * \return число - идентификатор типа шины
     */
    int getTypeBusOnIndex(int index);

    /*!
     * \brief возвращает разрядность шины - разрядность одного элемента из вектора шин
     * \param index индекс элемента, разрядность которого нужно получить
     * \return число - разрядность шины
     */
    int getBitnessBusOnIndex(int index);

    /*!
     * \brief возвращает количество шин в блоке
     * \return число - размер вектора шин
     */
    int getSizeBus();

    /*!
     * \brief возвращает координаты, где расположен на сцене блок
     * \return элемент типа Coordinate - координату расположения блока
     */
    Coordinate getCoordinate();

    void setCoordinate(Coordinate coord);

};

#endif // IPBLOCK_H
