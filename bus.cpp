#include "bus.h"

Bus::Bus()
{
    nameBus = "";
    typeBus = 0;
    bitness = 0;
    id = -1;
}

Bus::Bus(QString nameBus, int typeBus, int bitness, int id):
        nameBus(nameBus), typeBus(typeBus), bitness(bitness), id(id){}

Bus::~Bus()
{
    connectionOnID.clear();
}

QString Bus::getNameBus(){
    return this->nameBus;
}

int Bus::getTypeBus(){
    return this->typeBus;
}

int Bus::getBitness(){
    return this->bitness;
}

int Bus::getId(){
    return this->id;
}

QVector <ConnectionBus> Bus::getConnectionOnID(){
    return this->connectionOnID;
}

void Bus::addConnection(ConnectionBus connection){
    connectionOnID.push_back(connection);
}

