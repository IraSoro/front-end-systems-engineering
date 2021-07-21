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
    int getSizeBusInBlock(int indexBlock);
    void addBlock(IpBlock addingBlock);
    void addConnection(Connection addingConnection);
    void setMarkConnection(int index, bool settingMark);
    IpBlock getBlock(int index);
    IpBlock getLastBlock();
    Connection getConnection(int index);
    bool getMarkConnection(int indexConnection);
    int getXCoordinate(int indexConnection);
    int getYCoordinate(int indexConnection);
    bool ruleCheckConnection(int idBlockFirst, int idBusFirst, int typeSecondBus, int bitnessSecondBus);

    void deleteSystem();
    void readFile();
    int setTypeBus(QString typeStr);
    void outputSystem(QVector <IpBlock> );



private:    
    QVector <IpBlock> blocks;
    QVector <Connection> connection;

    bool ruleCheckConnection(int idBlockFirst, int idBusFirst, int typeSecondBus, int bitnessSecondBus, QVector <IpBlock> block);
    int getTypeBus(int idBlock, int idBus);
    int getBitnessBus(int idBlock, int idBus);

};

#endif // SYSTEM_H
