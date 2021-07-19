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
    void writtingToFile();
    void FindConnectoun(int idBlock, int idBus);
    int getSizeBlocks();
    int getSizeConnections();
    void addBlock(IpBlock addingBlock);
    void addConnection(Connection addingConnection);
    void setMarkConnection(int index, bool settingMark);
    IpBlock getBlock(int index);
    IpBlock getLastBlock();
    Connection getConnection(int index);
    bool getMarkConnection(int indexConnection);
    int getXCoordinate(int indexConnection);
    int getYCoordinate(int indexConnection);


private:    
    QVector <IpBlock> blocks;
    QVector <Coordinate> coordinateConnection;
    QVector <Connection> connection;

};

#endif // SYSTEM_H
