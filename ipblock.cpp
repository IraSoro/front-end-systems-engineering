#include "ipblock.h"

IpBlock::IpBlock()
{
    nameBlock = "";
}

IpBlock::IpBlock(QString nameBlock, QVector <Bus> listBuses, Coordinate coordinate) :
    nameBlock(nameBlock), listBuses(listBuses), coordinate(coordinate){}

IpBlock::~IpBlock()
{
    listBuses.clear();
}

QString IpBlock::getNameBlock(){
    return this->nameBlock;
}

Coordinate IpBlock::getCoordinate(){
    return this->coordinate;
}

QVector <Bus> IpBlock::getListBuses(){
    return this->listBuses;
}

int IpBlock::getTypeBusOnIndex(int index){
    return listBuses[index].getTypeBus();
}

int IpBlock::getBitnessBusOnIndex(int index){
    return listBuses[index].getBitness();
}

int IpBlock::getSizeBus(){
    return listBuses.size();
}
