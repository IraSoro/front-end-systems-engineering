#ifndef SYSTEM_H
#define SYSTEM_H

#include <QVector>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

#include "ipblock.h"

struct Coordinate{
    int x = 0;
    int y = 0;
};

struct Connection{
    Coordinate coordinates;
    ConnectionBus connectionBusStart;
    ConnectionBus connectionBusFinish;
    bool mark = 0;
};

class System
{
public:
    System();
    ~System();
    void WrittingToFile();
    void FindConnectoun(int idBlock, int idBus);

    QVector <IpBlock> Blocks;
    QVector <Coordinate> CoordinateConnection;
    QVector <Connection> connection;

private:


};

#endif // SYSTEM_H
