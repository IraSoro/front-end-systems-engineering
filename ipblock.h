#ifndef IPBLOCK_H
#define IPBLOCK_H

#include <QString>
#include <QVector>
#include "bus.h"

class IpBlock
{

private:

public:
    IpBlock();
    IpBlock(QString nameBlock, QVector <Bus> listBuses);
    ~IpBlock();
    QString nameBlock = nullptr;
    QVector <Bus> listBuses;

};

#endif // IPBLOCK_H
