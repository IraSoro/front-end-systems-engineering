#include "ipblock.h"

IpBlock::IpBlock()
{

}

IpBlock::IpBlock(QString nameBlock, QVector <Bus> listBuses) : nameBlock(nameBlock), listBuses(listBuses){

}

IpBlock::~IpBlock()
{
    listBuses.clear();
}
