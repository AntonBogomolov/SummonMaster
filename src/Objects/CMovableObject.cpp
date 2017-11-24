#include "CMovableObject.h"

#include "src/Map/CTileData.h"

unsigned int CMovableObject::getMoveCost(const CTileData& tile) const
{
    return 10;
}