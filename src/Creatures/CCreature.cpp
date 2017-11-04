#include "CCreature.h"


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

}