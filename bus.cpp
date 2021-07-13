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
