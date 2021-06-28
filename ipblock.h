#ifndef IPBLOCK_H
#define IPBLOCK_H

#include <QString>
#include <QVector>
#include "shine.h"

class IpBlock
{

private:

public:
    IpBlock();
    IpBlock(QString NameBlock, QVector <Shine> ListShines);
    ~IpBlock();
    QString NameBlock = nullptr;
    QVector <Shine> ListShines;

};

#endif // IPBLOCK_H
