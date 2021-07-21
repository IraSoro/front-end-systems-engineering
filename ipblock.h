#ifndef IPBLOCK_H
#define IPBLOCK_H

#include <QString>
#include <QVector>

#include "bus.h"

struct Coordinate{
    int x = 0;
    int y = 0;
};

class IpBlock
{

private:
    QString nameBlock = "";
    QVector <Bus> listBuses;
    Coordinate coordinate;
public:
    IpBlock();
    IpBlock(QString nameBlock, QVector <Bus> listBuses, Coordinate coordinate);
    ~IpBlock();

    QString getNameBlock();
    QVector <Bus> getListBuses();
    Bus getBusOnIndex(int index);
    int getTypeBusOnIndex(int index);
    int getBitnessBusOnIndex(int index);
    int getSizeBus();
    Coordinate getCoordinate();

};

#endif // IPBLOCK_H
