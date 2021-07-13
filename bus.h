#ifndef SHINE_H
#define SHINE_H

#include <QString>
#include <QVector>

enum class TypeBus {Type1 = 0, Type2, Type3};

struct ConnectionBus{
    int idBlock = -1;
    int idBus = -1;
};

class Bus
{
private:
    QString nameBus = "";
    int typeBus = 0;
    int bitness = 0;
    int id = -1;
    QVector <ConnectionBus> connectionOnID;

public:    
    Bus();
    ~Bus();
    Bus(QString nameBus, int typeBus, int bitness, int id);

    QString getNameBus();
    int getTypeBus();
    int getBitness();
    int getId();
    QVector <ConnectionBus> getConnectionOnID();
    void addConnection(ConnectionBus connection);
};



#endif // SHINE_H
