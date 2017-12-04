#include "CCreature.h"

#include "src/Map/CTileData.h"

CCreature::CCreature(const CCreature& creature) : CObject(creature)
{
    this->characteristics = creature.getCharacteristics();
    this->effects         = creature.getEffects();
    this->resistances     = creature.getResistances();  
}

CCreature::CCreature( const CObjectCreationParams& param) : CObject(param)
{
    try
    {
        const CCreatureCreationParams& creationParams = static_cast<const CCreatureCreationParams&>(param);
        this->characteristics = creationParams.characteristics;
        this->resistances = creationParams.resistances;
        this->effects = creationParams.effects;
    }
    catch(...)
    {
        setIsValid(false);
    }
}

CCreature::~CCreature()
{
    
}

void CCreature::update(const float dt)
{
    if(isNeedToUpdate)
    {
        effects.update(dt);
    }
}

float CCreature::getMoveSpeed() const
{
    return CMetrics::baseMoveSpeed;
}
unsigned int CCreature::getMoveCost(const CTileData& tile) const
{
    switch(tile.getTileBiom())
    {
        case ENBioms::DESERT:
            return 20;
        break;
        case ENBioms::GRASS:
            return 10;
        break;
        case ENBioms::LAVA:
            return 15;
        break;
        case ENBioms::SNOW:
            return 15;
        break;
        case ENBioms::WARFOG:
            return 9999;
        break;
        case ENBioms::WATER:
            return 9999;
        break;
        default: 
            return 9999;
        break;
    }
    return 9999;
}
