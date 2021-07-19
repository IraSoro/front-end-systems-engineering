#ifndef IPBLOCK_H
#define IPBLOCK_H

#include <QString>
#include <QVector>

#include "bus.h"

class IpBlock
{

private:
    QString nameBlock = "";
    QVector <Bus> listBuses;
public:
    IpBlock();
    IpBlock(QString nameBlock, QVector <Bus> listBuses);
    ~IpBlock();

    QString getNameBlock();
    QVector <Bus> getListBuses();
    int getTypeBusOnIndex(int index);
    int getBitnessBusOnIndex(int index);
    int getSizeBus();
};

#endif // IPBLOCK_H
