#include "bus.h"

Bus::Bus()
{
    nameBus = "";
    typeBus = 0;
    bitness = 0;
    id = -1;
    startAddress = "";
    finishAddress = "";
}

Bus::Bus(QString nameBus, int typeBus, int bitness, int id, QString startAddress, QString finishAddress):
        nameBus(nameBus), typeBus(typeBus), bitness(bitness), id(id), startAddress(startAddress), finishAddress(finishAddress){}

Bus::~Bus()
{
    connectionOnID.clear();
}

QString Bus::getNameBus(){
    return this->nameBus;
}

QString Bus::getStartAddress(){
    return this->startAddress;
}

QString Bus::getFinishAddress(){
    return this->finishAddress;
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

ConnectionBus Bus::getConnectionOnIndex(int index){
    return this->connectionOnID[index];
}

void Bus::addConnection(ConnectionBus connection){
    connectionOnID.push_back(connection);
}

