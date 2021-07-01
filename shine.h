#ifndef SHINE_H
#define SHINE_H

#include <QString>

enum class TypeBus {Type1 = 0, Type2, Type3};

class Shine
{
public:    
    Shine();

    QString NameShine = "";
    int TypeShine = 0;
    int Bitness = 0;
};

#endif // SHINE_H
