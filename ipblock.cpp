#include "ipblock.h"

IpBlock::IpBlock()
{
    nameBlock = "";
}

IpBlock::IpBlock(QString nameBlock, QVector <Bus> listBuses) : nameBlock(nameBlock), listBuses(listBuses){}

IpBlock::~IpBlock()
{
    listBuses.clear();
}

QString IpBlock::getNameBlock(){
    return this->nameBlock;
}

QVector <Bus> IpBlock::getListBuses(){
    return this->listBuses;
}

int IpBlock::getTypeBusOnIndex(int index){
    return listBuses[index].getTypeBus();
}

int IpBlock::getSizeBus(){
    return listBuses.size();
}
