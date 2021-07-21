#ifndef SHINE_H
#define SHINE_H

#include <QString>
#include <QVector>

enum class TypeBus {AVALON = 0, AXI, APB, WISHBONE,     MAX_BUS = 4};
const QString g_typeBus[4] = {"AVALON", "AXI", "APB", "WISHBONE"};
const bool g_busMapping[static_cast<int>(TypeBus::MAX_BUS)][static_cast<int>(TypeBus::MAX_BUS)] = {
    {true, false, false, false},
    {false, true, false, false},
    {false, false, true, false},
    {false, false, false, true}
};

struct ConnectionBus{
    int idBlock = -1;
    int idBus = -1;
};

class Bus
{
private:
    QString nameBus = "";
    QString startAddress = "";
    QString finishAddress = "";
    int typeBus = 0;
    int bitness = 0;
    int id = -1;
    QVector <ConnectionBus> connectionOnID;

public:    
    Bus();
    ~Bus();
    Bus(QString nameBus, int typeBus, int bitness, int id, QString startAddress, QString finishAddress);

    QString getNameBus();
    QString getStartAddress();
    QString getFinishAddress();
    int getTypeBus();
    int getBitness();
    int getId();
    QVector <ConnectionBus> getConnectionOnID();
    ConnectionBus getConnectionOnIndex(int index);
    void addConnection(ConnectionBus connection);
};



#endif // SHINE_H
