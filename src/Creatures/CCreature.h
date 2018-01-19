#pragma once

#include "src/IUpdatable.h"
#include "src/Objects/IMovable.h"
#include "src/Objects/CObject.h"
#include "src/Objects/CObjectContainer.h"

#include "CCharacteristics.h"
#include "CEffects.h"
#include "CResistances.h"
#include "src/Objects/CTags.h"

#include <string>
#include <vector>

class CCreatureCreationParams : public CObjectCreationParams
{
public:
    CCreatureCreationParams(const CResistances& resistances, const CCharacteristics& characteristics, 
                            const CEffects& effects) : CObjectCreationParams(ENObjectsType::CREATURE),
                            resistances(resistances), characteristics(characteristics), effects(effects)
    {
       
    }
    virtual ~CCreatureCreationParams()
    {
        
    }
    
    CResistances resistances;
    CCharacteristics characteristics;
    CEffects effects;
protected:    
};

class CCreature : public CObject, public IUpdatable, public IMovable
{
friend class CSpawner;
public:
    CCreature(const CCreature& creature);
    virtual ~CCreature();
    
    const CResistances& getResistances() const
    {
        return resistances;
    }
    const CCharacteristics& getCharacteristics() const
    {
        return characteristics;
    }
    CCharacteristics& getCharacteristicsForModify()
    {
        return characteristics;
    }
    const CEffects& getEffects() const
    {
        return effects;
    }
    virtual void update(const float dt);  
    virtual float getMoveSpeed() const;
    virtual unsigned int getMoveCost(const CTileData& tile) const;
    
    virtual const json toJSON() const
    {
        json result = CObject::toJSON();
        result["resistances"]       = resistances.toJSON();
        result["characteristics"]   = characteristics.toJSON();
        result["effects"]           = effects.toJSON();
        return result;
    }
protected:
    CCreature(const CObjectCreationParams& param); 

    CResistances resistances;
    CCharacteristics characteristics;
    CEffects effects;
};