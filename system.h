#ifndef SYSTEM_H
#define SYSTEM_H

#include <QVector>

#include "ipblock.h"

struct Coordinate{
    int x = 0;
    int y = 0;
};

class System
{
public:
    System();
    ~System();

    QVector <IpBlock> Blocks;
    QVector <Coordinate> CoordinateConnection;

private:


};

#endif // SYSTEM_H
